/*
 * pattern.h
 *
 *  Created on: Feb 23, 2020
 *      Author: Antara and Pavan
 */

#ifndef PATTERN_H_
#define PATTERN_H_
#include "general.h"

uint32_t* get_address(uint32_t* base_addr, uint32_t* offset);
void rand_pattern(int8_t *pattern, size_t length, int8_t seed);
mem_status write_pattern(struct data_type t);
mem_status compare_pattern(struct data_type t);

#endif /* PATTERN_H_ */
