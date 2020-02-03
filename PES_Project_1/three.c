/* @filename : three.c
 * @date : 01/29/2020
 * @author : Pavan Shiralagi and Antara Prakash
 * @references : https://codeforwin.org/2017/12/c-program-rotate-number-bits.html for bit rotation
 *				https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/ for hex string to binary table
 * @description : This program performs necessary bit and byte manipulations on a hex value as described in the 
 *					Spring 2020 PES assignment 1
 * @note : We assume that the "last" bits are the right most bits (based on assumption of endianness) 
 *			however the bit check function has been written so it is easy to modify if required
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//Defines
#define INT_SIZE sizeof(uint16_t)        // Size of int in bytes
#define INT_BITS ((INT_SIZE * 8) - 1)   // Size of int in bits - 1

//Function declarations
uint16_t reverse_bytes(uint16_t bytes);
uint16_t rotateRight(uint16_t num, uint8_t rotation);
uint16_t rotateLeft(uint16_t num, uint8_t rotation);
void HexToBin(char* hexdec);
void binary_print(uint16_t to_print);
void check_bits(uint16_t to_check);



int main()
{
    uint16_t manipulate;
    manipulate = 0xFACE;//Initial hex value
    printf("\n\rOriginal input in hex, 0x%X\n\r", manipulate);
	check_bits(manipulate);//Check last 4 bits for at least 3 1s
    manipulate = reverse_bytes(manipulate);//Reverse bytes of hex value
    printf("\n\rReversed bytes, 0x%X\n\r", manipulate);
	check_bits(manipulate);
    manipulate = rotateLeft(manipulate, 6);//Rotate 6 bits left
    printf("\n\rRotated 6 bits to the left, 0x%X\n\r", manipulate);
	check_bits(manipulate);
    manipulate = rotateRight(manipulate, 4);//Rotate 4 bits right
    printf("\n\rRotated 4 bits to the right, 0x%X\n\r", manipulate);
	check_bits(manipulate);
	printf("\n\r");
    return 0;
}

/**
 * @brief : Function to check if at least 3 of the last 4 bits are set
 *
 * @to_check        16 bit hex value to be checked
 */
void check_bits(uint16_t to_check)
{
	uint8_t count = 0;
	if(to_check & (1<<0))
	{
		count++;
	}
	if(to_check & (1<<1))
	{
		count++;
	}
	if(to_check & (1<<2))
	{
		count++;
	}
	if(to_check & (1<<3))
	{
		count++;
	}
	if (count >= 3)
	{
		printf("True, ");
	}
	if (count < 3)
	{
		printf("False, ");
	}
	binary_print(to_check);
	
}

/**
 * @brief : Function to reverse bytes of the hex value
 *
 * @to_reverse         16 bit hex value to be reversed
 */
uint16_t reverse_bytes(uint16_t to_reverse)
{
    uint16_t reversed = 0;
    uint16_t byte_no;
    uint8_t i;

    for(i = 0; i < 16; i+=8)
    {
        byte_no = (to_reverse >> i) & 0xFF;
        reversed |= byte_no << (8 - i);
    }
    return reversed;
}


/**
 * @brief : Function to rotate bits of a number to left
 *
 * @num         Number to rotate
 * @rotation    Number of times to rotate left
 */
uint16_t rotateLeft(uint16_t num, uint8_t rotation)
{
    int DROPPED_MSB;

    // The effective rotation
    rotation %= INT_BITS;


    // Loop till rotation becomes 0
    while(rotation--)
    {
        // Get MSB of num before it gets dropped
        DROPPED_MSB = (num >> INT_BITS) & 1; 

        // Left rotate num by 1 and 
        // Set its dropped MSB as new LSB
        num = (num << 1) | DROPPED_MSB;
    }

    return num;
}



/**
 * @brief : Function to rotate bits of a number to right
 *
 * @num         Number to rotate
 * @rotation    Number of times to rotate right
 */
uint16_t rotateRight(uint16_t num, uint8_t rotation)
{
    int DROPPED_LSB;

    // The effective rotation
    rotation %= INT_BITS;


    // Loop till rotation becomes 0
    while(rotation--)
    {
        // Get LSB of num before it gets dropped
        DROPPED_LSB = num & 1;

        // Right shift num by 1 and 
        // Clear its MSB
        num = (num >> 1) & (~(1 << INT_BITS));

        // Set its dropped LSB as new MSB
        num = num | (DROPPED_LSB << INT_BITS);
    }

    return num;
}

/**
 * @brief : Function to print binary value from a hex value
			Uses HexToBin to print from hex string
 *
 * @to_print         Hex value to be printed
 */

void binary_print(uint16_t to_print)
{
	char hex_str[16];
	uint16_t hex_val;
	hex_val = to_print;
	sprintf(hex_str, "%02X", hex_val);
	HexToBin(hex_str);
}
/**
 * @brief : Function to print binary value from hex string
 *
 * @hexdec       Hex value in string format
 */
void HexToBin(char* hexdec) 
{ 

	long int i = 0; 

	while (hexdec[i]) { 

		switch (hexdec[i]) { 
		case '0': 
			printf("0000"); 
			break; 
		case '1': 
			printf("0001"); 
			break; 
		case '2': 
			printf("0010"); 
			break; 
		case '3': 
			printf("0011"); 
			break; 
		case '4': 
			printf("0100"); 
			break; 
		case '5': 
			printf("0101"); 
			break; 
		case '6': 
			printf("0110"); 
			break; 
		case '7': 
			printf("0111"); 
			break; 
		case '8': 
			printf("1000"); 
			break; 
		case '9': 
			printf("1001"); 
			break; 
		case 'A': 
		case 'a': 
			printf("1010"); 
			break; 
		case 'B': 
		case 'b': 
			printf("1011"); 
			break; 
		case 'C': 
		case 'c': 
			printf("1100"); 
			break; 
		case 'D': 
		case 'd': 
			printf("1101"); 
			break; 
		case 'E': 
		case 'e': 
			printf("1110"); 
			break; 
		case 'F': 
		case 'f': 
			printf("1111"); 
			break; 
		default: 
			printf("\nInvalid hexadecimal digit %c", 
				hexdec[i]); 
		} 
		i++; 
	} 
} 
