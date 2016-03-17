#include "utils.h"
#include <avr/io.h>
#include <util/delay.h>

void pin_mode_out(byte pin) {
	DDRB |= (1 << pin);
}

void pin_mode_in(byte pin) {
	DDRB &= ~(1 << pin);
}

void pin_out_high(byte pin) {
	PORTB |= (1 << pin);
}

void pin_out_low(byte pin) {
	PORTB &= ~(1 << pin);
}

bool pin_in(byte pin) {
	return PINB & (1 << pin);
}


int analog_read() {
	//set ADSC pin to 1 in order to start reading the AIN value
	ADCSRA |= _BV(ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);
	int result = ADCL; // ADCL has to be read first
	result = ADCH << 8 | result;
	return result;
}

void flash(byte pin, byte count) {
	for (byte i = 0; i < count; ++i) {
		pin_out_high(pin);
		_delay_ms(200);
		pin_out_low(pin);
		_delay_ms(200);
	}
	_delay_ms(500);
}

void debug_out(byte pin, int value) {
	byte digits[6] = {0};
	byte counter = 0;

	while (value > 0 && counter < sizeof digits) {
		int digit = value % 10;
		digit += 1;	
		digits[counter++] = digit; 
		value /= 10; 
	}   
	// Output it backwards
	while (--counter >= 0) {
		flash(pin, digits[counter]);
		if (!counter) break;
	}
	_delay_ms(1500);
}
