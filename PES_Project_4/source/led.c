/*
 * @filename : led.c
 *
 *  @date : Feb 6, 2020
 *  @description : File containing led initializations
 *
 *		@reference : https://github.com/alexander-g-dean/ESF/edit/master/Code/Chapter_2/Source/main.c
 *    	@author : Pavan Shiralagi and Antara Prakash
 *
 */

#include "led.h"


/*	@brief : Function to initialize 3 LEDs as outputs	*/
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
