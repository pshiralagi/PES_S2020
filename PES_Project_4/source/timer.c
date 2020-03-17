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
