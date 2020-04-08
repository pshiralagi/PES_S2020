/*
 * @filename : time.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for i2c.c
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#include <timer.h>

/*	@brief : Wait function, waits in milliseconds using a while loop
 * @param : time is time to wait for in milliseconds
 */
void wait_ms(volatile uint32_t time)
{
	time = time*4250;	//Values tested on oscilloscope
	for (time; time!=0; time--)
	{
		__asm("nop"); //No operation
	}
}

///*
// * @brief : Initialize systick and provide delay based on value of param, polls touch slider till time complete
// * @param : ticks is the number of ticks to wait
// * @reference : https://hasanyavuz.ozderya.net/?p=393
// */
//void cap_delay_ticks(unsigned ticks)
//{
//    SysTick->LOAD = ticks;
//    SysTick->VAL = 0;
//    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
//
//    // COUNTFLAG is a bit that is set to 1 when counter reaches 0.
//    // It's automatically cleared when read.
//    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
//    	{
//    		cap_val = touch_scan();//Obtaining capacitance slider value;
//    	}
//    SysTick->CTRL = 0;
//}

void SysTick_delay(uint8_t seconds)
{
	//Interrupt at 3s
	SysTick->LOAD = seconds*(48000000L/16);
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}


//void SysTick_Handler(void)
//{
//	interrupt_clear = true;
//
//	NVIC_DisableIRQ(SysTick_IRQn);
//}
