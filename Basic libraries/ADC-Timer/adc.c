#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>

#include "lib_uart.c"
#include "lib_uart.h" 

#include "lib_adc.c"

unsigned int a=0;

void main()
{
	unsigned char str[10]={0};
	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();

	while(1)
	{
		a=readADC_10bit(1);

		itoa(a,str,10);
		
		uart_puts(str);
		uart_puts("\n");
		uart_puts("\r");
		_delay_ms(50);
	}
}
