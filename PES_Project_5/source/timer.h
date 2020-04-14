/*
 * @filename : time.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for i2c.c
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#ifndef timer_h
#define timer_h
#include "general.h"

#define STM32_SYSCLK (48000000)

void wait_ms(uint32_t time);
void cap_delay_ticks(unsigned ticks);
void SysTick_delay();
void SysTick_Handler();
void timestamp(void);


//static inline void delay_ms(uint16_t ms)
//{
//    cap_delay_ticks((ms * (STM32_SYSCLK / 8)) / 1000);
//}

#endif
