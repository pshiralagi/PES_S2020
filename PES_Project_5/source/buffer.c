/*
 * @file	buffer.c
 * @author	pshiralagi and aprakash
 * @date	7th April
 * @reference	http://www.simplyembedded.org/tutorials/interrupt-free-ring-buffer/
 * https://hackaday.com/2015/10/29/embed-with-elliot-going-round-with-circular-buffers/
 */



#include "buffer.h"
/****************Check if buffer initialized*************/
buffer_status isBufferInitialized(buffer_t *q)
{
	if(((q->head)==(q->tail)) && ((q->count)!=(q->size)) && (q->count == 0))
		return success;
	return fail;

}
/********************Check if its valid buffer***********************/
buffer_status isPointerValid(buffer_t *q)
{
    if((q->buffer==(NULL)))
    	return fail;
    return success;

}
/***********Add Value to buffer ********************/
buffer_status bufferAdd(buffer_t *q, uint8_t data)
{

	if(isBufferFull(q)==buff_full)
	{
		return buff_full;
	}
	*(q->head)=data;
	if((q->head)==(q->buffer+q->size-1))
	{
		 (q->head)=(q->buffer);
	}
	else
	{
		q->head=q->head+1;
	}
	q->count=q->count+1;
	return success;
}
/*******************Extend buffer after every add********************************/
buffer_status bufferExtendAdd(buffer_t *q, uint8_t data)
{
	*(q->head)=data;
	if(((q->head)==(q->buffer+q->size-1)) && (q->tail == q->buffer))
	{
		add_memory(q, 1);
	}
	else if((q->head)==(q->buffer+q->size-1)&& (q->tail != q->buffer))
	{
		 (q->head)=(q->buffer);
		q->count=q->count+1;
		return success;
	}
	q->head=q->head+1;
	q->count=q->count+1;
	return success;
}

/******Remove Element from buffer******************/
buffer_status bufferRemove(buffer_t *q, volatile uint8_t **data){
    if(isBufferEmpty(q)==buff_empty)
		return buff_empty;

    START_CRITICAL();
  	*data=(q->tail);
	if((q->tail)==(q->buffer+q->size-1))
		{
		 	(q->tail)=(q->buffer);
		}
	else
		{
			(q->tail)=(q->tail)+1;
		}
		(q->count)=(q->count)-1;
		END_CRITICAL();
	return success;
}
/************Check if buffer id full***********************/
buffer_status isBufferFull(buffer_t *q)
{

	if(((q->count)==(q->size))&&((q->head)==(q->tail)))
		return buff_full;
	return success;

}
/**************Check if Buffer is Empty*************************/
buffer_status isBufferEmpty(buffer_t *q)
{
	if(((q->count)!=(q->size))&&((q->head)==(q->tail)))
		return buff_empty;
	return success;
}

/***************Initialize circular buffer*******************/
buffer_status init_buffer(buffer_t *q, size_t size)
{
	START_CRITICAL();
	q->size=size;
	q->buffer=(uint8_t*)malloc((sizeof(uint8_t)*size)+100);
	q->head=q->buffer;
	q->tail=q->buffer;
	q->count=0;
	END_CRITICAL();
	return isBufferInitialized(q);
}
/************destroy circular buffer*******************/
buffer_status destroy_buffer(buffer_t *q)
{
	q->size=0;
	free (q->buffer);
	return success;
}

/*Add Memory to the buffer*/
buffer_status add_memory(buffer_t *q, size_t size)
{
	START_CRITICAL();
	q->size = q->size + size;
	END_CRITICAL();
	return success;
}


/****Display Buffer Value****/
void displayBuffer(buffer_t *q)
{
	uint8_t a;
	uint8_t count = q->count;
	uint8_t *p = q->buffer;
	for (a = 0; (a < count); a++)
	{
		printf(" \n\r %c", p[a]);
	}


}
