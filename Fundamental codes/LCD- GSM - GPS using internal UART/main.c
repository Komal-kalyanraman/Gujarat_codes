
// IN THIS PROJECT THE ULTRASONIC MODULE DETECTS AN OBSTRUCLE AND GIVES A BUZZER SOUND TO ALERT THE USER
// A BUTTON ON STICK IF PRESSED SENDS THE GPS CO-ORDINATES THROUGH THE GSM SIM 900 MODULE

#define F_CPU 8000000UL

////// IN THIS PROJECT INITIALLY UART HEADER WAS NOT WORKING, SO INITIATED ALL REGISTERS OF UART IN THIS PROGRAM //////
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <compat/deprecated.h>
#include<avr/io.h>
#include<util/delay.h>

#include <lcd.c>
#include <lcd.h> 

////////////////////////////////////// ULTRASONIC MODULE BEGINS /////////////////////////////////////////


#define US_PORT PORTA
#define US_PIN PINA
#define US_DDR  DDRA
#define US_TRIG PA5
#define US_ECHO PA6

int distance;
//Calculating width of high pulse in micro second.
#define US_Time_out  -12
#define US_NO_OBSTACLE -13

void US_init();
void US_trig();

void US_init()
{
 US_DDR|=(1<<US_TRIG);
}

void US_trig()
{
 //Send a 10uS pulse on trigger line
 
 US_PORT|=(1<<US_TRIG); //high
 
 _delay_us(15);    //wait 15uS
 
 US_PORT&=~(1<<US_TRIG); //low

}

uint16_t pulse_width()
{

 uint32_t i,result;      // Value goes from 0 to 65536.

 //Wait for the rising edge
 for(i=0;i<600000;i++)
 {
  if(!(US_PIN & (1<<US_ECHO)))
   continue;      //Line is still low, so wait
  else
   break;       //High edge detected, so break.
 }

 if(i==600000)
  return US_Time_out;     // No Reply found from US sensor, time lapsed
 
 //High Edge Found


 //Setup Timer1
 TCCR1A=0X00;
 TCCR1B=(1<<CS11);      //Prescaler = Fcpu/8
 TCNT1=0x00;        //Again initialising the counter

 //Counting the width of pulse.
 
 //Now wait for the falling edge
 for(i=0;i<600000;i++)
 {
  if(US_PIN & (1<<US_ECHO))
  {
   if(TCNT1 > 60000) break; else continue;
  }
  else
   break;
 }

 if(i==600000)
  return US_NO_OBSTACLE; //Indicates time out

 //Falling edge found

 result=TCNT1;

 //Stop Timer
 TCCR1B=0x00;

 if(result > 60000)
  return US_NO_OBSTACLE; //No obstacle
 else
  return (result>>1);
}

/////////////////////////////// ULTRASNIC MDULE ENDS /////////////////////////////////////////////////

/////// NOTE: ULTRASONIC USES TIMER 1, SO DON'T CONNECT THE ENABLE PINS OF L293 TO PD4 7 PD5 /////////


void usart_init();
unsigned int usart_getch();

unsigned char i,buffer[50];
unsigned int value,card[70];

int main(void)
{	
	uint16_t r;
	
	US_init();							///// INITIALIZING ULTRASONIC IS MOST IMPORTANT //////////
	
	//Set io port direction of sensor
	sbi(DDRC,1);						// BUZZER 
	sbi(DDRC,2);
	sbi(DDRA,7);						// LED FOR INDICATION IS BUTTON IS PRESSED TO SEND SMS
	
	cbi(DDRC,0);						// SWITCH TO SEND SMS
	
	usart_init();		// initialization of USART
	
	while(1)
	{		
	
	US_trig();

	//Measure the width of pulse
	r=pulse_width();

	//Handle Errors
	if(r==US_Time_out)
	{
	//	lcd_clrscr();
	//	lcd_gotoxy(1,1);
	//	lcd_puts("Error !");
	}
	
	else if(r==US_NO_OBSTACLE)
	{
	//	lcd_clrscr();
	//	lcd_gotoxy(1,1);
	//	lcd_puts("Clear !");
	}
	
	else
	{
	//	lcd_clrscr();
	//	lcd_gotoxy(1,1); 
		
		distance=((r*2)/77.0); 			////Convert to cm
		
	//	itoa(distance,buffer,10);
	//	lcd_puts(buffer);
	//	lcd_puts(" cm");
		
		_delay_ms(100);
	  
		
		
		if(distance<50)
		{
			sbi(PORTC,1);
		}
		else
		{
			cbi(PORTC,1);
		}
	}
	  
		card[0]= usart_getch();
		
		if(card[0]=='$')
			{
				card[1]= usart_getch();
				if(card[1]=='G')
				{
					card[2]= usart_getch();
					if(card[2]=='P')
					{
						card[3]= usart_getch();
						if(card[3]=='G')
						{
							card[4]= usart_getch();
							if(card[4]=='G')
							{
								card[5]= usart_getch();
								if(card[5]=='A')
								{
									card[6]= usart_getch();
									if(card[6]==',')
									{
										getcard_id();      // Function to get data from serial port
										
										
										
									if(bit_is_set(PINC,0))				
										{
											sbi(PORTA,7);
											uart_tx('A');
											uart_tx('T');
											uart_tx('\r');
											uart_tx('\n'); // Transmit AT to the module  GSM Modem sends
											_delay_ms(200);
											
											uart_tx('A');
											uart_tx('T');
											uart_tx('E');
											uart_tx('0');
											uart_tx('\r');
											uart_tx('\n'); // Transmit AT to the module  GSM Modem sends
											_delay_ms(200);
											
											uart_tx('A');
											uart_tx('T');
											uart_tx('+');
											uart_tx('C');
											uart_tx('M');
											uart_tx('G');
											uart_tx('F');
											uart_tx('=');
											uart_tx('1');
											uart_tx('\r');
											uart_tx('\n'); // Transmit AT to the module  GSM Modem sends
											_delay_ms(200);
											
											uart_tx('A');
											uart_tx('T');
											uart_tx('+');
											uart_tx('C');
											uart_tx('S');
											uart_tx('C');
											uart_tx('S');
											uart_tx('=');
											uart_tx('\"');
											uart_tx('G');
											uart_tx('S');
											uart_tx('M');
											uart_tx('\"');
											uart_tx('\r');
											uart_tx('\n'); // Transmit AT to the module  GSM Modem sends
											_delay_ms(200);
											
											uart_tx('A');
											uart_tx('T');
											uart_tx('+');
											uart_tx('C');
											uart_tx('M');
											uart_tx('G');
											uart_tx('S');
											uart_tx('=');
											uart_tx('\"');
											uart_tx('+');
											uart_tx('9');
											uart_tx('1');
											uart_tx('9');
											uart_tx('7');
											uart_tx('2');
											uart_tx('7');
											uart_tx('6');
											uart_tx('5');
											uart_tx('6');
											uart_tx('6');
											uart_tx('8');
											uart_tx('4');
											uart_tx('\"');
											uart_tx('\r');
											uart_tx('\n'); // Transmit AT to the module  GSM Modem sends
											_delay_ms(200);
											
											uart_tx('L');
											uart_tx('A');
											uart_tx('T');
											uart_tx('I');
											uart_tx('T');
											uart_tx('U');
											uart_tx('D');
											uart_tx('E');
											uart_tx(':');
											uart_tx('-');
											
											uart_tx(card[18]);
											uart_tx(card[19]);
											uart_tx(card[20]);
											uart_tx(card[21]);
											uart_tx(card[22]);
											uart_tx(card[23]);
											uart_tx(card[24]);
											uart_tx(card[25]);
											uart_tx(card[26]);
											//uart_tx(card[27]);
											uart_tx(card[28]);
											uart_tx('\r');
											uart_tx('\n');
											uart_tx('L');
											uart_tx('O');
											uart_tx('N');
											uart_tx('G');
											uart_tx('I');
											uart_tx('T');
											uart_tx('U');
											uart_tx('D');
											uart_tx('E');
											uart_tx(':');
											uart_tx('-');
											uart_tx(card[30]);
											uart_tx(card[31]);
											uart_tx(card[32]);
											uart_tx(card[33]);
											uart_tx(card[34]);
											uart_tx(card[35]);
											uart_tx(card[36]);
											uart_tx(card[37]);
											uart_tx(card[38]);
											uart_tx(card[39]);
											uart_tx(card[41]); 			// Input SMS Data
										    uart_tx(0x1a); 				// TO SEND SMS ctrl+z SHOULD BE GIVEN WHOSE HEX VALUE IS 0X1a
											
										}		
										
										else
										{
											cbi(PORTA,7);				// SWITCH OFF LED
										}		
										
										
										}
									}

								}
								
							}
						}
					}
				} 
				
			
		
	}	
}


void getcard_id(void)     //Function to get data fron the GPS module
{             
    for(i=7;i<71;i++)
    {
        card[i]= usart_getch();  // reading the gps values after "$GPGGA,"
    }

    return;
}

void LCD_display(void)  //Function for displaying ID no. on LCD
{
	
	lcd_clrscr();
	lcd_command(0x80);                               // ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
    
	for(i=18;i<29;i++)
    {
        lcd_data(card[i]);         // display card value byte by byte
    }
	
	lcd_command(0xC0);
	
	for(i=30;i<42;i++)
    {
        lcd_data(card[i]);         // display card value byte by byte
    }
	
	_delay_ms(500);
	lcd_command(0x01);
    return;
}



void usart_init()
{
    UCSRB |= (1 << RXEN) | (1 << TXEN);   // Turn on the transmission and reception circuitry
    UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1);

											// Use 8-bit character sizes

    UBRRL = BAUD_PRESCALE;          // Load lower 8-bits of the baud rate value..
                                    // into the low byte of the UBRR register
    UBRRH = (BAUD_PRESCALE >> 8);  // Load upper 8-bits of the baud rate value..
                                    // into the high byte of the UBRR register
}

unsigned int usart_getch()
{
    while ((UCSRA & (1 << RXC)) == 0); // Do nothing until data have been received..
                                        // and is ready to be read from UDR
    return(UDR); // return the byte
}




void uart_tx(int txdata)
{

	while(!(UCSRA & (1<<UDRE)))
	{
	}

	UDR=txdata;
	_delay_ms(3);
	UCSRA=(0<<UDRE);//for accessing USCRA register
}

