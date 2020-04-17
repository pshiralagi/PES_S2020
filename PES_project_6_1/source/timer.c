/*
 * @filename : time.h
 *
 *  @date : Feb 6, 2020
 *  @description : Source file for timer.c
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#include "timer.h"

/*	@brief : Wait function, waits in milliseconds using a while loop
 * @param : time is time to wait for in milliseconds
 */

static uint8_t hr=0, min=0, sec=0, ms;
char tstamp[20];
char hour[4], minutes[2], seconds[2], milliseconds[3];
void wait_ms(volatile uint32_t time)
{
	time = time*4250;	//Values tested on oscilloscope
	for (time; time!=0; time--)
	{
		__asm("nop"); //No operation
	}
}

/*************initializing timer********************/
void SysTick_delay(void)
{
	//Interrupt at 3s
	SysTick->LOAD = (48000000L/16)*0.1;
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void timer_calculation(void){
	ms += 10;
			if(ms == 100)
			{
				ms = 0;
				sec += 1;
				if(sec == 60)
				{
					sec = 0;
					min += 1;

					if(min == 60)
					{
						hr += 1;
						min = 0;

					}
				}
			}
}
void timestamp(void){

	Log_Integer(hr);
	Log_string(":");
	Log_Integer(min);
	Log_string(":");
	Log_Integer(sec);
	Log_string(":");
	Log_Integer(ms);
}
