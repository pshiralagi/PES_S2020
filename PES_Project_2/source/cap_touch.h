/*
 * @filename : cap_touch.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for cap_touch.c
 *
 *    	@author : pshiralagi
 */

#ifndef cap_touch_h
#define cap_touch_h

#include "MKL25Z4.h"

void touch_init(void);
uint16_t touch_scan(void);

// Macros
#define SCAN_OFFSET 544  // Offset for scan range
#define SCAN_DATA TSI0->DATA & 0xFFFF // Accessing the bits held in TSI0_DATA_TSICNT


#endif
