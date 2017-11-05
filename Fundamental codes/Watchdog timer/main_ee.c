#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <compat/deprecated.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/wdt.h>
/*
void WDT_Init(void)
{
//disable interrupts
cli();
//reset watchdog
wdt_reset();
//set up WDT interrupt
WDTCR = (1<<WDCE)|(1<<WDE);
//Start watchdog timer with 2s prescaller
WDTCR = (1<<WDIE)|(1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
//Enable global interrupts
sei();
}
*/

int main()
{
	wdt_disable();
	
	wdt_enable(7);
	
	sbi(DDRC,0); // OUTPUT PIN RELAY
	
	while(1)
	{
		wdt_disable();
		
		wdt_enable(7);
		
		sbi(PORTC,0);
		_delay_ms(5000);
		
		cbi(PORTC,0);
		_delay_ms(5000);
	}
    wdt_reset();
	
	//sbi(PORTC,0);
	//_delay_ms(100);
	
	//cbi(PORTC,0);
	//_delay_ms(100);
	
	return 0;
	
    
}
