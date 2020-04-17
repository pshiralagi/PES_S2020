/*
 * log.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Pavan Shiralagi and Antara Prakash
 */

#include "log.h"
#include "timer.h"
#include <stdlib.h>

void log_Level(log_lvl mode)
{
	if(mode == NormalMode)
	{
		PRINTF("  Normal Mode: ");
	}
	else if(mode == DebugMode)
	{
		PRINTF("  DEBUG: ");
	}
	else
	{
		PRINTF("  TEST: ");
	}
	return;
}

/********** Function to print different function names **********/
void log_func_Str(log_lvl mode, func_name func, char *string)
{
	PRINTF("\n\r");
	timestamp();
	log_Level(mode);
#ifdef DEBUG_MODE
 	if(func == updateDACvals_)
	{
		PRINTF("updateDACvals: ");
	}
	else if(func == dacInit_)
	{
		PRINTF("dacInit: ");
	}
	else if(func == mainFunction)
	{
		PRINTF("main: ");
	}
	else if(func == DACtask)
	{
		PRINTF("dacTask: ");
	}
	else
	{
		PRINTF("");
	}

#endif
 	PRINTF("%s ",string);
	PRINTF("  ");
	return;
}

/*void Log_data(uint32_t* location){
	PRINTF("Address: 0x%x Data: 0x%x", location, *location);
}*/

void Log_string(char *string)
{
	PRINTF("%s",string);
}

void Log_Integer(uint16_t intg){
	PRINTF("%d", intg);
}
