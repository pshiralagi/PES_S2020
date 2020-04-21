# PES Project 6
----------------------------------------------------------------------------------------------------------------------------------------------------

## Authors - Pavan Shiralagi and Antara Prakash

## Contents

This repository contains C code for project 6 as described in Assignment 6 of the Spring 2020 PES class at CU Boulder

This project explores usage of DAC, ADC and DMA in a FreeRTOS environment.

**Important Notes**
1. Oscilloscope captures were not taken due to lack of access to equipment, instead the values were plotted in excel and a sine wave was seen
2. Baud rate is set to **115200**
3. ADC pin number - **j10 1**
4. DAC pin number - **j10 11**
5. Access to the shared LED is controlled through Mutex
6. ADC values are stored in a queue, these values are then copied to a buffer and then transferred to the DSP buffer using DMA


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

- Reading size of queue in FreeRTOS does not seem to be possible. 
- Debugging without an oscilloscope or logic analyzer was very difficult as you can't tell if DAC or ADC is messed up.

## Execution Notes

For project 6_2, connect ADC pin to DAC pin and observe similar values, every 1 run cycle (64 values) DSP functions are 
carried out and after 5 run cycles, tasks are terminated.

The data can be read on a terminal emulator with a baud rate of 115200.


-----------------------------------------------------------------------------------------------------------------------------------------------------