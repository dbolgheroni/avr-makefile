PROG = skel
MCU = atmega328p
BAUDRATE = 57600
PROGRAMMER = arduino
PORT = /dev/ttyU0
F_CPU = 16000000UL

.include "Makefile.avr"
