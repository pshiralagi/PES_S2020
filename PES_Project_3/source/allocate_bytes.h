/*
 * allocate_bytes.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Antara and Pavan
 */

#ifndef ALLOCATE_BYTES_H_
#define ALLOCATE_BYTES_H_

#include<stdint.h>
#include"general.h"

mem_status free_mem(struct data_type t);
mem_status allocate_memory(struct data_type t);
mem_status verify_memory(struct data_type t);

#endif /* ALLOCATE_BYTES_H_ */
