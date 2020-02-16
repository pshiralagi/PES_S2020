/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    PES_Project_2.c
 * @brief   Application entry point.
 * @date 	4th February, 2020
 * @author	Pavan Shiralagi and Antara Prakash
 */
#include "general.h"
/*
 * @brief   Application entry point.
 */
int main(void) {
#ifdef FB_DEBUG
    PRINTF("\n\rProgram Start\n\r");
#endif
#ifdef PC_DEBUG
    printf("\n\rProgram Start\n\r");
#endif

#ifdef FB_RUN
    board_init();//Board initialization function
#endif

//    To check cap_vals being read
//    while(1)
//    {
//    	wait_ms(3000);
//    	PRINTF("\n\r%d", touch_scan());
//    }

    	led_blink_cap();	//Function to blink LED based on requirements



#ifdef FB_DEBUG
		PRINTF("\n\rGoing to wait 500ms before switching LED on");
#endif


#ifdef FB_DEBUG
    PRINTF("\n\rProgram ending, exiting with code 0\n\r");
#endif
#ifdef PC_DEBUG
    printf("\n\rProgram ending, exiting with code 0\n\r");
#endif

#ifdef FB_RUN
    _exit(0);
#else
    exit(0);
#endif
}

#ifdef FB_RUN
/*	@brief : Function consisting necessary board initializations	*/
	void board_init(void)
	{
		/* Init board hardware. */
		BOARD_InitBootPins();
		BOARD_InitBootClocks();
		BOARD_InitBootPeripherals();
		/* Init FSL debug console. */
		BOARD_InitDebugConsole();


		led_init();
		touch_init();
	}
#endif


#ifdef PC_RUN
	/*	@brief : Wait function for PC using time.h	*/
	void pc_wait(uint16_t wait_time)
	{
		// clock start time, using time.h
		clock_t start_time = clock();

		//Looping until required time elapses
		while (clock() < start_time + wait_time);
	}
#endif




/*	@brief : Main function consisting of LED blinking routines in different modes	*/
void led_blink_cap(void)
{
	uint32_t cap_val;

	uint8_t loop, count;//Initializing to 0 only once
#ifdef PC_RUN
	uint8_t ledTrig = 0, LED_G, LED_B, LED_R = 1, loop_no = 1;//Initializing values only once
#endif
	//Time lookup table
	uint16_t arr_time[4] = {500, 1000, 2000, 3000};
	/*	PSOR sets output register, PCOR clears output register	*/
#ifdef FB_RUN
		for (count = 0; count < 10; count++)
		{
			cap_val = touch_scan();//Obtaining capavitance slider value
	#ifdef FB_DEBUG
			PRINTF("\n\rLoop number : %d", count);
			PRINTF("\n\rTouch value is %d",cap_val);
	#endif
			for(loop = 0; loop < 4; loop++)
			{
				if(cap_val < 6001)// Approximate values, not accurate because of short sampling times
				{
			#ifdef FB_DEBUG
					PRINTF("\n\rSwitching red LED on");
			#endif
					PTB->PCOR = MASK(RED_LED_PIN);
				}
				if((cap_val > 6000 ) & (cap_val < 12501 ))
				{
			#ifdef FB_DEBUG
					PRINTF("\n\rSwitching green LED on");
			#endif
					PTB->PCOR = MASK(GREEN_LED_PIN);
				}
				if(cap_val > 12500)
				{
			#ifdef FB_DEBUG
					PRINTF("\n\rSwitching blue LED on");
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

				wait_ms(500);
			}


		}
#endif


#ifdef PC_RUN
	for(count = 0; count < 10; count++)
	{
		#ifdef PC_DEBUG
			printf("\n\rLoop number is %d", count+1);
		#endif
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
				printf("\n\rDone waiting");
		#endif

				pc_wait(arr_time[loop]);
		#ifdef PC_DEBUG
				printf("\n\rTotal on time is %d milliseconds", arr_time[loop]);
		#endif
				printf("\n\rAll LEDs off");
		#ifdef PC_DEBUG
				printf("\n\rTotal off time is %d milliseconds", 500);
		#endif
				pc_wait(500);
			//Ensures LED color change once every 3 cycles
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
