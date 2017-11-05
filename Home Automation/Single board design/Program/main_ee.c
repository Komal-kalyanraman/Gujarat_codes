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

uint8_t app_1,app_2,app_3,app_4,app_5,fan,cmd=0,cnt=0,cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0,lan=0;

uint8_t speed=0,value,value1,value2;



int main()
{
	//uart_init(UART_BAUD_SELECT(9600,F_CPU)); //UART intialization
	
	int count=0,a;  
	
	
	sbi(DDRC,2);  //LED ARE CONNECTED HERE
	sbi(DDRC,1);
	sbi(DDRC,0);
	sbi(DDRD,5);
	sbi(DDRB,7);
	

	sbi(DDRB,0);	 //7-SEG
	sbi(DDRD,7);
	sbi(DDRD,6);
	sbi(DDRB,4);
	sbi(DDRB,2);
	sbi(DDRB,3);
	sbi(DDRB,1);
	

	sbi(DDRD,0); // OUTPUT PIN TRIAC
	sbi(DDRD,1);
	sbi(DDRD,3);
	sbi(DDRD,4);
	sbi(DDRB,6);
	
	
	sbi(DDRC,4); // OUTPUT PIN RELAY
	sbi(DDRC,3);
	sbi(DDRC,5);

	//Give Some Time for other hardware to start

	_delay_loop_2(0);

	RC5_Init();
	sei();
	
	app_1 = EEPROM_read(0);    //Reading from internal EEPROM
	app_2 = EEPROM_read(1);
	app_3 = EEPROM_read(2);
	app_4 = EEPROM_read(3);
	app_5 = EEPROM_read(4);
	fan   = EEPROM_read(5);
	count = EEPROM_read(7);
	
	
			if(app_1==0)
			{
				sbi(PORTD,0);
					if(count==0)
					{
					sbi(PORTC,2);
					}
					else if(count==1)
					{
					cbi(PORTC,2);
					}
			}		
			else
			{
			cbi(PORTC,2);
			cbi(PORTD,0);
			}
			
			if(app_2==0)
			{
				sbi(PORTD,1);
					if(count==0)
					{
					sbi(PORTC,1);
					}
					else if(count==1)
					{
					cbi(PORTC,1);
					}
			}
			else
			{
			cbi(PORTC,1);
			cbi(PORTD,1);
			}
			
			
			if(app_3==0)
			{
				sbi(PORTD,3);
					if(count==0)
					{
					sbi(PORTC,0);
					}
					else if(count==1)
					{ 
					cbi(PORTC,0);
					}
			}
			else
			{
			cbi(PORTC,0);
			cbi(PORTD,3);
			}
			
			
			if(app_4==0)
			{
				sbi(PORTD,4);
					if(count==0)
					{
					sbi(PORTD,5);
					}
					else if(count==1)
					{
					cbi(PORTD,5);
					}
			}		
			else
			{
			cbi(PORTD,5);	
			cbi(PORTD,4);
			}
			
		
			
			if(app_5==0)
			{
				sbi(PORTB,6);
					if(count==0)
					{
					sbi(PORTB,7);
					}
					else
					{
					cbi(PORTB,7);
					}
			}
			else
			{
			cbi(PORTB,7);
			cbi(PORTB,6);
			}
			
	
		if(fan==0xFF)
			{
				speed=0;
				cbi(PORTC,3);	//med
				cbi(PORTC,5);	//low
				cbi(PORTC,4);	//high
				_delay_ms(250);
				if(count==0)
				{
				 	sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					cbi(PORTB,2);
					sbi(PORTB,1);

				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			
			
			if(fan==0x01)
			{
				speed=1;
				sbi(PORTC,3);
				cbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					cbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}	
			}
			
			
			
			
			if(fan==0x02)
			{
				speed=2;
				cbi(PORTC,3);
				sbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					cbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					sbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			
			if(fan==0x03)
			{
				speed=3;
				cbi(PORTC,3);
				cbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					cbi(PORTB,1);	
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}	
			
			
			if(fan==0x04)
			{
				speed=4;
				sbi(PORTC,3);
				sbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					cbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);	
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}		
			
			if(fan==0x05)
			{
				speed=5;
				sbi(PORTC,3);
				cbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	cbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			if(fan==0x06)
			{
				speed=6;
				cbi(PORTC,3);
				sbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	cbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			if(fan==0x07)
			{
				speed=7;
				sbi(PORTC,3);
				sbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
	
	
	
	
	
	
	uint16_t command,cmd1,tog;
	while(1)
	{
	
		

l1:		
	if(RC5_NewCommandReceived(&command))
        {
         /* Reset RC5 lib so the next command
             * can be decoded. This is a must! */
l2:         RC5_Reset();
            
            /* Toggle the LED on PB5 */
           // PORTB ^= _BV(PB5);
            
            /* Do something with the command 
             * Perhaps validate the start bits and output
             * it via UART... */
				
            if(RC5_GetStartBits(command) != 3)
            {
                /* ERROR */
            }
			
			uint16_t cmd = RC5_GetCommandBits(command);
			uint16_t toggle = RC5_GetToggleBit(command);
			
			if(tog==toggle)
				{
				goto j1;
				}
			tog=toggle;
			
			
			if(command==14392)								//Switch 1
			{	
				app_1=0;
				sbi(PORTD,0);
				sbi(PORTC,2);
				EEPROM_write(0,app_1); //saving the state of appliance
				goto m8;
			}
			
			else if(command==12344)
			{
				app_1=0xFF;
				cbi(PORTD,0);
				cbi(PORTC,2);
				EEPROM_write(0,app_1); //saving the state of appliance
				goto m8;
			}
			
			else if(command==12301)							//Switch 2
			{
				app_2=0;
				sbi(PORTD,1);
				sbi(PORTC,1);
				EEPROM_write(1,app_2); //saving the state of appliance
				goto m8;	
			}
			
			else if(command==14349)
			{
				app_2=0xFF;
				cbi(PORTD,1);
				cbi(PORTC,1);
				EEPROM_write(1,app_2); //saving the state of appliance	
				goto m8;	
			}
			
		
			else if(command==14337)							//Switch 3
			{
				app_3=0;
				sbi(PORTD,3);
				sbi(PORTC,0);
				EEPROM_write(2,app_3); //saving the state of appliance	
				goto m8;			
			}
			
			else if(command==12289)
			{
				app_3=0xFF;
				cbi(PORTD,3);
				cbi(PORTC,0);
				EEPROM_write(2,app_3); //saving the state of appliance	
				goto m8;			
			}


		    else if(command==12321)							//Switch 4
			{
				app_4=0;
				sbi(PORTD,4);
				sbi(PORTD,5);
				EEPROM_write(3,app_4); //saving the state of appliance	
				goto m8;			
			}
			
			else if(command==14369)
			{
				app_4=0xFF;
				cbi(PORTD,4);
				cbi(PORTD,5);
				EEPROM_write(3,app_4); //saving the state of appliance	
				goto m8;
			}
			
			
			else if(command==14353)							//Switch 5
			{
				app_5=0;
				sbi(PORTB,6);
				sbi(PORTB,7);
				EEPROM_write(4,app_5); //saving the state of appliance	
				goto m8;			
			}
			
			else if(command==12305)
			{
				app_5=0xFF;
				cbi(PORTB,6);
				cbi(PORTB,7);
				EEPROM_write(4,app_5); //saving the state of appliance	
				goto m8;
			}
			
			else if(command==14348)	// Indicator Off
			{	
				count=1;
				EEPROM_write(7,count);
				goto l5;
				
			}
		
			else if(command==12300)   //	Indicator on
			{	
			
				count=0;
				EEPROM_write(7,count);
				app_1 = EEPROM_read(0);    //Reading from internal EEPROM
				app_2 = EEPROM_read(1);
				app_3 = EEPROM_read(2);
				app_4 = EEPROM_read(3);
				app_5 = EEPROM_read(4);
				fan   = EEPROM_read(5);
				goto l5;
			}
			
			else if(command==12332)		//FAN1 ON
			{
				fan  = EEPROM_read(6);
				EEPROM_write(5,fan);
				goto l5;
			}
			
			else if(command==14380)		//FAN1 OFF
			{ 
				fan  = 0xFF;
				EEPROM_write(5,fan);
				goto l5;
			}
	
			
			
			if((command==14382)||(command==12334))
			{
				//if(cmd1==command)
				//{
				//goto l1;
				//}
				
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
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						cbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
					
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
					if(count==0)
					{
						cbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						cbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						sbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
					if(count==0)
					{
						cbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);	
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						cbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}

				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						cbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				lan=1;
				value1=fan;
				EEPROM_write(6,value1);
			}	
			
			
			
			if((command==14377)||(command==12329))
			{
				//if(cmd1==command)
				//{
				//goto l1;
				//}
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
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						cbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
					
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
					if(count==0)
					{
						cbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						cbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						sbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
					if(count==0)
					{
						cbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);	
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						cbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						cbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}

				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						cbi(PORTD,7);
						sbi(PORTD,6);
						sbi(PORTB,4);
						sbi(PORTB,3);
						sbi(PORTB,2);
						sbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
					if(count==0)
					{
						sbi(PORTB,0);
						sbi(PORTD,7);
						sbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
					else if(count==1)
					{
						cbi(PORTB,0);
						cbi(PORTD,7);
						cbi(PORTD,6);
						cbi(PORTB,4);
						cbi(PORTB,3);
						cbi(PORTB,2);
						cbi(PORTB,1);
					}
				}
				lan=1;
				value1=fan;
				EEPROM_write(6,value1);
			}
			
				
				
			if((command==14352) || (command==12304))		//All on
			{
				app_1=0;
				app_2=0;
				app_3=0;
				app_4=0;
				app_5=0;
				fan   = EEPROM_read(6);
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);
				EEPROM_write(5,fan);
				goto l5;
			}		
	
			
			if((command==14566) || (command==12518))		//All Off
			{	
				
				app_1=0xFF;
				app_2=0xFF;
				app_3=0xFF;
				app_4=0xFF;
				app_5=0xFF;
				fan=0xFF;
				EEPROM_write(0,app_1);
				EEPROM_write(1,app_2);
				EEPROM_write(2,app_3);
				EEPROM_write(3,app_4);
				EEPROM_write(4,app_5);	
				EEPROM_write(5,fan);
				goto l5;
			}	
	
			j1:
			cmd1=command;
			  
			
			for(int x=0;x<101;x++)
			{
			if(RC5_NewCommandReceived(&command))
			{
			goto l2;
			}
			_delay_ms(10);
			}
			goto k1;
			
		l5:	
			if(app_1==0)
			{
				sbi(PORTD,0);
					if(count==0)
					{
					sbi(PORTC,2);
					}
					else if(count==1)
					{
					cbi(PORTC,2);
					}
			}		
			else
			{
			cbi(PORTC,2);
			cbi(PORTD,0);
			}
			
			if(app_2==0)
			{
				sbi(PORTD,1);
					if(count==0)
					{
					sbi(PORTC,1);
					}
					else if(count==1)
					{
					cbi(PORTC,1);
					}
			}
			else
			{
			cbi(PORTC,1);
			cbi(PORTD,1);
			}
			
			
			if(app_3==0)
			{
				sbi(PORTD,3);
					if(count==0)
					{
					sbi(PORTC,0);
					}
					else if(count==1)
					{ 
					cbi(PORTC,0);
					}
			}
			else
			{
			cbi(PORTC,0);
			cbi(PORTD,3);
			}
			
			
			if(app_4==0)
			{
				sbi(PORTD,4);
					if(count==0)
					{
					sbi(PORTD,5);
					}
					else if(count==1)
					{
					cbi(PORTD,5);
					}
			}		
			else
			{
			cbi(PORTD,5);	
			cbi(PORTD,4);
			}
			
		
			
			if(app_5==0)
			{
				sbi(PORTB,6);
					if(count==0)
					{
					sbi(PORTB,7);
					}
					else
					{
					cbi(PORTB,7);
					}
			}
			else
			{
			cbi(PORTB,7);
			cbi(PORTB,6);
			}
			
	
	k1:	
		if(fan==0xFF)
			{
				lan=0;
				speed=0;
				cbi(PORTC,3);	//med
				cbi(PORTC,5);	//low
				cbi(PORTC,4);	//high
				_delay_ms(250);
				if(count==0)
				{
				 	sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					cbi(PORTB,2);
					sbi(PORTB,1);

				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			
			
			if(fan==0x01)
			{
				lan=0;
				speed=1;
				sbi(PORTC,3);
				cbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					cbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}	
			}
			
			
			
			
			if(fan==0x02)
			{
				lan=0;
				speed=2;
				cbi(PORTC,3);
				sbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					cbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					sbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			
			if(fan==0x03)
			{
				lan=0;
				speed=3;
				cbi(PORTC,3);
				cbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					cbi(PORTB,1);	
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}	
			
			
			if(fan==0x04)
			{
				lan=0;
				speed=4;
				sbi(PORTC,3);
				sbi(PORTC,5);
				cbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					cbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);	
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}		
			
			if(fan==0x05)
			{
				lan=0;
				speed=5;
				sbi(PORTC,3);
				cbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	cbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					cbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			if(fan==0x06)
			{
			    lan=0;
				speed=6;
				cbi(PORTC,3);
				sbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	cbi(PORTD,7);
					sbi(PORTD,6);
					sbi(PORTB,4);
					sbi(PORTB,3);
					sbi(PORTB,2);
					sbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
			if(fan==0x07)
			{
				lan=0;
				speed=7;
				sbi(PORTC,3);
				sbi(PORTC,5);
				sbi(PORTC,4);
				_delay_ms(250);
				if(count==0)
				{
					sbi(PORTB,0);
				 	sbi(PORTD,7);
					sbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
				else if(count==1)
				{
					cbi(PORTB,0);
				 	cbi(PORTD,7);
					cbi(PORTD,6);
					cbi(PORTB,4);
					cbi(PORTB,3);
					cbi(PORTB,2);
					cbi(PORTB,1);
				}
			}
			
		}
			m8:
			if(lan==1)
			{			
			goto k1; 
			}	
		
	}
   return 0;
}
