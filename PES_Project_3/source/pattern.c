/*
 * write_pattern.c
 *
 *  Created on: Feb 21, 2020
 *      Author: Antara and Pavan
 */

/*
 * Reference
 * https://www.geeksforgeeks.org/pseudo-random-number-generator-prng/
 * Xn+1 = (aXn + c) mod m
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "general.h"

/************************Get address for offset************************************************/
uint32_t* get_address(uint32_t* base_addr, uint32_t* offset)
{
	uint8_t off = (*(uint8_t*)offset);	/* type casting to an 8 bit value to access byte values */
	uint8_t* temp = (uint8_t*)base_addr;
	return ((uint32_t*)&temp[off]);
}
/***************************generate random pattern***************************************/
void rand_pattern(uint8_t *pattern, size_t length, uint8_t seed)
{
	for(uint8_t i=0;i<length;i++)
	{
		uint8_t location = (uint8_t *)(mem_ptr+i);
		pattern[i] = seed^location;
		//PRINTF("0x%x", pattern[i]);
	}
}

/**********************************Write generated pattern to memory**************************************************/
mem_status write_pattern(struct data_type t)
{
	if(mem_ptr == NULL)
	{
		PRINTF("\n\rMemory location unavailable.");
		return FAILED;
	}
	uint8_t len = t.length;
	uint8_t pat[len];
	int8_t i;
	rand_pattern(pat,t.length,t.seed);
	uint8_t* temp = (uint8_t*)mem_ptr;
	for(i = 0;i < t.length;i++)
	{
		temp[i] = pat[i];
	}
	if(i == t.length)
	{
		Log_string("pattern written to the memory");
		return SUCCESS;
	}
	else
	{
		Log_string("Failed To write pattern");
		return FAILED;
	}
}

/*******************************verify if pattern matches******************************************/
mem_status compare_pattern(struct data_type t){
	if(mem_ptr == NULL)
		{
			PRINTF("\n\rMemory location unavailable.");
			return FAILED;
		}
	PRINTF("\n\rEntered %d   %d  \n",t.length,t.seed);
	uint8_t len = t.length;
	uint8_t pat[len];
	uint8_t* temp = (uint8_t *)mem_ptr;
	rand_pattern(pat,t.length,t.seed);
	for(uint8_t i=0;i<len;i++)
	{
		if(pat[i] != temp[i])
		{
			Log_string("pattern Mismatch");
			return FAILED;
		}
	}
	Log_string("Pattern Verified Successfully");
	return SUCCESS;
}

