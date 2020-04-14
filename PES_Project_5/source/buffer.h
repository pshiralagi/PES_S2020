/*
 * @file buffer.h
 *
 *  @date: Apr 7, 2020
 *      @author: pshiralagi, aprakash
 */

#ifndef BUFFER_H
#define BUFFER_H

#include "general.h"
/******Structure to determine pointer of buffer***/
typedef struct {
	uint8_t *buffer;	//pointer to the buffer
	uint8_t *head;		//Where to add an item
	uint8_t *tail;	//Where to remove an item
	size_t  size;		//No. of items allocated to the buffer
	size_t count;	//number of items currently in the buffer
	}buffer_t;

/*******Enum determining status of buffer***********/
typedef enum {
	success = 0,
	buff_full,
	buff_empty,
	fail
	}buffer_status;


buffer_status bufferAdd(buffer_t *q, 	uint8_t data);
buffer_status bufferRemove(buffer_t *q, uint8_t *data);
buffer_status isBufferFull(buffer_t *q);
buffer_status isBufferEmpty(buffer_t *q);
buffer_status init_buffer(buffer_t *q, size_t size);
buffer_status destroy_buffer(buffer_t *q);
buffer_status isPointerValid(buffer_t *q);
buffer_status isBufferInitialized(buffer_t*q);
buffer_status add_memory(buffer_t *q, size_t size);
buffer_status bufferExtendAdd(buffer_t *q, uint8_t data);
void displayBuffer(buffer_t *q);

extern buffer_t * Tx;
extern buffer_t * Rx;
#endif // BUFFER_H
