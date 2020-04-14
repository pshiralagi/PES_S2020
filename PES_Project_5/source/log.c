/*
 * log.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Pavan Shiralagi and Antara Prakash
 */

#include "log.h"
#include <stdlib.h>
/********** get the mode of the application************/
void log_Level(log_lvl mode)
{
	if(mode == normalmode)
	{
		Send_String_Poll("  NORMAL: ");
	}
	else if(mode == DebugMode)
	{
		Send_String_Poll("  DEBUG: ");
	}
	else
	{
		Send_String_Poll("  TEST: ");
	}
	return;
}

/********** Function to print different function names **********/
void log_func_Str(log_lvl mode, func_name func, char *string)
{
	Send_String_Poll("\n\r");
	timestamp();
	log_Level(mode);

 	if(func == bufferAdd_)
	{
 		Send_String_Poll("bufferAdd: ");
	}
	else if(func == initbuffer)
	{
		Send_String_Poll("init_buffer: ");
	}
	else if(func == isBufferFull_)
	{
		Send_String_Poll("isBufferFull: ");
	}
	else if(func == bufferRemove_)
	{
		Send_String_Poll("bufferRemove: ");
	}
	else if(func == isBufferEmpty_)
	{
		Send_String_Poll("isBufferEmpty: ");
	}
	else if(func == destroybuffer)
	{
		Send_String_Poll("destroy_buffer: ");
	}
	else if(func == mainfunc)
	{
		Send_String_Poll("main function: ");
	}
	else if(func == uartappmode)
	{
		Send_String_Poll("uart_app_mode: ");
	}
	else if(func == uartappmodeint)
	{
		Send_String_Poll("uart_app_mode_int: ");
	}
	else
	{
		Send_String_Poll("change_State: ");
	}
	PRINTF("%s ",string);

	return;
}

/*void Log_data(uint32_t* location){
	PRINTF("Address: 0x%x Data: 0x%x", location, *location);
}*/

void Log_string(char *string)
{
	PRINTF("\n\r%s",string);
}

void Log_Integer(uint32_t intg){
	Send_Number(intg);
}
