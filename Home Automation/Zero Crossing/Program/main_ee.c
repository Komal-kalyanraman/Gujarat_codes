#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include <stdint.h>
#include <stdlib.h>
#include "myutils.h"
#include "rc5.h"
#include "rc5.c"
#include "eeprom.h"
#include "eeprom.c"
#include <uart.c>
#include <uart.h> 


uint8_t app_1,app_2,app_3,app_4,app_5,fan,fan1,cmd=0;

uint8_t speed=0,speed1=0,value,value1,value2;
//uint8_t fan_on=0;
//uint8_t table[6]={160,90,75,60,53,43,30};
//uint8_t table1[6]={160,75,60,53,43,30};
uint8_t table[8]={160,110,90,88,79,70,60,45};
uint8_t table1[8]={160,110,90,88,79,70,60,45};



//Zero Crossing Detect.


ISR(INT1_vect)
{
	//timer2
	OCR2=table[speed];
	TCNT2=0x00;

	TCCR2|=((1<<CS22)|(1<<CS21)|(1<<CS20));	//Start Timer prescaler =1024

	//timer0
	OCR0=table1[speed1];

	TCNT0=0x00;
	sbi(TCCR0,0);
	cbi(TCCR0,1);
	sbi(TCCR0,2);
	//TCCR0|=((1<<CS02)|(1<<CS00));	//Start Timer prescaler =1024
	

}



//Timer2 Compare ISR


ISR(TIMER2_COMP_vect)
{
	
	PORTB|=(1<<PB1);	//High = TRIAC on
	TCCR2&=(~((1<<CS22)|(1<<CS21)|(1<<CS20)));	//Stop Timer
	_delay_us(10);
	PORTB&=(~(1<<PB1)); //low = TRIAC off
	
}


//Timer0 Compare ISR

ISR(TIMER0_COMP_vect)
{
	
	PORTB|=(1<<PB2);	//High = TRIAC on
//	TCCR0&=(~((1<<CS02)|(1<<CS00)));	//Stop Timer
	cbi(TCCR0,0);
	cbi(TCCR0,1);
	cbi(TCCR0,2);
	_delay_us(10);
	PORTB&=(~(1<<PB2)); //low = TRIAC off
	
}



int main()
{
	uart_init(UART_BAUD_SELECT(9600,F_CPU)); //UART intialization
	
	//Give Some Time for other hardware to start
	_delay_loop_2(0);

	sei();
	char str[10]={0};
	char p;
	//unsigned int k;
	
	while(1)
	{
		
		
		
		p=uart_getc();
		
		//if(!(p & (UART_NO_DATA)))
		{
			//itoa(p,str,10);
			
			//uart_puts(str);
			//uart_putc('\n');
			//uart_putc('\r');
				
				if(p=='A')								//Switch 1
				{	
					uart_puts("E");	
				}
				
				
				if(p=='a')
				{
					uart_puts("e");
				}
				
			_delay_ms(100);	
		}
		    if(p=='B')							//Switch 2
			{
				app_2=0;
				sbi(PORTB,4);
				sbi(PORTC,4);
				EEPROM_write(1,app_2); //saving the state of appliance	
			}
			
			
		    if(p=='b')
			{
				app_2=0xFF;
				cbi(PORTB,4);
				cbi(PORTC,4);
				EEPROM_write(1,app_2); //saving the state of appliance	
	
			}
			
		
		    if(p=='C')							//Switch 3
			{
				app_3=0;
				sbi(PORTB,5);
				sbi(PORTC,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}
			
			
		    if(p=='c')
			{
				app_3=0xFF;
				cbi(PORTB,5);
				cbi(PORTC,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}


		    if(p=='D')							//Switch 4
			{
				app_4=0;
				sbi(PORTB,6);
				sbi(PORTC,6);
				EEPROM_write(3,app_4); //saving the state of appliance	
			}
			
			
			if(p=='d')
			{
				app_4=0xFF;
				cbi(PORTB,6);
				cbi(PORTC,6);
				EEPROM_write(3,app_4); //saving the state of appliance	

			}
			
			
			if(p=='E')							//Switch 5
			{
				app_5=0;
				sbi(PORTB,7);
				sbi(PORTC,7);
				EEPROM_write(4,app_5); //saving the state of appliance	
			}
			
			
			if(p=='e')
			{
				app_5=0xFF;
				cbi(PORTB,7);
				cbi(PORTC,7);
				EEPROM_write(4,app_5); //saving the state of appliance	
			}
			
			
			
			if(p=='m')	// Indicator Off
			{	
				count=1;
				
			}
		
		
			if(p=='M')   //	Indicator on
			{	
			
				count=0;
				
				app_1 = EEPROM_read(0);    //Reading from internal EEPROM
				app_2 = EEPROM_read(1);
				app_3 = EEPROM_read(2);
				app_4 = EEPROM_read(3);
				app_5 = EEPROM_read(4);
				fan   = EEPROM_read(5);
				fan1   = EEPROM_read(6);
				
			}
			
			
			if(p=='F')		//FAN1 ON
			{
				fan  = EEPROM_read(7);
				EEPROM_write(5,fan);

			}
			
			if(p=='f')		//FAN1 OFF
			{ 
				fan  = 0xFF;
				EEPROM_write(5,fan);
				

			}
			
			
			if(p=='G')		//FAN2 ON						
			{
				fan1  = EEPROM_read(8);
				EEPROM_write(6,fan1);

			}
			
			if(p=='g')				//FAN2 OFF				
			{
				fan1  = 0xFF;
				EEPROM_write(6,fan1);

			}	
			
		
					
			if(p=='h')
			{
				fan=0xFF;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='i')
			{
				fan=0x01;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='j')
			{
				fan=0x02;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='k')
			{
				fan=0x03;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='l')
			{
				fan=0x04;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='n')
			{
				fan=0x05;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}

			if(p=='o')
			{
				fan=0x06;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
			if(p=='p')
			{
				fan=0x07;
				EEPROM_write(5,fan);
				EEPROM_write(7,fan);
			}
				
				
		
		
		
			if(p=='H')
			{
				fan1=0xFF;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
			
	
			if(p=='I')
			{
				fan1=0x01;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
			
	
			if(p=='J')
			{
				fan1=0x02;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
				
			if(p=='K')
			{
				fan1=0x03;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
				
			if(p=='L')
			{
				fan1=0x04;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
				
			if(p=='N')
			{
				fan1=0x05;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}

			if(p=='O')
			{
				fan1=0x06;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
				
			if(p=='P')
			{
				fan1=0x07;
				EEPROM_write(6,fan1);
				EEPROM_write(8,fan1);
			}
				
			
			
			
			
			
		    if(p=='Q')	//All on			
			{
				app_1=0;
				app_2=0;
				app_3=0;
				app_4=0;
				app_5=0;
				fan   = EEPROM_read(7);
				fan1   = EEPROM_read(8);
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);
				EEPROM_write(5,fan);
				EEPROM_write(6,fan1);
			}		
	
		
		    if(p=='q')		//All Off
			{	
				
				app_1=0xFF;
				app_2=0xFF;
				app_3=0xFF;
				app_4=0xFF;
				app_5=0xFF;
				fan=0xFF;
				fan1=0xFF;
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);	
				EEPROM_write(5,fan);
				EEPROM_write(6,fan1);
				
			}	

	
		
		
	
		
	if(RC5_NewCommandReceived(&command))
        {
            // Reset RC5 lib so the next command
            // can be decoded. This is a must! 
            RC5_Reset();
            
            // Toggle the LED on PB5 
           // PORTB ^= _BV(PB5);
            
            // Do something with the command 
             // Perhaps validate the start bits and output
             //it via UART... 
            if(RC5_GetStartBits(command) != 3)
            {
                // ERROR 
            }
			
			uint8_t cmd = RC5_GetCommandBits(command);
			if(command==14392)								//Switch 1
			{	
				app_1=0;
				sbi(PORTB,3);
				sbi(PORTC,3);
				EEPROM_write(0,app_1); //saving the state of appliance	
			}
			  else if(command==12344)
			{
				app_1=0xFF;
				cbi(PORTB,3);
				cbi(PORTC,3);
				EEPROM_write(0,app_1); //saving the state of appliance	
			}
			
		  else if(command==12301)							//Switch 2
			{
				app_2=0;
				sbi(PORTB,4);
				sbi(PORTC,4);
				EEPROM_write(1,app_2); //saving the state of appliance	
			}
			  else if(command==14349)
			{
				app_2=0xFF;
				cbi(PORTB,4);
				cbi(PORTC,4);
				EEPROM_write(1,app_2); //saving the state of appliance	
	
			}
			
		
		  else if(command==14337)							//Switch 3
			{
				app_3=0;
				sbi(PORTB,5);
				sbi(PORTC,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}
			  else if(command==12289)
			{
				app_3=0xFF;
				cbi(PORTB,5);
				cbi(PORTC,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}


		  else if(command==12321)							//Switch 4
			{
				app_4=0;
				sbi(PORTB,6);
				sbi(PORTC,6);
				EEPROM_write(3,app_4); //saving the state of appliance	
			}
			  else if(command==14369)
			{
				app_4=0xFF;
				cbi(PORTB,6);
				cbi(PORTC,6);
				EEPROM_write(3,app_4); //saving the state of appliance	

			}
			
			
			else if(command==14353)							//Switch 5
			{
				app_5=0;
				sbi(PORTB,7);
				sbi(PORTC,7);
				EEPROM_write(4,app_5); //saving the state of appliance	
			}
			  else if(command==12305)
			{
				app_5=0xFF;
				cbi(PORTB,7);
				cbi(PORTC,7);
				EEPROM_write(4,app_5); //saving the state of appliance	

			}
			
			  else if(command==14348)	// Indicator Off
			{	
				count=1;
				
			}
		
			  else if(command==12300)   //	Indicator on
			{	
			
				count=0;
				
				app_1 = EEPROM_read(0);    //Reading from internal EEPROM
				app_2 = EEPROM_read(1);
				app_3 = EEPROM_read(2);
				app_4 = EEPROM_read(3);
				app_5 = EEPROM_read(4);
				fan   = EEPROM_read(5);
				fan1   = EEPROM_read(6);
				
			}
			
				
			
			
			else if(command==12332)		//FAN1 ON
			{
				fan  = EEPROM_read(7);
				EEPROM_write(5,fan);

			}
			
			else if(command==14380)		//FAN1 OFF
			{ 
				fan  = 0xFF;
				EEPROM_write(5,fan);
				

			}
			
			
			else if(command==14345)		//FAN2 ON						
			{
				fan1  = EEPROM_read(8);
				EEPROM_write(6,fan1);

			}
			
			else if(command==12297)				//FAN2 OFF				
			{
				fan1  = 0xFF;
				EEPROM_write(6,fan1);

			}
			
			
			
			
			if((command==14382)||(command==12334))
			{
			if(cmd1==command)
				{
				goto l1;
				}
				
				speed++;	
				
		
			if(speed>=8)
				{
				speed=7;
				goto l1;
				}
				
						
				if(speed==0)
				{
				fan=0xFF;
				EEPROM_write(5,fan);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				}

				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				}
				
				value1=fan;
				EEPROM_write(7,value1);
			}	
			
			
			
			if((command==14377)||(command==12329))
			{
			if(cmd1==command)
				{
				goto l1;
				}
			if(speed<=0)
				{
				speed=0;
				goto l1;
				}
			if(speed>0)
			{
			speed--;	
			}
			
				if(speed==0)
				{
				fan=0xFF;
				EEPROM_write(5,fan);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				}
				
				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				}
				
				value1=fan;
				EEPROM_write(7,value1);
			}
			
			
			
			
			if((command==14342) || (command==12294))			
			{
			if(cmd1==command)
				{
				goto l1;
				}
				speed1++;	
						
				if(speed1>=8)
				{
				speed1=7;
				goto l1;
				}
				
				
				if(speed1==0)
				{
				fan1=0xFF;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==1)
				{
				fan1=0x01;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==2)
				{
				fan1=0x02;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==3)
				{
				fan1=0x03;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==4)
				{
				fan1=0x04;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==5)
				{
				fan1=0x05;
				EEPROM_write(6,fan1);
				}

				if(speed1==6)
				{
				fan1=0x06;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==7)
				{
				fan1=0x07;
				EEPROM_write(6,fan1);
				}
				value2=fan1;
				EEPROM_write(8,value2);
			}	
			
			
			
			if((command==14370) || (command==12322))			
			{
			if(cmd1==command)
				{
				goto l1;
				}
				else if(speed1<=0)
				{
				speed1=0;
				goto l1;
				}
				if(speed1>0)
				{
				speed1--;	
				}
			
				if(speed1==0)
				{
				fan1=0xFF;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==1)
				{
				fan1=0x01;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==2)
				{
				fan1=0x02;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==3)
				{
				fan1=0x03;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==4)
				{
				fan1=0x04;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==5)
				{
				fan1=0x05;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==6)
				{
				fan1=0x06;
				EEPROM_write(6,fan1);
				}
				
				if(speed1==7)
				{
				fan1=0x07;
				EEPROM_write(6,fan1);
				}
				value2=fan1;
				EEPROM_write(8,value2);
			}
			
			
			
			
			
			
			
			
		 if((command==14352) || (command==12304))	//All on			
			{
				app_1=0;
				app_2=0;
				app_3=0;
				app_4=0;
				app_5=0;
				fan   = EEPROM_read(7);
				fan1   = EEPROM_read(8);
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);
				EEPROM_write(5,fan);
				EEPROM_write(6,fan1);
			}		
	
		
		 if((command==14566) || (command==12518))		//All Off
			{	
				
				app_1=0xFF;
				app_2=0xFF;
				app_3=0xFF;
				app_4=0xFF;
				app_5=0xFF;
				fan=0xFF;
				fan1=0xFF;
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);	
				EEPROM_write(5,fan);
				EEPROM_write(6,fan1);
				
			}	

	
			
			cmd1=command;
			
			
			
		}
			
		
		
			if(fan==0xFF)
			{
			  speed=0;
				if(count==0)
				{
				 	sbi(PORTD,4);
				 	sbi(PORTD,5);
				   	sbi(PORTD,6);
					sbi(PORTD,7);
					sbi(PORTC,0);
					cbi(PORTC,1);
					sbi(PORTC,2);
				}
				else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}


			
			if(fan==0x01)
			{
			  speed=1;
				if(count==0)
				{
					sbi(PORTD,4);
					sbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}	
			}
			
			
			
			
			if(fan==0x02)
			{
			  speed=2;
				if(count==0)
				{
					cbi(PORTD,4);
					sbi(PORTD,5);
					sbi(PORTD,6);
					sbi(PORTD,7);
					sbi(PORTC,0);
					sbi(PORTC,1);
					cbi(PORTC,2);
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}
			
			
			
			
				
			if(fan==0x03)
			{
			  speed=3;
				if(count==0)
				{
					sbi(PORTD,4);
					sbi(PORTD,5);
					sbi(PORTD,6);
					sbi(PORTD,7);
					cbi(PORTC,0);
					sbi(PORTC,1);
					cbi(PORTC,2);	
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}	
				
				
				
			
			if(fan==0x04)
			{
			  speed=4;
				if(count==0)
				{
					sbi(PORTD,4);
					sbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					sbi(PORTC,1);
					sbi(PORTC,2);	
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}		

			
			if(fan==0x05)
			{
			  speed=5;
				if(count==0)
				{
					sbi(PORTD,4);
					cbi(PORTD,5);
					sbi(PORTD,6);
					sbi(PORTD,7);
					cbi(PORTC,0);
					sbi(PORTC,1);
					sbi(PORTC,2);
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}
		
			
			
			if(fan==0x06)
			{
			  speed=6;
				if(count==0)
				{
					sbi(PORTD,4);
					cbi(PORTD,5);
					sbi(PORTD,6);
					sbi(PORTD,7);
					sbi(PORTC,0);
					sbi(PORTC,1);
					sbi(PORTC,2);
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}
		
			
			if(fan==0x07)
			{
			  speed=7;
				if(count==0)
				{
					sbi(PORTD,4);
					sbi(PORTD,5);
					sbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			else if(count==1)
				{
					cbi(PORTD,4);
					cbi(PORTD,5);
					cbi(PORTD,6);
					cbi(PORTD,7);
					cbi(PORTC,0);
					cbi(PORTC,1);
					cbi(PORTC,2);
				}
			}
		
			
			
			
			
			
			if(fan1==0xFF)
			{
			  speed1=0;
				if(count==0)
				{
				 	sbi(PORTA,0);
				 	sbi(PORTA,2);
				   	sbi(PORTA,3);
					sbi(PORTA,4);
					sbi(PORTA,5);
					cbi(PORTA,6);
					sbi(PORTA,7);
				}
				else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);
				}
			}


			
			if(fan1==0x01)
			{
			  speed1=1;
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}	
			}
			
			
			
			
			if(fan1==0x02)
			{
			  speed1=2;
				if(count==0)
				{
					cbi(PORTA,0);
					sbi(PORTA,2);
					sbi(PORTA,3);
					sbi(PORTA,4);
					sbi(PORTA,5);
					sbi(PORTA,6);
					cbi(PORTA,7);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}
			
			
			
			
				
			if(fan1==0x03)
			{
			  speed1=3;
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTA,2);
					sbi(PORTA,3);
					sbi(PORTA,4);
					cbi(PORTA,5);
					sbi(PORTA,6);
					cbi(PORTA,7);	
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}	
				
				
				
			
			if(fan1==0x04)
			{
			  speed1=4;
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					sbi(PORTA,6);
					sbi(PORTA,7);	
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}		

			
			if(fan1==0x05)
			{
			  speed1=5;
				if(count==0)
				{
					sbi(PORTA,0);
					cbi(PORTA,2);
					sbi(PORTA,3);
					sbi(PORTA,4);
					cbi(PORTA,5);
					sbi(PORTA,6);
					sbi(PORTA,7);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}
		
			
			if(fan1==0x06)
			{
			  speed1=6;
				if(count==0)
				{
					sbi(PORTA,0);
					cbi(PORTA,2);
					sbi(PORTA,3);
					sbi(PORTA,4);
					sbi(PORTA,5);
					sbi(PORTA,6);
					sbi(PORTA,7);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}
			

			if(fan1==0x07)
			{
			  speed1=7;
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTA,2);
					sbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTA,2);
					cbi(PORTA,3);
					cbi(PORTA,4);
					cbi(PORTA,5);
					cbi(PORTA,6);
					cbi(PORTA,7);

				}
			}
		
			
			
			
			
			if(app_1==0)
			{
				sbi(PORTB,3);
					if(count==0)
					{
					sbi(PORTC,3);
					}
					else if(count==1)
					{
					cbi(PORTC,3);
					}
			}		
			else
			{
			cbi(PORTC,3);
			cbi(PORTB,3);
			}
			
			
			
			
			if(app_2==0)
			{
				sbi(PORTB,4);
					if(count==0)
					{
					sbi(PORTC,4);
					}
					else if(count==1)
					{
					cbi(PORTC,4);
					}
			}
			else
			{
			cbi(PORTC,4);
			cbi(PORTB,4);
			}
			
			
			if(app_3==0)
			{
				sbi(PORTB,5);
					if(count==0)
					{
					sbi(PORTC,5);
					}
					else if(count==1)
					{ 
					cbi(PORTC,5);
					}
			}
			else
			{
			cbi(PORTC,5);
			cbi(PORTB,5);
			}
			
			
			if(app_4==0)
			{
				sbi(PORTB,6);
					if(count==0)
					{
					sbi(PORTC,6);
					}
					else if(count==1)
					{
					cbi(PORTC,6);
					}
			}		
			else
			{
			cbi(PORTC,6);	
			cbi(PORTB,6);
			}
			
		
			
			if(app_5==0)
			{
				sbi(PORTB,7);
					if(count==0)
					{
					sbi(PORTC,7);
					}
					else
					{
					cbi(PORTC,7);
					}
			}
			else
			{
			cbi(PORTC,7);
			cbi(PORTB,7);
			}
					
		//	cmd=GetRemoteCmd(1);
		//	LCDWriteIntXY(0,1,command,5);
		//	_delay_ms(500);
			//Get Remote Command. Command is taken in last because the
			//	the past device status has to be recovered first!   
			
		
		
	}
   return 0;
}
