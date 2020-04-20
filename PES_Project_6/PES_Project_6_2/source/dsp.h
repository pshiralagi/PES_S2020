/*
 * dsp.h
 *
 *  Created on: Apr 18, 2020
 *      Author: praka
 */

#ifndef DSP_H_
#define DSP_H_

#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>

uint32_t average(uint32_t arr[]);
uint32_t calculateSD(uint32_t data[]);
uint32_t largest(uint32_t arr[]);
uint32_t minimum(uint32_t arr[]);

#endif /* DSP_H_ */
