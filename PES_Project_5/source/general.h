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

//#define TEST_MODE
//#define DEBUG_MODE
#define STATUS

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
#include "fsm.h"
#include "log.h"
#include "spi.h"
#include "i2c.h"
#include "acc.h"
#include "buffer.h"
#include "uart.h"




#endif



