/*
 * dsp.c
 *
 *  Created on: Apr 18, 2020
 *      Author: Antara and Pavan
 */

#include "dsp.h"
/******************Calculate Standard Deviation********************************/
uint32_t calculateSD(uint32_t data[]) {
    uint32_t sum = 0, mean, SD = 0;
    uint8_t i;
    for (i = 0; i < 64; ++i) {
        sum += data[i];
    }
    mean = sum / 64;
    for (i = 0; i < 64; ++i)
        SD += pow(data[i] - mean, 2);
    return sqrt(SD / 64);
}
/*******************Find the largest value*****************/
uint32_t largest(uint32_t arr[])
{
    uint8_t i;

    // Initialize maximum element
    uint32_t max = arr[0];

    // Traverse array elements from second and
    // compare every element with current max
    for (i = 1; i < 64; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}
/***********************Find the minimum value*************/
uint32_t minimum(uint32_t arr[])
{
    uint8_t i;

    // Initialize minimum element
    uint32_t min = arr[0];

    // Traverse array elements from second and
    // compare every element with current min
    for (i = 1; i < 64; i++)
        if (arr[i] < min)
            min = arr[i];

    return min;
}
/***************find average value***************/
uint32_t average(uint32_t arr[])
{
	uint32_t sum = 0, mean;
	    uint8_t i;
	    for (i = 0; i < 64; ++i) {
	        sum += arr[i];
	    }
	    mean = sum / 64;

    return mean;
}
