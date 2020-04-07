/*
 * @filename : board_init.c
 *
 *  @date : Feb 6, 2020
 *  @description : File containing calls to initialization functions
 *
 *    	@author : pshiralagi and Antara Suresh
 *
 */

#include "board_init.h"


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
}
