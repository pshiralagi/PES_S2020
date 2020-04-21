/*
 * myq.c
 *
 *  Created on: Apr 18, 2020
 *      Author: Pavan and Antara
 *      Reference: adc_dma demo project
 */
#include "myq.h"
uint32_t src_adc[64];
/* Logger queue handle */
static QueueHandle_t log_queue = NULL;

void q_init(uint32_t queue_length, uint32_t max_log_lenght)
{
    log_queue = xQueueCreate(queue_length, max_log_lenght);
}
void q_add( uint32_t *log)
{
    xQueueSend(log_queue, log, 0);
}

void q_reset (void)
{
	assert(xQueueReset(log_queue) == pdPASS);
}

void q_copy (uint32_t *store)
{
	xQueueReceive(log_queue, store, 0);
}
