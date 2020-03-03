/*
 * led.c
 *
 *  Created on: Feb 23, 2020
 *      Author: praka
 */
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "led.h"
void led_init(void)
	{
		// Enable clock to Port B and Port D
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

		// Initialize 3 GPIO pins
		PORTB->PCR[RED_LED_PIN] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[RED_LED_PIN] |= PORT_PCR_MUX(1);
		PORTB->PCR[GREEN_LED_PIN] &= ~PORT_PCR_MUX_MASK;
		PORTB->PCR[GREEN_LED_PIN] |= PORT_PCR_MUX(1);
		PORTD->PCR[BLUE_LED_PIN] &= ~PORT_PCR_MUX_MASK;
		PORTD->PCR[BLUE_LED_PIN] |= PORT_PCR_MUX(1);

		// Set required GPIO pins as outputs
		PTB->PDDR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
		PTD->PDDR |= MASK(BLUE_LED_PIN);

		//Port clear output registers, masked to clear specific pins (LEDs on)
		PTB->PCOR |= MASK(RED_LED_PIN) | MASK(GREEN_LED_PIN);
		PTD->PCOR |= MASK(BLUE_LED_PIN);

		//Set output registers, LEDs off
		PTD->PSOR = MASK(BLUE_LED_PIN);
		PTB->PSOR = MASK(RED_LED_PIN);
		PTB->PSOR = MASK(GREEN_LED_PIN);
	}
void red_led_on(void){
	//Set Red Led on
	PTB->PCOR = MASK(RED_LED_PIN);
}
void blue_led_on(void){
	//Set Blue Led on
	PTD->PCOR = MASK(BLUE_LED_PIN);
}
void green_led_on(void){
	//Set Green Led on
	PTB->PCOR = MASK(GREEN_LED_PIN);
}
void red_led_off(void){
	//Set Red Led off
	PTB->PSOR = MASK(RED_LED_PIN);
}
void blue_led_off(void){
	//Set Blue Led off
	PTD->PSOR = MASK(BLUE_LED_PIN);
}
void green_led_off(void){
	//Set Green Led off
	PTB->PSOR = MASK(GREEN_LED_PIN);
}
void Start_Test(void){
	blue_led_on();
	red_led_off();
	green_led_off();
}
void Success_Test(void){
	blue_led_off();
	red_led_off();
	green_led_on();
}
void Fail_Test(void){
	blue_led_off();
	red_led_on();
	green_led_off();
}
