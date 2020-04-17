
#include "myq.h"
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
