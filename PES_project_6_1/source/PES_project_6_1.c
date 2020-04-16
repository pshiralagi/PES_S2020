/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    PES_project_6_1.c
 * @brief   Application entry point.
 * https://github.com/kylemanna/kinetis-sdk2/blob/master/boards/frdmkl43z/rtos_examples/freertos_swtimer/freertos_swtimer.c
 */
#include <stdio.h>
#include <assert.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "dac.h"
#include "task.h"



static bool write_flag = 0;
uint16_t dac_vals[500];
static void SwTimerCallback(TimerHandle_t xTimer);
static void dacTask(void *pvParameters);
/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    SystemCoreClockUpdate();
    TimerHandle_t SwTimerHandle = NULL;
    printf("LED Initialized\n\r");
    LED_BLUE_INIT(1);

    updateDACvals();

    dacInit();
    SwTimerHandle = xTimerCreate("SwTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     SwTimerCallback);
    xTimerStart(SwTimerHandle, 0);
    xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+10, NULL, tskIDLE_PRIORITY+1 , NULL);
    vTaskStartScheduler();

    while(1);

}



static void SwTimerCallback(TimerHandle_t xTimer)
{
	LED_BLUE_TOGGLE();
	write_flag = 1;
}


static void dacTask(void *pvParameters)
{
	static uint16_t i = 0;
    while(1)
    {
    	if (write_flag)
    	{
    		DAC_SetBufferValue(DAC0, 0U, dac_vals[i]);
    		printf ( "\n\r%d" , dac_vals[i]);
    		i++;
    		write_flag = 0;
    		if (i == 500)
    			i = 0;
    	}
    }
}

