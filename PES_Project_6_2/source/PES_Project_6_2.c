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
 * @file    PES_project_6_2.c
 * @brief   Application entry point.
 * https://github.com/kylemanna/kinetis-sdk2/blob/master/boards/frdmkl43z/rtos_examples/freertos_swtimer/freertos_swtimer.c
 */


#define NORMAL_MODE
//#define DEBUG_MODE

#include <stdio.h>
#include <assert.h>
#include <myq.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "fsl_dac.h"
#include "fsl_adc16.h"
#include "FreeRTOS.h"
#include "adc_dac.h"
#include "timers.h"
#include "task.h"
#include "timer.h"
#include "log.h"
#include "semphr.h"
#include "myq.h"

TimerHandle_t SwTimerHandle = NULL;
TimerHandle_t SwTimerHandle_2 = NULL;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
SemaphoreHandle_t xMutex;
static bool write_flag = 0, read_flag = 0;
uint16_t dac_vals[50];
uint32_t adc_val = 0;
void BOARD_Init(void);
static void SwTimerCallback(TimerHandle_t xTimer);
static void SwTimerCallback_2(TimerHandle_t xTimer);
static void dacTask(void *pvParameters);
static void adcTask(void *pvParameters);
/*
 * @brief   Application entry point.
 */
int main(void) {


    BOARD_Init();

    updateDACvals();
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LUT Updated:");
#endif


    xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , NULL);
    xTaskCreate(adcTask,  "adcTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , NULL);
    vTaskStartScheduler();

    while(1);

}



static void SwTimerCallback(TimerHandle_t xTimer)
{
//	LED_BLUE_TOGGLE();
	write_flag = 1;
	timer_calculation();
}

static void SwTimerCallback_2(TimerHandle_t xTimer)
{
	read_flag = 1;
}


static void dacTask(void *pvParameters)
{
	static uint16_t i = 0;
    SwTimerHandle = xTimerCreate("SwTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     SwTimerCallback);
    xTimerStart(SwTimerHandle, 0);
    while(1)
    {
    	if (write_flag)
    	{
    		DAC_SetBufferValue(DAC0, 0U, dac_vals[i]);
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, DACtask, "DAC Value:");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, DACtask, "");
#endif
    		Log_Integer(dac_vals[i]);
    		i++;
    		write_flag = 0;
    		if (i == 50)
    		{
    			i = 0;
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, DACtask, "*********Wave Generation Complete*************");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, DACtask, "*********Wave Generation Complete*************");
#endif
    		}

    	}
    }
}


static void adcTask(void *pvParameters)
{
    SwTimerHandle_2 = xTimerCreate("SwTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     SwTimerCallback_2);
    xTimerStart(SwTimerHandle_2, 0);
	while(1)
	{
		if (read_flag)
		{
		    ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
			while (0U == (kADC16_ChannelConversionDoneFlag &
						  ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)));
			adc_val = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);  //Obtain ADC value
			read_flag = 0;

			q_add(&adc_val); //Updating the ADC value to the ADC buffer
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, DACtask, "DAC Value:");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, DACtask, "");
#endif
    		Log_Integer(adc_val);


		}
	}
}

void BOARD_Init(void)
{
  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    SystemCoreClockUpdate();
    xMutex = xSemaphoreCreateMutex();
//    xSemaphoreTake(xMutex, portMAX_DELAY);
//    xSemaphoreGive(xMutex);

#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LEDs initialized:");
#endif
    LED_BLUE_INIT(1);
    LED_GREEN_INIT(1);
    LED_RED_INIT(1);

    dacInit();

    adcInit();

    q_init(64, 32);



}
