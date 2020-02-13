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


void led_blink_cap(void)
{
	uint32_t cap_val;

	uint8_t loop, count;//Initializing to 0 only once
#ifdef PC_RUN
	uint8_t ledTrig = 0, LED_G, LED_B, LED_R = 1, loop_no = 1;//Initializing values only once
#endif
	uint16_t arr_time[4] = {500, 1000, 2000, 3000};
	/*	PSOR sets output register, PCOR clears output register	*/
#ifdef FB_RUN
		for (count = 0; count < 10; count++)
		{
			cap_val = touch_scan();
	#ifdef FB_DEBUG
			PRINTF("\n\rTouch value is %d",cap_val);
	#endif
			for(loop = 0; loop < 4; loop++)
			{
				if(cap_val < 6001)
				{
			#ifdef FB_DEBUG
					PRINTF("\n\rSwitching red LED on");
			#endif
					PTB->PCOR = MASK(RED_LED_PIN);
				}
				if((cap_val > 6000 ) & (cap_val < 9001 ))
				{
			#ifdef FB_DEBUG
					PRINTF("\n\rSwitching red LED on");
			#endif
					PTB->PCOR = MASK(GREEN_LED_PIN);
				}
				if(cap_val > 9000)
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
				cap_val = touch_scan();
			#ifdef FB_DEBUG
					PRINTF("\n\rDone waiting");
			#endif

				PTB->PSOR = MASK(RED_LED_PIN);
				PTB->PSOR = MASK(GREEN_LED_PIN);
				PTD->PSOR = MASK(BLUE_LED_PIN);
			#ifdef FB_DEBUG
				PRINTF("\n\rAll LEDs off");
			#endif

				wait_ms(500);
			}


		}
#endif


#ifdef PC_RUN
	for(count = 0; count < 10; count++)
	{
		for(loop = 0; loop < 4; loop++)
		{
			if(LED_R == 1)
			{
		#ifdef PC_DEBUG
				printf("\n\rSwitching red LED on");
		#endif
				printf("\n\rRed LED on");
			}
			if(LED_G == 1)
			{
		#ifdef PC_DEBUG
				printf("\n\rSwitching Green LED on");
		#endif
				printf("\n\rGreen LED on");
			}
			if(LED_B == 1)
			{
		#ifdef PC_DEBUG
				printf("\n\rSwitching Blue LED on");
		#endif
				printf("\n\rBlue LED on");
			}

		#ifdef PC_DEBUG
				printf("\n\rLED on time is %d milliseconds", arr_time[loop]);
		#endif
			wait_ms(arr_time[loop]);
		#ifdef PC_DEBUG
				printf("\n\rDone waiting");
		#endif

				printf("\n\rAll LEDs off");
		#ifdef PC_DEBUG
				printf("\n\rAll LEDs off");
		#endif

			if (loop_no == 3)
			{
				ledTrig++;
				if(ledTrig == 1)
				{
					LED_G = 1;
					LED_R = 0;
					LED_B = 0;
				}
				if(ledTrig == 2)
				{
					LED_B = 1;
					LED_G = 0;
					LED_R = 0;
				}
				if(ledTrig == 3)
				{
					LED_R = 1;
					LED_G = 0;
					LED_B = 0;
					ledTrig = 0;
				}
				loop_no = 0;
			}
			loop_no++;
		}

	}
#endif

}



