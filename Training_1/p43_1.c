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
	DDRB = 0;
	DDRB |= ( 1 << 0 );
	
	DDRA = ( 1 << 8 ) - 1; // 255
	DDRA &= ~( 1 << 6 );
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
	if ((PINA & (1 << 6)) == 0)
		return 1;
	return 0;
}

int main(void)
{
	setup();
    while (1) 
    {
		if ( button_pressed() )
		{
			_delay_ms ( BUTTON_DELAY_MS );
			if ( button_pressed() )
			{
				while ( button_pressed() );
				led_toogle();
			}
		}
    }
}
