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

#define BUTTON_DELAY_MS 1


void setup()
{
	DDRB = (1 << 8) - 1; // 255
	
	PORTB = 1;
	
	//DDRB |= ( 1 << 0 );
	
	DDRA = ( 1 << 8 ) - 1; // 255
	DDRA = DDRA << 2;
}

void led_on()
{
	PORTB |= ( 1 << 0 );
}

void led_off()
{
	PORTB &= ~( 1 << 0 );
}

void led_toogle()
{
	if ((PORTB & (1 << 0)) == 0)
	{
		led_on();
		return;
	}
	led_off();
}

int button_pressed()
{
	if ((PINA & (1 << 0)) == 0)
		return -1;
	if ((PINA & (1 << 1)) == 0)
		return 1;
	return 0;
}

void led_perm ( int rotation )
{
	if ( rotation == -1 )
		PORTB = ( uint8_t ) ( PORTB >> 1 );
	else
		PORTB = ( uint8_t ) ( PORTB << 1 );
		
	if ( PORTB ) return;
	
	if ( rotation == -1 )
		PORTB |= ( 1 << 7 );
	else
		PORTB = 1;
}

int main(void)
{
	setup();
	int button;
    while (1) 
    {
		if ( button_pressed() )
		{
			_delay_ms ( BUTTON_DELAY_MS );
			if ( button_pressed() )
			{
				button = button_pressed();
				while ( button_pressed() );
				// led_toogle();
				led_perm ( button );
			}
		}
    }
}