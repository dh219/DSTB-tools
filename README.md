# DSTB-tools

Tools for use with David's ST Booster (DSTB)

This project links to LibCMini (https://github.com/freemint/libcmini) by default, but may be compiled with the standard GCC C library.

## SDRAM commands

Of these programs should be placed in the AUTO folder, although they may be run from the desktop if circumstances demand.

Only one should be used at a time and once one is run it, or the other, will not run again until reset.

### DSTB1_RAM

This program will allocate an FRB, enable the SDRAM on DSTB1 and declare the new memory to TOS.

### DSTB1_ROM

This is as DSTB1_RAM above but also copies the ROM from 0xE00000 into SDRAM for fast access by the CPU. This is broadly similar to what MAPROM does for 68030s.

## Speed commands

These programs may be run from the auto folder or run from the desktop. They may be run multiple times and in combination to dynamically change the acceleration settings of DSTB1.

### DSTB1_16

This small program simply switches the DSTB1 into 16.5MHz mode. This is the default.

### DSTB1_8

As DSTB1_16 but prevents DSTB1 accelerating the CPU. The motherboard 8MHz clock will be followed.


##### Copyright 2022 D Henderson & others.

Released under the terms of the GPLv2.
