#pragma once

#ifndef F_CPU
#error F_CPU is needed for correct delays
#endif

#include "types.h"

void pin_mode_out(byte pin);
void pin_mode_in(byte pin);
void pin_out_high(byte pin);
void pin_out_low(byte pin);

void setup_pwm_pb1();
void pin_pwm_pb1(byte value);

int analog_read();
void enable_interrupt_on(byte interrupt);

void flash(byte pin, byte value);
void debug_out(byte pin, int value);
