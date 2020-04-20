

#ifndef MYQ_H_
#define MYQ_H_
#include "FreeRTOS.h"
#include "queue.h"
void q_add( uint32_t *log);
void q_init(uint32_t queue_length, uint32_t max_log_lenght);

#endif
