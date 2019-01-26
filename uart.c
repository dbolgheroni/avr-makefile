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
#include <stdio.h>

#define BAUD 9600
#include <util/setbaud.h>

int uart_putchar(char c, FILE *stream);
FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,
                _FDEV_SETUP_WRITE);

int uart_getchar(FILE *stream);
FILE mystdin = FDEV_SETUP_STREAM(NULL, uart_getchar,
                _FDEV_SETUP_READ);

int uart_putchar(char c, FILE *stream) {
        if (c == '\n')
                uart_putchar('\r', stream);
        loop_until_bit_is_set(UCSR0A, UDRE0);
        UDR0 = c;

        return 0;
}

int uart_getchar(FILE *stream) {
        loop_until_bit_is_set(UCSR0A, RXC0);
        return UDR0;
}

void uart_init(void) {
        UBRR0H = UBRRH_VALUE;
        UBRR0L = UBRRL_VALUE;

#if USE_2X
        UCSR0A |= (1 << U2X0);
#else
        UCSR0A &= ~(1 << U2X0);
#endif

        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8n1
        UCSR0B = (1 << RXEN0) | (1 << TXEN0); // enable RX and TX
}
