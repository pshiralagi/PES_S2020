/*
 * logger.h
 *
 *  Created on: Feb 20, 2020
 *      Author: Antara and Pavan
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include<stdint.h>


void Log_enable(void);
void Log_disable(void);
uint8_t Log_status(void);
void Log_data(uint32_t* location);
void Log_string(char* str);
void Log_Integer(uint32_t intg);

#endif /* LOGGER_H_ */
