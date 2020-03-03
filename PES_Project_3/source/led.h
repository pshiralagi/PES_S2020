/*
 * led.h
 *
 *  Created on: Feb 23, 2020
 *      Author: Antara and Pavan
 */

#ifndef LED_H_
#define LED_H_

/**Includes**/
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led.h"

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

#endif /* LED_H_ */
