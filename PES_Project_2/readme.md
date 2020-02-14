# PES Project 2
----------------------------------------------------------------------------------------------------------------------------------------------------

## Authors - Pavan Shiralagi and Antara Prakash

## Contents

This repository contains C code for project 2 as described in Assignment 2 of the Spring 2020 PES class at CU Boulder 

The four modes it can be run in are - 
### FB_RUN - Blinks LED as required and changes color based on values read from capacitice slider
### FB_DEBUG - Same as FB_RUN with additional debug statements
### PC_RUN - Prints out states of LEDs and changes LED colors once every 3 cycles
### PC_DEBUG - Same as PC_RUN with additional debug statements

The project contains the following source files written by the authors -
Source:
	- 'PES_Project_2.c' : Main file containing main routine
		Please see the [PES_Project_2.c file](/source/PES_Project_2.c) for further details.
	- 'led.c' : File containing LED initializations
		Please see the [led.c file](/source/led.c) for further details.
	- 'cap_touch.c'	: File containing functions to initialize capacitive touch slider and read values 
		Please see the [cap_touch.c file](/source/cap_touch.c) for further details.
	- 'timer.c' : File containing function to wait in milliseconds for FB modes
		Please see the [timer.c file](/source/timer.c) for further details.

The following documentation is also available - 
- 'readme.md' : Overview file (This file)
doc:
	- 'initial_wbs.pdf' : Work breakdown structure before staring the project
		Please see the [initial_wbs.pdf file](/doc/initial_wbs.pdf) for further details.
	- 'final_wbs.pdf' : Work breakdown structure after project completion

Each source file has its own header file.

**Project Comments**

- Faced some issues creating the makefile to compile using gcc on MCUXpresso, figured out how to add 
  environment variables and configure parameters correctly.
- Capactive touch values are very unreliable.  Reading the value once every two seconds and added a large multiplier to try increasing accuracy.
- Difficulty including multiple compile files using gcc in MCUXpresso.

## Execution Notes

All modes can be executed from MCUXpresso using custom makefile
Platform - MCUXpresso

### For FB modes
Compiler used - arm-none-eabi-gcc
Debug statements viewed on Realterm. Baud rate - 115200

### For PC modes
Compiler used - gcc
MinGW is required to use gcc from Windows systems.  The environment vairable mus tbe added to the path and gcc can be verified on cmd line.
MinGW must also be added to the path in MCUXpresso.
An executable file is created in the debug folder and can then be run on command line.
The PC mode can also be run on Ubuntu using the `make VERSION=PC_RUN` or `make VERSION=PC_DEBUG`

**If facing problems while generating executable files, delete all contents of the debug folder and then re-build**

-----------------------------------------------------------------------------------------------------------------------------------------------------