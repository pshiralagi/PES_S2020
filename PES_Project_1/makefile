# Date : 01/23/2020 \
Authors : Pavan Shiralagi, Antara Prakash \
Reference : https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html \
This is a make file to create executables of C codes, the functions in the make file are defined as follows \
1. make all - Compile and build all executables \
2. Clean - Delete all files in make directory

# the compiler: gcc for C program
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#  -Werror shows warnings as errors
CFLAGS  = -Wall -Werror -g

# typing 'make' will invoke the first target entry in the file 
# (in this case the all target entry)
all: ott

# To create the executable file ott we need the object files
# one.o, two.o, and three.o:
#
ott:  one two three 

# To create the object file countwords.o, we need the source
# files one.c
#
one.o:  one.c
	$(CC) $(CFLAGS) -c one.c

# To create the object file counter.o, we need the source files
# two.c
#
two.o:  two.c
	$(CC) $(CFLAGS) -c two.c

# To create the object file scanner.o, we need the source files
# three.c
#
three.o:  three.c
	$(CC) $(CFLAGS) -c three.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) one two three *.o *~