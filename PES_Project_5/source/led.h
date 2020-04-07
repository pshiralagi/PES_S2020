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

void red_led_on(void);
void blue_led_on(void);
void green_led_on(void);
void red_led_off(void);
void blue_led_off(void);
void green_led_off(void);
void Start_Test(void);
void Success_Test(void);
void Fail_Test(void);

#endif
