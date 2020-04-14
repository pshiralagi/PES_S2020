# PES Project 4
----------------------------------------------------------------------------------------------------------------------------------------------------

## Authors - Pavan Shiralagi and Antara Prakash

## Contents

This repository contains C code for project 4 as described in Assignment 4 of the Spring 2020 PES class at CU Boulder

**Important Notes**
1. The on board accelerometer has been used
2. SPI has been demonstrated using a loopback function
3. The POST checks for SPI connection (on board accelerometer cannot be disconnected)
4. 3 State Machines are present but state machine 3 just checks for SPI loopback and then makes a decision on the next state as 
described in the Assignment 4
5. We were unable to take scope shots of the i2c transactions as the pins are not accesible.  I have taken
a picture of the oscilloscope sending out an A (01000001). 
Please see the [A_SPI.jpg file](./doc/A_SPI.jpg)

it can be viewed on Drive [Demo.mp4](https://drive.google.com/drive/folders/16nQBLe9fvAS2s-ByGluDAprDUm0cBKMg?usp=sharing "Demo Video link")

Printed read out of accelerometer values are available in [accelerometer_values.pdf file](./doc/accelerometer_values.pdf)

I do not have any memory device I can connect to the oscilloscope at home. Please forgive the low image quality.

- fsm1 is the state driven state machine that uses a polling i2c method to obtain accelerometer values
- fsm2 is a table driven state machine that uses interrupt driven i2c
- fsm3 is a table driven state machine that tests SPI loopback and follows the decision making sequence 

The three modes it can be run in are - 
### STATUS - Minimal prints/logging to show working of state machines, i2c (interrupt and polling) and spi
### DEBUG_MODE - Increased logging to help debug or better understand code flow
### TEST_MODE - Runs the C Unit Tests, displays detailed results, changes LED to green if all pass and red if any fail
 and then ends in an infinite loop
The mode can be selected in 'general.h' 
Please see the [general.h file](./source/general.h) for further details.

The project contains the following source files written by the authors -
- Source:
	- 'PES_Project_4.c' : Main file containing main routine. 
Please see the [PES_Project_4.c file](./source/PES_Project_4.c) for further details.
	- 'led.c' : File containing LED initializations. 
Please see the [led.c file](./source/led.c) for further details.
	- 'cap_touch.c'	: File containing functions to initialize capacitive touch slider and read values. 
Please see the [cap_touch.c file](./source/cap_touch.c) for further details.
	- 'timer.c' : File containing function to wait in milliseconds for FB modes. 
Please see the [timer.c file](./source/timer.c) for further details.
	- 'acc.c' : File containing accelerometer functions. 
Please see the [acc.c file](./source/acc.c) for further details.
	- 'fsm.c' : File containing the 3 state machines as decribed in the Assignment 4 file. 
Please see the [fsm.c file](./source/fsm.c) for further details.
	- 'i2c.c' : File containing function to wait in milliseconds for FB modes. 
Please see the [i2c.c file](./source/timer.c) for further details.
	- 'log.c' : File containing logging functions. 
Please see the [log.c file](./source/log.c) for further details.
	- 'spi.c' : File containing SPI functions for loopback. 
Please see the [spi.c file](./source/spi.c) for further details.
	- 'UnitTest.c' : File containing unit tests for TEST_MODE. 
Please see the [UnitTest.c file](./source/UnitTest.c) for further details.

The following documentation is also available - 
- 'readme.md' : Overview file (This file)

Each source file has its own header file.

## Project Comments

- Some problems creating table driven state machine. The length of array of pointers is required to be declared explicitly.
	This could be because the memory defined gets formatted differently. 
- Capactive touch values are unreliable.
- Zero values from accelerometer occasionally

## Execution Notes

The mode can be selected in 'general.h' 
Please see the [general.h file](./source/general.h) for further details.
The data can be read on a terminal emulator with a baud rate of 115200.


-----------------------------------------------------------------------------------------------------------------------------------------------------