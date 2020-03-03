/*
 * write_memory.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Antara and Pavan
 */

#include<stdio.h>
#include<stdint.h>
#include "fsl_debug_console.h"
#include "logger.h"
#include "pattern.h"
#include "general.h"

/********** Display memory at particular location *************/

mem_status display_memory(struct data_type t){
	uint8_t *display;
	uint8_t *temp = (uint8_t *)mem_ptr;
	display = temp;
	if(t.length <= gsize){
		Log_string("Following is the content in the memory");
		for(int i=0;i<t.length;i++)
		{
			*(display+i) = *(temp+i);
			Log_string("\t");
			Log_Integer(*(display+i));
		}
		Log_string("\n");
		return SUCCESS;
	}else{
		Log_string("Memory out of Bounds");
		return FAILED;
	}
}


/********* Memory data write function definition *********/
mem_status write_memory(struct data_type t)
{
	uint32_t temp_value = t.value;
	if(mem_ptr == NULL)
	{
		Log_string("\n\rMemory location unavailable.");
		return FAILED;
	}
	int j = (uint8_t)t.offset;
	PRINTF("\n\r%d    %x     %d\n",t.offset, t.value, t.length);
	uint8_t* temp = (uint8_t*)mem_ptr;
	for(uint8_t i=t.length;i>0;i--){
		*(temp+j+i) = (uint8_t)temp_value;
		PRINTF("\n\r %x    %x", (temp+j+i), *(temp+j+i));
		temp_value = temp_value>>8;
	}

	Log_string("Data written to the memory");
	return SUCCESS;
}

/********* Memory inversion *********/
mem_status invert_block(struct data_type t)
{
	if(mem_ptr == NULL)
	{
		PRINTF("Memory not available");
		return FAILED;
	}
	uint8_t i;
	uint8_t* temp = (uint8_t*)mem_ptr;
	uint8_t offset = (uint8_t*)t.offset;
	if(t.offset <= gsize){
		for(i=0;i<t.length;i++)
		{

			*(temp+offset+i) = *(temp+offset+i)^(0xFF);
		}
		if(i == t.length)
		{
			Log_string("Memory Inverted");
			return SUCCESS;
		}
		else
		{
			Log_string("Memory Inversion failed");
			return FAILED;
		}
	}
	else
		Log_string("Memory Inversion failed");
		return FAILED;
}
