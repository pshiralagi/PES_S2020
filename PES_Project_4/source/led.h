/*
 * @filename : led.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for led.c
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#ifndef led_h_
#define led_h_

	//Includes
#include "general.h"

void led_init(void);
//Defines
#define RED_LED_PIN   (18)	//Pin 18, Port B
#define GREEN_LED_PIN (19)	//Pin 19, Port B
#define BLUE_LED_PIN  (1)	//Pin 1, Port D
#define MASK(x) (1UL << (x))


#endif
