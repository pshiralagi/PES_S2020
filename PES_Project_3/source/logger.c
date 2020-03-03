/*
 * logger.c
 *
 *  Created on: Feb 20, 2020
 *      Author: Antara and Pavan
 */

#include<stdio.h>
#include<stdint.h>
#include"logger.h"
#include "fsl_debug_console.h"

//#define LOG_ENABLE			//Comment to disable log
#define LOG DISABLE			//Comment to Enable Log


#ifdef LOG_ENABLE
void Log_data(uint32_t* location){
		PRINTF("Address: 0x%x Data: 0x%x", location, *location);
	}

	void Log_string(char *string)
		{
			PRINTF("\n\r%s",string);
		}

	void Log_Integer(uint32_t intg){
		PRINTF("0x%x", intg);
	}

#else
	void Log_data(uint32_t* location){
			//PRINTF("Address: 0x%x Data: 0x%x", location, *location);
		}

		void Log_string(char *string)
			{
				//PRINTF("\n\r%s",string);
			}

		void Log_Integer(uint32_t intg){
			//PRINTF("0x%x", intg);
		}

#endif

uint8_t FLAG = 0;
/*
void Log_enable(void){
	FLAG = 1;
}

void Log_disable(void){
	FLAG = 0;
}
*/

uint8_t Log_status(void){
	if(FLAG == 0){
		return 1;
	}else{
		return 0;
	}
}

