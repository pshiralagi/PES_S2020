/*
 * myq.h
 *
 *  Created on: Apr 18, 2020
 *      Author: Pavan and Antara
 */

#ifndef MYQ_H_
#define MYQ_H_
#include "FreeRTOS.h"
#include "queue.h"
#include "DMA.h"
void q_add( uint32_t *log);
void q_init(uint32_t queue_length, uint32_t max_log_lenght);
void q_reset (void);
void q_copy (uint32_t *store);
#endif
