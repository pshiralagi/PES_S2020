/*
 * @file	buffer.c
 * @author	pshiralagi and aprakash
 * @date	7th April
 * @reference	http://www.simplyembedded.org/tutorials/interrupt-free-ring-buffer/
 * https://hackaday.com/2015/10/29/embed-with-elliot-going-round-with-circular-buffers/
 */



#include "buffer.h"

buffer_status isBufferInitialized(buffer_t *q)
{
	if(((q->head)==(q->tail)) && ((q->count)!=(q->size)) && (q->count == 0))
		return success;
	return fail;

}

buffer_status isPointerValid(buffer_t *q)
{
    if((q->buffer==(NULL)))
    	return fail;
    return success;

}

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
buffer_status bufferRemove(buffer_t *q, uint8_t *data){
    if(isBufferEmpty(q)==buff_empty)
		return buff_empty;

  	*data=*(q->tail);
	if((q->tail)==(q->buffer+q->size-1))
		{
		 	(q->tail)=(q->buffer);
		}
	else
		{
			(q->tail)=(q->tail)+1;
		}
		(q->count)=(q->count)-1;
	return success;
}

buffer_status isBufferFull(buffer_t *q)
{

	if(((q->count)==(q->size))&&((q->head)==(q->tail)))
		return buff_full;
	return success;

}

buffer_status isBufferEmpty(buffer_t *q)
{
	if(((q->count)!=(q->size))&&((q->head)==(q->tail)))
		return buff_empty;
	return success;
}

buffer_status init_buffer(buffer_t *q, size_t size)
{
	q->size=size;
	q->buffer=(uint8_t*)malloc((sizeof(uint8_t)*size)+100);
	q->head=q->buffer;
	q->tail=q->buffer;
	q->count=0;
	return isBufferInitialized(q);
}

buffer_status destroy_buffer(buffer_t *q){

	uint8_t *p;
	q->size=NULL;
	p=q->buffer;
	free (q->buffer);
//	while(p != NULL)
//	{
//		p=NULL;
//		p++;
//	}
	return success;
}


buffer_status add_memory(buffer_t *q, size_t size)
{
	q->size = q->size + size;
	return success;
}
