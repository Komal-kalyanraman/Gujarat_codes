
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/interrupt.h>

#include "lib_uart.c"
#include "lib_uart.h" 

#include "lib_lcd.c"
#include "lib_lcd.h" 

unsigned int a=10;	
	
int main()
{
	
	unsigned char str[10]={0};
	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();

	lcd_init(LCD_DISP_ON);
	
	while(1)
	{
		
		lcd_clrscr();
		
		lcd_gotoxy(1,1);
		lcd_puts("Error !");
		
		lcd_gotoxy(8,1);
		lcd_puts("KOMAL");
		
		itoa(a,str,10);
		
		uart_puts(str);
		uart_puts("\n");
		uart_puts("\r");
		_delay_ms(50);
		
	}
	
}
