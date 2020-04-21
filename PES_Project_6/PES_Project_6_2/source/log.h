/*
 * log.h
 *
 *  Created on: Mar 24, 2020
 *      Author: pavan and antara
 */


#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdlib.h>
#include "fsl_debug_console.h"

/*	SELECT MODE HERE	*/
#define NORMAL_MODE
//#define DEBUG_MODE

typedef enum {
	NormalMode,
	DebugMode,
	Test
}log_lvl;

typedef enum {
	mainFunction,
	updateDACvals_,
	dacInit_,
	DACtask,
	ADCtask,
	DSPtask,
	null,
	POST
}func_name;


void log_Level(log_lvl mode);
void log_func_Str(log_lvl mode, func_name func, char *string);
/*void Log_data(uint32_t* location);*/
void Log_string(char *string);
void Log_Integer(uint32_t intg);
void Log_Float(uint32_t intg);
#endif /* LOG_H_ */
