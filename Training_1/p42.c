/*
 * GccApplication2.c
 *
 * Created: 11/27/2024 10:33:57 AM
 * Author : dspproject
 */ 
#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PERIOD_MS 500

void init_led()
{
	DDRB = 0;
	DDRB |= ( 1 << 0 );
}

void led_on()
{
	PORTB |= ( 1 << 0 );
}

void led_off()
{
	PORTB &= ~( 1 << 0 );
}

int main(void)
{
    /* Replace with your application code */
	init_led();
    while (1) 
    {
		led_on();
		_delay_ms ( PERIOD_MS >> 1 );
		led_off();
		_delay_ms ( PERIOD_MS >> 1 );
    }
}