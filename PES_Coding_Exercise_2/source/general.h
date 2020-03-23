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

#ifndef GENERAL_H_
#define GENERAL_H_

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "cap_touch.h"
#include "timer.h"
#include "led.h"
#include "board_init.h"
#include "fsm.h"

extern bool state_machine_1, state_machine_2, state_machine_3;
extern bool interrupt_clear;
extern volatile uint32_t cap_val;


#endif
