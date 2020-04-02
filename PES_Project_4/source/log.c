/*
 * log.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Pavan Shiralagi and Antara Prakash
 */

#include "log.h"
#include <stdlib.h>

void log_Level(log_lvl mode)
{
	if(mode == Status)
	{
		PRINTF("\n\rSTATUS: ");
	}
	else if(mode == DebugMode)
	{
		PRINTF("\n\rDEBUG: ");
	}
	else
	{
		PRINTF("\n\rTEST: ");
	}
	return;
}

/********** Function to print different function names **********/
void log_func_Str(log_lvl mode, func_name func, char *string)
{
	log_Level(mode);
#ifdef DEBUG_MODE
 	if(func == fsm1_)
	{
		PRINTF("fsm_1: ");
	}
	else if(func == fsm2)
	{
		PRINTF("fsm_2: ");
	}
	else if(func == fsm3)
	{
		PRINTF("fsm_3: ");
	}
	else if(func == statedecision)
	{
		PRINTF("state_decision: ");
	}
	else if(func == displaydata)
	{
		PRINTF("display_data: ");
	}
	else if(func == sortdata)
	{
		PRINTF("sort_data: ");
	}
	else if(func == programend)
	{
		PRINTF("program_end: ");
	}
	else if(func == i2cwritebyte)
	{
		PRINTF("i2c_write_byte: ");
	}
	else if(func == i2creadbyte)
	{
		PRINTF("i2c_read_byte: ");
	}
	else if(func == readx_)
	{
		PRINTF("readx : ");
	}
	else if(func == ready_)
	{
		PRINTF("ready : ");
	}
	else if(func == readz_)
	{
		PRINTF("readz : ");
	}
	else if(func == initmma)
	{
		PRINTF("init_mma: ");
	}
	else if(func == touchscan)
	{
		PRINTF("touch_scan : ");
	}
	else if(func == readfullxyz)
	{
		PRINTF("read_full_xyz : ");
	}
	else if(func == spicount)
	{
		PRINTF("spi_count : ");
	}
	else if(func == TestSPILoopback)
	{
		PRINTF("Test_SPI_Loopback : ");
	}
	else
	{
		PRINTF("change_State: ");
	}
	PRINTF("%s ",string);
#endif

#ifdef TEST_MODE
 	if(func == fsm1_)
	{
		PRINTF("fsm_1: ");
	}
	else if(func == fsm2)
	{
		PRINTF("fsm_2: ");
	}
	else if(func == fsm3)
	{
		PRINTF("fsm_3: ");
	}
	else if(func == statedecision)
	{
		PRINTF("state_decision: ");
	}
	else if(func == displaydata)
	{
		PRINTF("display_data: ");
	}
	else if(func == sortdata)
	{
		PRINTF("sort_data: ");
	}
	else if(func == programend)
	{
		PRINTF("program_end: ");
	}
	else if(func == i2cwritebyte)
	{
		PRINTF("i2c_write_byte: ");
	}
	else if(func == i2creadbyte)
	{
		PRINTF("i2c_read_byte: ");
	}
	else if(func == readx_)
	{
		PRINTF("readx : ");
	}
	else if(func == ready_)
	{
		PRINTF("ready : ");
	}
	else if(func == readz_)
	{
		PRINTF("readz : ");
	}
	else if(func == initmma)
	{
		PRINTF("init_mma: ");
	}
	else if(func == touchscan)
	{
		PRINTF("touch_scan : ");
	}
	else if(func == readfullxyz)
	{
		PRINTF("read_full_xyz : ");
	}
	else if(func == spicount)
	{
		PRINTF("spi_count : ");
	}
	else if(func == TestSPILoopback)
	{
		PRINTF("Test_SPI_Loopback : ");
	}
	else
	{
		PRINTF("change_State: ");
	}
	PRINTF("%s ",string);
#endif
	return;
}

/*void Log_data(uint32_t* location){
	PRINTF("Address: 0x%x Data: 0x%x", location, *location);
}*/

void Log_string(char *string)
{
	PRINTF("\n\r%s",string);
}

void Log_Integer(uint16_t intg){
	PRINTF("\n\r  %d", intg);
}
