# PES Coding Exercise 2
----------------------------------------------------------------------------------------------------------------------------------------------------
## Reference - Code taken from PES Coding Exercise document provided my Prof. Bruce Montgomery
## Author - Pavan Shiralagi

## Contents

This repository contains C code for the Coding Assignment 2 of the Spring 2020 PES class at CU Boulder 

It can be run in 3 different modes based on the define enabled at the beginning of the file.

Uncomment `#define EXAMPLE_1` to run Problem 1 code where the LED blinks in a RGB pattern.
Uncomment `#define EXAMPLE_2` to run Problem 2 which will blink all three colored LEDs (becomes white) at 1 Hz. 
Uncomment `#define EXAMPLE_3` and connect PE1 to PE3 to transmit data over SPI.  If data is transmitted correctly, Green LED stays on, 
if transmission is not occurring correctly, Red LED switches on.
