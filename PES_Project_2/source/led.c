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
#ifdef FB_RUN
	void led_init(void)
	{
		#ifdef FB_DEBUG
			PRINTF("\n\rInitializing LEDs");
		#endif
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
		#ifdef FB_DEBUG
			PRINTF("\n\rAll LEDs off");
		#endif

	}
#endif
