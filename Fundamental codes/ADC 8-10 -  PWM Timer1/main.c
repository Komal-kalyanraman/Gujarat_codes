
///////////////////////// IN THE TRANSMITTER SIDE WHEN THE TERMINALS ARE TOUCHED WITH THE TONGUE 
///////// ADC VALUES ARE TAKEN INTO CONSIDERATION AND PARTICULAR LETTERS ARE TRANSMITTED

#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>
#include <uart.c>
#include <uart.h> 

///////////////////////////// 10 bit ADC //////////////////////////////////////////

uint16_t readADC(int channel)	
{
	
	uint16_t value=0;
	
	ADCSRA |= (1 << ADPS2)| (1 << ADIF);// Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz

	ADMUX = channel;
	
	ADMUX |= (0 << REFS0)|(0 << REFS1); // Set ADC reference to internal 2.56v
	
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


///////////////////////////// 8 bit ADC //////////////////////////////////////////

int readADC(int channel)	 
{

	ADMUX=channel;
	ADMUX|=(1<<ADLAR)|(1<<REFS0);//|(1<<REFS1);	//supply vcc
	
	ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADEN)|(1<<ADSC);	//scaling factor=8 ,adc enable,start conversion


	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA|=(1<<ADIF);
	
	return ADCH;

}
	
unsigned int a=0;	
	
void main()
{
	 
	unsigned char str[10]={0};

	
	TCNT1 = 0X0000;

	TCCR1A=(1 << WGM10)| (1 << COM1A1) | (1 << COM1B1);
	TCCR1B=(1 << CS10) |(1 << CS12) | (1 << WGM12);
	
	OCR1B=200;

	sbi(DDRB,1);
	sbi(PORTB,1);
	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));

	while(1)
	{
		a=readADC(0);
		OCR1A=a;
		
		itoa(a,str,10);
		
		
		//uart_puts(str);
		//uart_puts("\n");
		//uart_puts("\r");
		//_delay_ms(50);
		
	}
	
}
