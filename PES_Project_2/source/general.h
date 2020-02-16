/*
 * @filename : general.h
 *
 *  @date : Feb 6, 2020
 *  @description : Genral header file to be included in all files
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

/** DO NOT USE WITH CUSTOM MAKEFILE **/
//#define FB_RUN 1	//Non - debug program run natively on the board
//#define FB_DEBUG 1	//Debug version of FB_RUN, includes print statements
//#define PC_RUN 1	//Not run on the board, run on the PC where statements are printed to the debug console
//#define PC_DEBUG 1	//Debug version of PC_RUN with a lot more debug statements
/*****************************************************************************/


#include <stdio.h>

#ifdef FB_DEBUG
#define FB_RUN
#endif

#ifdef PC_DEBUG
	#define PC_RUN
#endif

#ifdef PC_RUN
	#include <stdint.h>
	#include <time.h>
	#include <stdlib.h>
	void pc_wait(uint16_t wait_time);
#endif

void led_blink_cap(void);

#ifdef FB_RUN
	#include "board.h"
	#include "peripherals.h"
	#include "pin_mux.h"
	#include "clock_config.h"
	#include "MKL25Z4.h"
	#include "fsl_debug_console.h"
	#include "cap_touch.h"
	#include <timer.h>
	#include "led.h"
	void board_init(void);
#endif

/* TODO: insert other include files here. */


/* TODO: insert other definitions and declarations here. */


