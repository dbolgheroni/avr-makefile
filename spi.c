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
#include <avr/interrupt.h>

#include "gpio.h"

void spi_master_init() {
        /* disable interrupts */
        cli();

        /* set SS to output and set it to high */
        PORTB |= _BV(PORTB2);
        DDRB |= _BV(DDB2);

        /* spi master, fosc/64, spi irq enable, spi enable */
        SPCR |= _BV(MSTR) | _BV(SPR1);
        SPCR |= _BV(SPIE) | _BV(SPE);

        /* set MOSI and SCK to output */
        DDRB |= _BV(DDB3) | _BV(DDB5);

        /* enable interrupts */
        sei();
}

ISR (SPI_STC_vect) {

}

uint8_t spi_send(uint8_t data) {
        SPDR = data;
        asm volatile("nop");
        while (!(SPSR & _BV(SPIF))) ; // wait

        return SPDR;
}

void enable_ss() {
        PORTB &= ~(_BV(PORTB2));
}

void disable_ss() {
        PORTB |= _BV(PORTB2);
}
