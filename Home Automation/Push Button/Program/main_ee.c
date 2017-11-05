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
//#include <uart.c>
//#include <uart.h> 

#define FAN_CNTRL_PIN1	PINC
#define FAN_CNTRL_PIN2	PINA
#define SET_UP			2
#define SET_DOWN		2
#define FAN_ON_OFF		PINA
#define ON_OFF_FAN		1


#define SWITCH1_ON_OFF	PIND
#define S1				5
#define SWITCH2_ON_OFF	PIND
#define S2				6
#define SWITCH3_ON_OFF	PIND
#define S3				4
#define SWITCH4_ON_OFF	PIND
#define S4				7
#define SWITCH5_ON_OFF	PIND
#define S5				3




uint8_t app_1,app_2,app_3,app_4,app_5,fan,cmd=0,cnt=0,cnt1=0,cnt2=0,cnt3=0,cnt4=0,cnt5=0;

uint8_t speed=0,value,value1,value2;



int main()
{
	//uart_init(UART_BAUD_SELECT(9600,F_CPU)); //UART intialization
	
	int count=0,a;  
	
	cbi(DDRD,5);	// BUTTONS are connected here
	cbi(DDRD,6);
	cbi(DDRD,4);
	cbi(DDRD,7);
	cbi(DDRD,3);
	
	cbi(DDRA,1);
	cbi(DDRC,2);
	cbi(DDRA,2);
	

	sbi(PORTD,5);
	sbi(PORTD,6);
	sbi(PORTD,4);
	sbi(PORTD,7);
	sbi(PORTD,3);
	
	sbi(PORTA,1);
	sbi(PORTA,2);
	sbi(PORTC,2);
	

	sbi(DDRA,6);  //LED ARE CONNECTED HERE
	sbi(DDRA,7);
	sbi(DDRA,5);
	sbi(DDRA,3);
	sbi(DDRA,4);
	

	sbi(DDRC,6);	 //7-SEG
	sbi(DDRC,5);
	sbi(DDRC,4);
	sbi(DDRC,3);
	sbi(DDRC,1);
	sbi(DDRC,7);
	sbi(DDRA,0);
	

	sbi(DDRB,0); //OUTPUT PIN
	sbi(DDRB,1);
	sbi(DDRB,2);
	sbi(DDRB,3);
	sbi(DDRB,4);
	sbi(DDRB,5);
	sbi(DDRB,6);
	sbi(DDRB,7);



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
	//fan1   = EEPROM_read(6);
	while(1)
	{
	
		uint16_t command,cmd1;

l1:		if(!(FAN_CNTRL_PIN1 & (1<<SET_UP)))
		
		{
			
			speed++;	
				
				if(speed>=8)
				{
				speed=7;
				a=1;
				goto l1;
				}
				
				if(speed==0)
				{
				fan=0xFF;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				sbi(PORTB,2);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				_delay_ms(50);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				cbi(PORTB,2);
				}

				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				cbi(PORTB,2);
				}
				
				value1=fan;
				EEPROM_write(6,value1);
				
				_delay_ms(a);	
				while(!(FAN_CNTRL_PIN1 & (1<<SET_UP)))
				{
				_delay_ms(1);
				}
		}
		
		
		if(!(FAN_CNTRL_PIN2 & (1<<SET_DOWN)))
		{
				
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
				sbi(PORTB,1);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				sbi(PORTB,2);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				_delay_ms(50);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				cbi(PORTB,2);
				}
				
				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				cbi(PORTB,2);
				}
				
				value1=fan;
				EEPROM_write(6,value1);
				
				while(!(FAN_CNTRL_PIN2 & (1<<SET_DOWN)))
				{
				_delay_ms(1);
				}
		}
		
		
		
		if(!(FAN_ON_OFF & (1<<ON_OFF_FAN)))		//FAN1 OFF-ON
			{ 
				cnt++;
				if(cnt==1)
					{
					fan  = EEPROM_read(6);
					EEPROM_write(5,fan);	
					}
				if(cnt==2)
					{
					fan  = 0xFF;
					EEPROM_write(5,fan);
					cnt=0;
					}	
				
				//while(!(FAN_CNTRL_PIN2 & (1<<SET_DOWN)))
				while(!(FAN_ON_OFF & (1<<ON_OFF_FAN)))
					{
					_delay_ms(1);
					}
					
			}
		
		
		
		
		if(!(SWITCH1_ON_OFF & (1<<S1)))									//Switch 1
			{	
				cnt1++;
				if(cnt1==1)
					{
					app_1=0;
					cbi(PORTB,7);
					sbi(PORTA,6);
					EEPROM_write(0,app_1); //saving the state of appliance	
			        }
				if(cnt1==2)
					{
					app_1=0xFF;
					sbi(PORTB,7);
					cbi(PORTA,6);
					EEPROM_write(0,app_1); //saving the state of appliance	
					cnt1=0;	
					}
					
				while(!(SWITCH1_ON_OFF & (1<<S1)))	
					{
					_delay_ms(1);
					}
			}		
			
			
		if(!(SWITCH2_ON_OFF & (1<<S2)))									//Switch 2
			{	
				cnt2++;
				if(cnt2==1)
					{
					app_2=0;
					cbi(PORTB,6);
					sbi(PORTA,7);
					EEPROM_write(1,app_2); //saving the state of appliance	
					}
					
				if(cnt2==2)
					{
					app_2=0xFF;
					sbi(PORTB,6);
					cbi(PORTA,7);
					EEPROM_write(1,app_2); //saving the state of appliance
					cnt2=0;
					}
				
				while(!(SWITCH2_ON_OFF & (1<<S2)))									
					{	
					_delay_ms(1);
					}
			}		
			
		if(!(SWITCH3_ON_OFF & (1<<S3)))									//Switch 3
			{	
				cnt3++;
				if(cnt3==1)
					{
					app_3=0;
					cbi(PORTB,5);
					sbi(PORTA,5);
					EEPROM_write(2,app_3); //saving the state of appliance	
					}
				
				
				if(cnt3==2)
					{
					app_3=0xFF;
					sbi(PORTB,5);
					cbi(PORTA,5);
					EEPROM_write(2,app_3); //saving the state of appliance	
					cnt3=0;
		        	}
					
				while(!(SWITCH3_ON_OFF & (1<<S3)))									
					{	
					_delay_ms(1);
					}
			}

			
		if(!(SWITCH4_ON_OFF & (1<<S4)))									//Switch 4
			{	
				cnt4++;
				if(cnt4==1)
					{
					app_4=0;
					cbi(PORTB,4);
					sbi(PORTA,3);
					EEPROM_write(3,app_4); //saving the state of appliance	
					}
			    if(cnt4==2)
					{
					app_4=0xFF;
					sbi(PORTB,4);
					cbi(PORTA,3);
					EEPROM_write(3,app_4); //saving the state of appliance	
					cnt4=0;
					}
				while(!(SWITCH4_ON_OFF & (1<<S4)))									
					{	
					_delay_ms(1);
					}
			}		
			
			
		if(!(SWITCH5_ON_OFF & (1<<S5)))									//Switch 5
			{	
				cnt5++;
				if(cnt5==1)
					{
					app_5=0;
					cbi(PORTB,3);
					sbi(PORTA,4);
					EEPROM_write(4,app_5); //saving the state of appliance	
					}
			    if(cnt5==2)
					{
					app_5=0xFF;
					sbi(PORTB,3);
					cbi(PORTA,4);
					EEPROM_write(4,app_5); //saving the state of appliance	
					cnt5=0;
					}
				while(!(SWITCH5_ON_OFF & (1<<S5)))									
					{	
					_delay_ms(1);
					}
			}
		
		
	
		
		
	if(RC5_NewCommandReceived(&command))
        {
            /* Reset RC5 lib so the next command
             * can be decoded. This is a must! */
            RC5_Reset();
            
            /* Toggle the LED on PB5 */
           // PORTB ^= _BV(PB5);
            
            /* Do something with the command 
             * Perhaps validate the start bits and output
             * it via UART... */
            if(RC5_GetStartBits(command) != 3)
            {
                /* ERROR */
            }
			
			uint8_t cmd = RC5_GetCommandBits(command);
			if(command==14392)								//Switch 1
			{	
				app_1=0;
				cbi(PORTB,7);
				sbi(PORTA,6);
				EEPROM_write(0,app_1); //saving the state of appliance	
			}
			else if(command==12344)
			{
				app_1=0xFF;
				sbi(PORTB,7);
				cbi(PORTA,6);
				EEPROM_write(0,app_1); //saving the state of appliance	
			}
			
		  else if(command==12301)							//Switch 2
			{
				app_2=0;
				cbi(PORTB,6);
				sbi(PORTA,7);
				EEPROM_write(1,app_2); //saving the state of appliance	
			}
			  else if(command==14349)
			{
				app_2=0xFF;
				sbi(PORTB,6);
				cbi(PORTA,7);
				EEPROM_write(1,app_2); //saving the state of appliance	
	
			}
			
		
		  else if(command==14337)							//Switch 3
			{
				app_3=0;
				cbi(PORTB,5);
				sbi(PORTA,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}
			  else if(command==12289)
			{
				app_3=0xFF;
				sbi(PORTB,5);
				cbi(PORTA,5);
				EEPROM_write(2,app_3); //saving the state of appliance	
			}


		  else if(command==12321)							//Switch 4
			{
				app_4=0;
				cbi(PORTB,4);
				sbi(PORTA,3);
				EEPROM_write(3,app_4); //saving the state of appliance	
			}
			  else if(command==14369)
			{
				app_4=0xFF;
				sbi(PORTB,4);
				cbi(PORTA,3);
				EEPROM_write(3,app_4); //saving the state of appliance	

			}
			
			
			else if(command==14353)							//Switch 5
			{
				app_5=0;
				cbi(PORTB,3);
				sbi(PORTA,4);
				EEPROM_write(4,app_5); //saving the state of appliance	
			}
			  else if(command==12305)
			{
				app_5=0xFF;
				sbi(PORTB,3);
				cbi(PORTA,4);
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
				
			}
			
				
			
			
			else if(command==12332)		//FAN1 ON
			{
				fan  = EEPROM_read(6);
				EEPROM_write(5,fan);

			}
			
			else if(command==14380)		//FAN1 OFF
			{ 
				fan  = 0xFF;
				EEPROM_write(5,fan);
				

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
				sbi(PORTB,1);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				sbi(PORTB,2);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				_delay_ms(50);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				cbi(PORTB,2);
				}

				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				cbi(PORTB,2);
				}
				
				value1=fan;
				EEPROM_write(6,value1);
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
				sbi(PORTB,1);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==1)
				{
				fan=0x01;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==2)
				{
				fan=0x02;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				sbi(PORTB,2);
				}
				
				if(speed==3)
				{
				fan=0x03;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				sbi(PORTB,2);
				}
				
				if(speed==4)
				{
				fan=0x04;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				_delay_ms(50);
				}
				
				if(speed==5)
				{
				fan=0x05;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				cbi(PORTB,2);
				}
				
				if(speed==6)
				{
				fan=0x06;
				EEPROM_write(5,fan);
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				}
				
				if(speed==7)
				{
				fan=0x07;
				EEPROM_write(5,fan);
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				cbi(PORTB,2);
				}
				
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
				
			}	
	
			
			cmd1=command;
			
			
			
		}
			
			
			if(fan==0xFF)
			{
				speed=0;
				sbi(PORTB,1);
				sbi(PORTB,0);
				sbi(PORTB,2);
				if(count==0)
				{
				 	sbi(PORTA,0);
				 	sbi(PORTC,7);
				   	sbi(PORTC,1);
					sbi(PORTC,3);
					sbi(PORTC,4);
					cbi(PORTC,5);
					sbi(PORTC,6);

				}
				else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}
			
			
			
			if(fan==0x01)
			{
				speed=1;
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				sbi(PORTB,2);
				if(count==0)
				{
					cbi(PORTA,0);
					sbi(PORTC,7);
					sbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}	
			}
			
			
			
			
			if(fan==0x02)
			{
				speed=2;
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				sbi(PORTB,2);
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTC,7);
					cbi(PORTC,1);
					sbi(PORTC,3);
					sbi(PORTC,4);
					sbi(PORTC,5);
					cbi(PORTC,6);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}
			
			
			if(fan==0x03)
			{
				speed=3;
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				sbi(PORTB,2);
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTC,7);
					sbi(PORTC,1);
					sbi(PORTC,3);
					cbi(PORTC,4);
					sbi(PORTC,5);
					cbi(PORTC,6);	
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}	
			
			
			if(fan==0x04)
			{
				speed=4;
				sbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				_delay_ms(50);
				if(count==0)
				{
					cbi(PORTA,0);
					sbi(PORTC,7);
					sbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					sbi(PORTC,5);
					sbi(PORTC,6);	
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}		
			
			if(fan==0x05)
			{
				speed=5;
				cbi(PORTB,1);
				_delay_ms(50);
				sbi(PORTB,0);
				cbi(PORTB,2);
				if(count==0)
				{
					sbi(PORTA,0);
					cbi(PORTC,7);
					sbi(PORTC,1);
					sbi(PORTC,3);
					cbi(PORTC,4);
					sbi(PORTC,5);
					sbi(PORTC,6);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}
			
			if(fan==0x06)
			{
				speed=6;
				sbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				_delay_ms(50);
				cbi(PORTB,2);
				if(count==0)
				{
					sbi(PORTA,0);
					cbi(PORTC,7);
					sbi(PORTC,1);
					sbi(PORTC,3);
					sbi(PORTC,4);
					sbi(PORTC,5);
					sbi(PORTC,6);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}
			
			if(fan==0x07)
			{
				speed=7;
				cbi(PORTB,1);
				_delay_ms(50);
				cbi(PORTB,0);
				cbi(PORTB,2);
				if(count==0)
				{
					sbi(PORTA,0);
					sbi(PORTC,7);
					sbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			else if(count==1)
				{
					cbi(PORTA,0);
					cbi(PORTC,7);
					cbi(PORTC,1);
					cbi(PORTC,3);
					cbi(PORTC,4);
					cbi(PORTC,5);
					cbi(PORTC,6);
				}
			}
			
			if(app_1==0)
			{
				cbi(PORTB,7);
					if(count==0)
					{
					sbi(PORTA,6);
					}
					else if(count==1)
					{
					cbi(PORTA,6);
					}
			}		
			else
			{
			cbi(PORTA,6);
			sbi(PORTB,7);
			}
			
			if(app_2==0)
			{
				cbi(PORTB,6);
					if(count==0)
					{
					sbi(PORTA,7);
					}
					else if(count==1)
					{
					cbi(PORTA,7);
					}
			}
			else
			{
			cbi(PORTA,7);
			sbi(PORTB,6);
			}
			
			
			if(app_3==0)
			{
				cbi(PORTB,5);
					if(count==0)
					{
					sbi(PORTA,5);
					}
					else if(count==1)
					{ 
					cbi(PORTA,5);
					}
			}
			else
			{
			cbi(PORTA,5);
			sbi(PORTB,5);
			}
			
			
			if(app_4==0)
			{
				cbi(PORTB,4);
					if(count==0)
					{
					sbi(PORTA,3);
					}
					else if(count==1)
					{
					cbi(PORTA,3);
					}
			}		
			else
			{
			cbi(PORTA,3);	
			sbi(PORTB,4);
			}
			
		
			
			if(app_5==0)
			{
				cbi(PORTB,3);
					if(count==0)
					{
					sbi(PORTA,4);
					}
					else
					{
					cbi(PORTA,4);
					}
			}
			else
			{
			cbi(PORTA,4);
			sbi(PORTB,3);
			}
			
			
			
				
		//	cmd=GetRemoteCmd(1);
		//	LCDWriteIntXY(0,1,command,5);
		//	_delay_ms(500);
			/*Get Remote Command. Command is taken in last because the
				the past device status has to be recovered first!   
			*/
		
		
	}
   return 0;
}
