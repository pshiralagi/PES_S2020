# PES Project 6
----------------------------------------------------------------------------------------------------------------------------------------------------

## Authors - Pavan Shiralagi and Antara Prakash

## Contents

This repository contains C code for project 6 as described in Assignment 6 of the Spring 2020 PES class at CU Boulder

This project explores usage of DAC, ADC and DMA in a FreeRTOS environment.

**Important Notes**
1. Oscilloscope captures were not taken due to lack of access to equipment, instead the values were plotted in excel and a sine wave was seen
2. Baud rate is set to **115200**


Demo video for this project can be viewed on drivce at
Excel plot of sine wave is available at [WavePlotExcel.png file](./PES_project_6_1/doc/WavePlotExcel.png)

**This project consists of two seperate sub project files -**
1. PES_project_6_1 (./PES_project_6_1)
2. PES_Project_6_2 (./PES_Project_6_2)

The two primary modes each project can be run in are - 
### NORMAL_MODE - Only basic DAC/ADC prints to show that the program is working. Can be selected in 'log.h'
### DEBUG_MODE - Increased logging to help debug or better understand code flow

The mode can be selected in 'log.h' 
For Project_6_1 please see the [log.h file](./PES_project_6_1/source/log.h) for further details.

For Project_6_2 please see the [log.h file](./PES_Project_6_2/source/log.h) for further details.

## Project 6_1
The projects contains the following source files written by the authors -
- Source:
	- 'PES_project_6_1.c' : Main file containing main routine. 
Please see the [PES_project_6_1.c file](./PES_project_6_1/source/PES_project_6_1.c) for further details.
	- 'dac.c' : File containing DAC functions. 
Please see the [dac.c file](./PES_project_6_1/source/dac.c) for further details.
	- 'timer.c' : File containing clock and timing functions. 
Please see the [timer.c file](./PES_project_6_1/source/timer.c) for further details.
	- 'log.c' : File containing logging functions, added time stamp functions.
Please see the [log.c file](./PES_project_6_1/source/log.c) for further details.


## Project 6_2
The projects contains the following source files written by the authors -
- Source:
	- 'PES_Project_6_2.c' : Main file containing main routine. 
Please see the [PES_Project_6_2.c file](./PES_Project_6_2/source/PES_Project_6_2.c) for further details.
	- 'dac.c' : File containing ADC and DAC functions. 
Please see the [dac.c file](./PES_Project_6_2/source/adc_dac.c) for further details.
	- 'timer.c' : File containing clock and timing functions. 
Please see the [timer.c file](./PES_Project_6_2/source/timer.c) for further details.
	- 'log.c' : File containing logging functions, added time stamp functions.
Please see the [log.c file](./PES_Project_6_2/source/log.c) for further details.
	- 'DMA.c' : File containing DMA initilization and functions.
Please see the [DMA.c file](./PES_Project_6_2/source/DMA.c) for further details.
	- 'dsp.c' : File contains DSP functions as described in project requirements.
Please see the [dsp.c file](./PES_Project_6_2/source/dsp.c) for further details.
	- 'myq.c' : File contains queue functions for using FreeRTOS queue.
Please see the [myq.c file](./PES_Project_6_2/source/myq.c) for further details.

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