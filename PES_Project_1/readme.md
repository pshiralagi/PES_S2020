 **PES Project 1 Readme**
----------------------------------------------------------------------------------------------------------------------------------------------------

**Authors** - Pavan Shiralagi and Antara Prakash

**Contents**

This repository contains C code for project 1 as described in Assignment 1 of the Spring 2020 PES class at CU Boulder 
The repository contains the following files -
Readme - Overview file
Makefile - File to build programs as required
one.c - Program One converts inputs to different types and prints them out while verifying error conditions. For further information, refer to PES Assignment 1 Spring 2020 for more information
two.c - Program Two tests a character code for certain features and prints them out in a specified formatas described in the assignment
three.c - Program Three as described in the assignment

one.c requires 3 inputs, Value | Radix | Operand Size	Comma seperated values without spaces is required
three.c assumes that the "last" bits are the right most bits (based on assumption of endianness) however the bit check function has been written so it is easy to modify if required
Checking for **at least** 3 bits on

**Project Comments**

Segmentation faults encountered when run on OSx, due to buffer overflow which is not monitored.  Ubuntu manages overflow.
Faced some problems getting Virtual Machine working on one of our computers (Windows), boots to a black screen, worked fine on the other (OSx). Could not be resolved
Stricter requirements could be both a plus point, was not sure exactly what was required in some areas but have described what has been done in comments

**Execution Notes**

Compiler used - gcc
Code edited on TextMate and Xcode
**All code and makefile tested and run on Ubuntu application for Windows**
Compiler flags -Wall, -Werror and -g used for compilation
Make `all` builds all three .c files and creates three executables
Make `one` builds only the first .c file (one.c) and creates the executable
Make `two `only builds two.c and creates the executable
Make `three` only builds three.c and creates the executable
Make `clean` removes all .o and executable files from the directory, leaving only the .c files
If a file that has been made is remade without changes, it will not be rebuilt as it is already up to date

-----------------------------------------------------------------------------------------------------------------------------------------------------