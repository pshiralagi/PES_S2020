/*
 * general.h
 *
 *  Created on: Feb 29, 2020
 *      Author: Antara and Pavan
 */

#ifndef GENERAL_H_
#define GENERAL_H_
#include<stdint.h>


extern size_t gsize;
extern uint32_t *mem_ptr;

typedef enum mem_status
{
SUCCESS = 0, // no error
FAILED // failure case
} mem_status;

/********************Data type structure*********************************/
struct data_type
{
    //uint32_t* base_addr;
    char *name;
	uint32_t* offset;
    uint8_t* length;
    size_t* size;
    uint32_t* value;
    uint8_t* seed;
};


#endif /* GENERAL_H_ */
