/*
 * log.h
 *
 *  Created on: Mar 24, 2020
 *      Author: praka
 */


#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include "fsl_debug_console.h"
#include "general.h"


typedef enum {
	normalmode,
	DebugMode,
	Test
}log_lvl;

typedef enum {
	bufferAdd_,
	initbuffer,
	isBufferFull_,
	bufferRemove_,
	isBufferEmpty_,
	destroybuffer,
	mainfunc,
	uartappmode,
	uartappmodeint,
	null
}func_name;


void log_Level(log_lvl mode);
void log_func_Str(log_lvl mode, func_name func, char *string);
/*void Log_data(uint32_t* location);*/
void Log_string(char *string);
void Log_Integer(uint32_t intg);

#endif /* LOG_H_ */
