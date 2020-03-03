/*
 * allocate_bytes.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Antara and Pavan
 */


#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"led.h"
#include"general.h"
#include"logger.h"

uint32_t *mem_ptr;
size_t gsize;

//uint32_t*
mem_status allocate_memory(struct data_type t){

	uint32_t *value; //Defining pointer
	value = (uint32_t *) malloc(t.size); //Allocating Size to heap
	gsize = (size_t *)t.size;
	mem_ptr = value;
	/*Check if memory allocation is successful*/
	if(mem_ptr == NULL){
		Log_string("\n\rMemory Allocation failed");
		Fail_Test();
		return FAILED;
	}else{
		Log_string("\n\rMemory Allocation Successful");
		Success_Test();
		return SUCCESS;
	}
	//PRINTF("\n\rAddress:%x  -  Value:%d", value, *value);
	//return value;
}

mem_status verify_memory(struct data_type t){
	PRINTF("MEM_PTR %d", mem_ptr);
	if(mem_ptr == NULL){
		Log_string("\n\rMemory Allocated not for use");
		return FAILED;
	}else{
		Log_string("\n\rMemory Allocated ready for Use");
		return SUCCESS;
	}
}

mem_status free_mem(struct data_type t){
	if(mem_ptr == NULL){
		Log_string("Trying to free Unallocated Memory");
		free(mem_ptr);
		//Fail_Test();
		mem_ptr = NULL;
		return FAILED;
	}else{
		free(mem_ptr);
		Log_string("Allocated Memory has been free");
		mem_ptr = NULL;
		//Success_Test();
		return SUCCESS;
	}
}
