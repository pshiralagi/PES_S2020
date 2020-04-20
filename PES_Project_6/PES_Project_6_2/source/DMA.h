/*
 * DMA.h
 *
 *  Created on: Apr 17, 2020
 *      Author: praka
 */

#ifndef DMA_H_
#define DMA_H_

#include <stdlib.h>
#include "board.h"

#include "fsl_debug_console.h"
#include "fsl_dma.h"
#include "fsl_dmamux.h"

#include "pin_mux.h"
#include "clock_config.h"

extern uint32_t src_adc[64];
extern uint32_t dest_adc[64];

#define BUFF_LENGTH 64
#define DMA_CHANNEL 0
#define DMA_SOURCE 63


void DMA_transfer();
void DMA_Callback(dma_handle_t *handle, void *param);

#endif /* DMA_H_ */
