/*
 * @filename : led.c
 *
 *  @date : Feb 6, 2020
 *  @description : File containing led functions
 *
 *		@reference : https://github.com/alexander-g-dean/ESF/edit/master/Code/Chapter_2/Source/main.c
 *    	@author : pshiralagi
 *
 */

#include "led.h"

/*	@brief : Function to initialize 3 LEDs as outputs	*/
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

void led_blink_cap(uint16_t cap_val)
{
	static uint8_t loop = 0;//Initializing to 0 only once
	uint16_t arr_time[4] = {500, 1000, 2000, 3000};
	/*	PSOR sets output register, PCOR clears output register	*/
	if(cap_val < 131)
	{
#ifdef FB_DEBUG
		PRINTF("\n\rSwitching red LED on");
#endif
		PTB->PCOR = MASK(RED_LED_PIN);
	}
	if((cap_val > 130 ) & (cap_val < 141 ))
	{
#ifdef FB_DEBUG
		PRINTF("\n\rSwitching red LED on");
#endif
		PTB->PCOR = MASK(GREEN_LED_PIN);
	}
	if(cap_val > 140)
	{
#ifdef FB_DEBUG
		PRINTF("\n\rSwitching red LED on");
#endif
		PTD->PCOR = MASK(BLUE_LED_PIN);
	}

#ifdef FB_DEBUG
		PRINTF("\n\rLED on time is %d milliseconds", arr_time[loop]);
#endif
	wait_ms(arr_time[loop]);
#ifdef FB_DEBUG
		PRINTF("\n\rDone waiting");
#endif

	PTB->PSOR = MASK(RED_LED_PIN);
	PTB->PSOR = MASK(GREEN_LED_PIN);
	PTD->PSOR = MASK(BLUE_LED_PIN);
#ifdef FB_DEBUG
	PRINTF("\n\rAll LEDs off");
#endif

	if (loop < 4)
	{
		loop++;
	}
	if (loop > 3)
	{
		loop = 0;
	}

}
