#pragma once

#ifndef F_CPU
#error F_CPU is needed for correct delays
#endif

#include "types.h"

void pin_mode_out(byte pin);
void pin_mode_in(byte pin);
void pin_out_high(byte pin);
void pin_out_low(byte pin);

int analog_read();

void flash(byte pin, byte value);
void debug_out(byte pin, int value);
