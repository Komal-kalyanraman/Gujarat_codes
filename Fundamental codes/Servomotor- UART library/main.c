
/////////////////////////// THE LETTERS ARE RECEIVED AT THE RECEIVERS END AND SERVOS ARE CONTROLLED ACCORDINGLY 


#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>

#include <uart.c>
#include <uart.h> 

#include "servo.c"

uint16_t readADC(int channel)
{
	
	uint16_t value=0;
	
	ADCSRA |= (1 << ADPS2)| (1 << ADIF);// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (1 << REFS0); // Set ADC reference to internal 2.56v
	
	ADCSRA |= (1 << ADEN);  // Enable ADC
	
	for(int i=0;i<3;i++)
	{
	
		ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
		
		while(!(ADCSRA & (1<<ADIF)));
		
		ADCSRA|=(1<<ADIF);	
		
		value = ADCL+(ADCH<<8);	
		
	}
	
	return value;
}
	
	
void main()
{
	servoStart();	
	setServoPosition(1,90);
	sei();
	unsigned int a,b,c; 
	unsigned char buff[20]={0};
	
	unsigned int k,l;	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	
	while(1)
	{
	
	l1:		k=uart_getc();
	
		if(!(k & (UART_NO_DATA)))
		{
				if(k=='R')
			{
				for(int i=0;i<180;i++)
				{
					setServoPosition(0,i);
					_delay_ms(20);
				}
			
			}
		
				else if(k=='L')
			{
						
				for(int i=179;i>0;i--)
				{
					setServoPosition(0,i);
					_delay_ms(20);
				}
			}
			
				else if(k=='O')
			{
				for(int i=0;i<100;i++)
				{
					setServoPosition(1,i);
					_delay_ms(20);
				}
			}
			
				else if(k=='C')
			{
				for(int i=100;i>20;i--)
				{
					setServoPosition(1,i);
					_delay_ms(20);
				}
			}
			
				
				else
			{
				_delay_ms(1);
			}	
			
		}

	}
}
