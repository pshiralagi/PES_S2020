/*
 * @filename : led.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for led.c
 *
 *    	@author : pshiralagi
 */

#ifndef led_h
#define led_h

//Includes
#include "MKL25Z4.h"
#include "time.h"


void led_init(void);
void led_blink_cap(uint16_t cap_val);

//Defines
#define RED_LED_PIN   (18)	//Pin 18, Port B
#define GREEN_LED_PIN (19)	//Pin 19, Port B
#define BLUE_LED_PIN  (1)	//Pin 1, Port D
#define MASK(x) (1UL << (x))

#endif
