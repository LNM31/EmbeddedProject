#define F_CPU 14745600UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "led.h"
#include "timer.h"
#include "7_segment_display.h"
#include "UART.h"

#include <string.h>

#define MY_UBRR 7

#define ADC_NR_BITS 10
#define AVCC_VALUE 5

#define STRING_LIMIT 32

void setup()
{
	DDRA = 0; // set PORTA as input
	
	ADCSRA |= ( 1 << ADEN ); // enable ADC
	
	// set ADC Prescaler Select bits // prescaler == 1 << ADPS
	// just in case 0 is not default
	// ADCSRA = ADCSRA & ( ~ ( 1 << ADPS2 ) ) | ( 1 << ADPS1 ) | ( 1 << ADPS0 );
	
	ADCSRA = ADCSRA | ( 1 << ADPS1 ) | ( 1 << ADPS0 );
	
	UART_init();
}

uint16_t read_sample ( uint8_t read_port )
{
	// pentru single input, porturile
	// ADMUX ar trebui sa ramana pe 0 pentru a selecta ADC0 ( PORTA0 ) ca single input
	
	ADMUX |= read_port;
	
	// ADMUX ar trebui sa fie pe 01 pentru REFS1:0 si pe 0 pentru ADLAR
	// REFS1:0 == 01 <=> U de referinta la AVCC ( pin 30 ), cu capacitor la AREF ( pin 32 )
	
	ADCSRA |= ( 1 << ADSC ); // start conversion // revine pe 0 din hardware
	
	while ( ( ADCSRA >> ADSC ) & 1 ); // wait for conversion to finish
	
	return ADCL | ( ADCH << 8 ); // combine result registers
}

int main ( void )
{
	setup();
	
	char str[STRING_LIMIT];
	int flag;
	
	while ( 1 )
	{
		uint16_t sample = read_sample ( 0 );
		uint32_t tensiune_mV = sample * AVCC_VALUE / ( ( 1 << ADC_NR_BITS ) - 1 );
		
		flag = sprintf ( str, "Voltage = %u mV\r\n", tensiune_mV );
		
		if ( flag > 0 )
			string_transmission ( str );
		
		_delay_ms ( 1000 );
	}
}