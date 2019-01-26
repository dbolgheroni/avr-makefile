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

int led_count = 0;

/**** timer0 ****/
void timer0_stop() {
        TCCR0B &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
}

void timer0_init() {
        /* enable timer/counter overflow interrupt */
        TIMSK0 |= _BV(TOIE0);

        /* set the timer/counter to zero */
        TCNT0 = 0;
        
        /* enable interrupts */
        sei();
}

void timer0_start() {
        /* set Clock Select bits to clkio/1024, start counter */
        TCCR0B |= _BV(CS02) | _BV(CS00);
}

/**** timer1 ****/
void timer1_stop() {
        TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
}

void timer1_init() {
        /* enable timer interrupt on Compare Buffer A */
        TIMSK1 |= _BV(OCIE1A); 

        /* set timer/counter Mode of Operation to CTC */
        TCCR1B |= _BV(WGM12);

        /* set the timer/counter to zero */
        TCNT1 = 0;

        /* 1000 ms at 16 MHz with prescaler /1024 */
        OCR1A = 15624;

        /* enable interrupts */
        sei();
}

void timer1_start() {
        /* set Clock Select bits to clkio/1024, start counter */
        TCCR1B |= _BV(CS12) | _BV(CS10);
}

/**** interrupts handlers ****/
ISR(TIMER0_OVF_vect) {
        ++led_count;

        if (led_count > 5) {
                PORTB &= ~_BV(PORTB5);
                timer0_stop();
                led_count = 0;
        }
}

ISR(TIMER1_COMPA_vect) {
        /* set MOSI and SCK to output */
        DDRB = _BV(DDB3) | _BV(DDB5);

        timer0_start();
        PORTB |= _BV(PORTB5);

}
