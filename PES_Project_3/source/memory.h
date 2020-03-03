/*
 * memory.h
 *
 *  Created on: Feb 22, 2020
 *      Author: praka
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include "general.h"

mem_status display_memory(struct data_type t);
mem_status write_memory(struct data_type t);
mem_status invert_block(struct data_type t);

#endif /* MEMORY_H_ */
