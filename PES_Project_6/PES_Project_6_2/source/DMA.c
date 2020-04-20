/*
 * DMA.c
 *
 *  Created on: Apr 17, 2020
 *      Author: Pavan and Antara
 */



#include "DMA.h"

uint32_t src_adc[64];
uint32_t dest_adc[64];
/*******************************************************************************
 * Variables
 ******************************************************************************/
dma_handle_t g_DMA_Handle;
volatile bool g_Transfer_Done = false;
dma_transfer_config_t transferConfig;

/* User callback function for DMA transfer. */
void DMA_Callback(dma_handle_t *handle, void *param)
{
    g_Transfer_Done = true;
}
/* Configure DMAMUX */
void DMA_transfer(void){

	/*PRINTF("DMA memory to memory transfer example begin.\r\n\r\n");
	    PRINTF("Destination Buffer:\r\n");
	    for (uint8_t i = 0; i < BUFF_LENGTH; i++)
	    {
	        PRINTF("%d\t", dest_adc[i]);
	    }
*/
	DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, DMA_CHANNEL, DMA_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, DMA_CHANNEL);

    /* Configure DMA one shot transfer */
    DMA_Init(DMA0);
    DMA_CreateHandle(&g_DMA_Handle, DMA0, DMA_CHANNEL);
    DMA_SetCallback(&g_DMA_Handle, DMA_Callback, NULL);
    DMA_PrepareTransfer(&transferConfig, src_adc, sizeof(src_adc[0]), dest_adc, sizeof(dest_adc[0]), sizeof(src_adc),
                        kDMA_MemoryToMemory);
    DMA_SubmitTransfer(&g_DMA_Handle, &transferConfig, kDMA_EnableInterrupt);
    DMA_StartTransfer(&g_DMA_Handle);
    /* Wait for DMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
    /* Print destination buffer */
  /*  PRINTF("\r\n\r\nDMA memory to memory transfer example finish.\r\n\r\n");
    PRINTF("Destination Buffer:\r\n");
    for (uint8_t i = 0; i < BUFF_LENGTH; i++)
    {
        PRINTF("%d\t", dest_adc[i]);
    }*/
}

