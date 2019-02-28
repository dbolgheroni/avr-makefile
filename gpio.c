/*
 * MIT License
 * 
 * Copyright (c) 2019, Daniel Bolgheroni.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <inttypes.h>
#include <avr/io.h>
#include "gpio.h"

/* deliberately make these function names non-generic */

/* arduino port 13 == avr PB5 */
void gpio_mode13() {
        DDRB |= _BV(DDB5); /* output */
}

void gpio_set13() {
        PORTB |= _BV(PORTB5);
}

void gpio_reset13() {
        PORTB &= ~_BV(PORTB5);
}

void gpio_toggle13() {
        PINB |= _BV(PINB5);
}

/* arduino port 10 == avr PB2 */
void gpio_mode10() {
        DDRB |= _BV(DDB2); /* output */
}

void gpio_set10() {
        PORTB |= _BV(PORTB2);
}

void gpio_reset10() {
        PORTB &= ~_BV(PORTB2);
}

void gpio_toggle10() {
        PINB |= _BV(PINB2);
}
