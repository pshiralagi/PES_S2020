/*
 * @filename : general.h
 *
 *  @date : Feb 6, 2020
 *  @description : Genral header file to be included in all files
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

/*****************************************************************************/

#ifndef general_h_
#define general_h_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define APPLICATION_MODE
//#define ECHO_MODE

//#define TEST_MODE
//#define NORMAL_MODE
#define DEBUG_MODE


#ifdef TEST_MODE
#include "UnitTest.h"
#endif

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
#include "log.h"
#include "buffer.h"
#include "uart.h"
#include "mode.h"


/*******Critical Section Definition**********/
#define START_CRITICAL() 	__disable_irq()
#define END_CRITICAL()		__enable_irq()


#endif



