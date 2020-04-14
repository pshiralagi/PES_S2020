# PES Project 5
----------------------------------------------------------------------------------------------------------------------------------------------------

## Authors - Pavan Shiralagi and Antara Prakash

## Contents

This repository contains C code for project 5 as described in Assignment 5 of the Spring 2020 PES class at CU Boulder

**Important Notes**
1. Oscilloscope captures were not taken due to lack of access to equipment
2. Application mode dumps characters and their counts once 10 values are added to the buffer. This count keeps increasing until the device is reset or session is ended
3. Special characters are handled in all modes
4. Implemented `bufferExtendFunction` if circular buffer is full for extra credit. Function replaces `bufferAdd`. Tested using unitTests.
5. Baud rate is set to **115200**


it can be viewed on Drive [Demo.mp4](https://drive.google.com/drive/folders/1Vx6lowz5C3nJvHKWkffDN4oPMSB9GWGV?usp=sharing "Demo Video link")
FMEA is available in the [FMEA.pdf file](./doc/FMEA.pdf)

The three primary modes it can be run in are - 
### NORMAL_MODE - Only basic UART prints based on APPLICATION_MODE or ECHO_MODE which are also selected in 'general.h'
### DEBUG_MODE - Increased logging to help debug or better understand code flow
### TEST_MODE - Runs the C Unit Tests, displays detailed results
 and then ends in an infinite loop

Additionally, applcicationi mode or echo mode as described in assignment 5 can be set in 'general.h'
### APPLICATION_MODE - Displays the number of time each character is entered in a particular session
### ECHO_MODE - Echos the entered character

The mode can be selected in 'general.h' 
Please see the [general.h file](./source/general.h) for further details.

The project contains the following source files written by the authors -
- Source:
	- 'PES_project_5.c' : Main file containing main routine. 
Please see the [PES_project_5.c file](./source/PES_project_5.c) for further details.
	- 'led.c' : File containing LED initializations. 
Please see the [led.c file](./source/led.c) for further details.
	- 'cap_touch.c'	: File containing functions to initialize capacitive touch slider and read values. 
Please see the [cap_touch.c file](./source/cap_touch.c) for further details.
	- 'timer.c' : File containing function to wait in milliseconds for FB modes. 
Please see the [timer.c file](./source/timer.c) for further details.
	- 'buffer.c' : File containing circular buffer functions, includes extend if buffer is full. 
Please see the [buffer.c file](./source/buffer.c) for further details.
	- 'mode.c' : Functions to count characters for Application Mode. 
Please see the [mode.c file](./source/mode.c) for further details.
	- 'uart.c' : File containing UART functions for interrupt and polling modes. 
Please see the [uart.c file](./source/uart.c) for further details.
	- 'log.c' : File containing logging functions, added time stamp function and changed printf to uart tx function. 
Please see the [log.c file](./source/log.c) for further details.
	- 'UnitTest.c' : File containing unit tests for TEST_MODE. 
Please see the [UnitTest.c file](./source/UnitTest.c) for further details.

The following documentation is also available - 
- 'readme.md' : Overview file (This file)

Each source file has its own header file.

## Project Comments

- Combining the `extendBufferAdd` with `bufferAdd` creates problems because of the way `isBufferFull` works
  it is fine if used seperately though, or if `extendBufferAdd` is used before buffer is full
- Faced some problems with double pointers

## Execution Notes

The mode can be selected in 'general.h' 
Please see the [general.h file](./source/general.h) for further details.
The data can be read on a terminal emulator with a baud rate of 115200.


-----------------------------------------------------------------------------------------------------------------------------------------------------