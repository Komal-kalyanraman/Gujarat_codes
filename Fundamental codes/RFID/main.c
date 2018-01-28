
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>

#include <lib_uart.c>
#include <lib_uart.h> 
	
void main()
{
	unsigned char RFID[15]={0};
	int i = 0;
	unsigned char tmphead = 0;
  
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();

	while(1)
	{	
	
        //tmphead = (UART_RxHead) & UART_RX_BUFFER_MASK;
        if(UART_RxHead == 13)
		{
		for(i = 0;i<10;i++)
		{
			RFID[i]=uart_getc(); 
		}
		    uart_puts(RFID);
			uart_puts("\n");
			uart_puts("\r");
//			RFID[15]={0};
			//_delay_ms(20);
			clearBuffer();
		}
		
		
	}  
}
