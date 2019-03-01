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

#include <util/delay.h>

#include "gpio.h"
#include "spi.h"
#include "mcp2515.h"

void _mcp2515_reset(void) {
    gpio_reset10();
    spi_send(MCP2515_RESET_INSTR);
    gpio_set10();
    _delay_ms(10);
}

uint8_t _mcp2515_read(uint8_t reg) {
    uint8_t val;
    gpio_reset10();
    spi_send(MCP2515_READ_INSTR);
    spi_send(reg);
    val = spi_send(0x00);
    gpio_set10();

    return val;
}

void _mcp2515_write(uint8_t reg, uint8_t value) {
    gpio_reset10();
    spi_send(MCP2515_WRITE_INSTR);
    spi_send(reg);
    spi_send(value);
    gpio_set10();
}

void _mcp2515_bit_modify(uint8_t reg, uint8_t mask, uint8_t data) {
    gpio_reset10();
    spi_send(MCP2515_BITMODIFY_INSTR);
    spi_send(reg);
    spi_send(mask);
    spi_send(data);
    gpio_set10();
}

void mcp2515_init() {
    spi_master_init();
    gpio_set10();

    /* enter Configuration Mode */
    _mcp2515_reset();

    /* 50 Kbit/s */
    _mcp2515_write(CNF1, 0x03);
    _mcp2515_write(CNF2, 0xb4);
    _mcp2515_write(CNF3, 0x06);

    /* enter Normal Mode */
    _mcp2515_bit_modify(CANCTRL0,
            CANCTRL_REQOP2 | CANCTRL_REQOP1 | CANCTRL_REQOP0, 0x00);
}

void mcp2515_putc(uint8_t c) {
    /* message id */
    _mcp2515_write(TXB0SIDH, 0x55);
    _mcp2515_write(TXB0SIDL, 0x40);

    /* load tx buffer */
    _mcp2515_write(TXB0D0, c);

    /* 1-byte data length */
    _mcp2515_write(TXB0DLC, 0x01);

    /* request to send TXB0 */
    _mcp2515_bit_modify(TXB0CTRL, TXB0CTRL_TXREQ, TXB0CTRL_TXREQ);
    
    /* clear TXB0 flag */
    _mcp2515_bit_modify(CANINTF, CANINTF_TX0IF, 0x00);
}
