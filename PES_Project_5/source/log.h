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
	Status,
	DebugMode,
	Test
}log_lvl;

typedef enum {
	fsm1_,
	fsm2,
	fsm3,
	statedecision,
	displaydata,
	sortdata,
	programend,
	I2CMasterTransmit,
	I2CMasterinit,
	readfullxyz,
	loglevel,
	i2cwritebyte,
	i2creadbyte,
	initmma,
	readx_,
	ready_,
	readz_,
	touchscan,
	spicount,
	TestSPILoopback,
	statusmode,
	POST
}func_name;


void log_Level(log_lvl mode);
void log_func_Str(log_lvl mode, func_name func, char *string);
/*void Log_data(uint32_t* location);*/
void Log_string(char *string);
void Log_Integer(uint16_t intg);

#endif /* LOG_H_ */
