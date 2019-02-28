# avr-makefile
BSD Makefile to compile AVR programs using avr-gcc + avr-libc.

## Motivation
The `devel/arduino` port used to use a simple, easy-to-adapt BSD Makefile to compile Arduino projects, until it was replaced by [Arduino-Makefile](https://github.com/sudar/Arduino-Makefile).

This project attempts to do the same, but compiling "pure"-C AVR code based on avr-libc.

## Goals
- opinionated, assume options, but easily modifiable
- BSD-make specific
  - don't work with GNU make
  - on Arch, should work with *community/bmake*
- don't try to work on every platform without changes
  - so far, this works great in OpenBSD with `devel/avr-libc` installed (it will install `devel/avr-gcc` as a dependency)
  
## See also
The [arm-makefile](https://github.com/dbolgheroni/arm-makefile) has the same goals but for the 32-bit STM32F1 microcontrollers based on the Cortex-M3 core.
