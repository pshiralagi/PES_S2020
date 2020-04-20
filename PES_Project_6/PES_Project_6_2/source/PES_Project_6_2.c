/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 */

 
/**
 * @file    PES_project_6_2.c
 * @brief   Application entry point.
 * https://github.com/kylemanna/kinetis-sdk2/blob/master/boards/frdmkl43z/rtos_examples/freertos_swtimer/freertos_swtimer.c
 */




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
#include "DMA.h"
#include "dsp.h"

TimerHandle_t SwTimerHandle = NULL;
TimerHandle_t SwTimerHandle_2 = NULL;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
SemaphoreHandle_t xMutex;
static bool write_flag = 0, read_flag = 0, dsp_ready = 0;
uint8_t i = 0;
uint16_t dac_vals[50];
uint32_t adc_val = 0;
uint32_t min, max, avg, Sd;
void BOARD_Init(void);
static void SwTimerCallback(TimerHandle_t xTimer);
static void SwTimerCallback_2(TimerHandle_t xTimer);
static void dacTask(void *pvParameters);
static void adcTask(void *pvParameters);
static void dspTask(void *pvParameters);
/*
 * @brief   Application entry point.
 */
int main(void) {


    BOARD_Init();

    updateDACvals();
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LUT Updated:");
#endif


    /*assert(xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , NULL) == pdPASS);
    assert(xTaskCreate(adcTask,  "adcTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , NULL) == pdPASS);
    assert(xTaskCreate(dspTask, "dspTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) == pdPASS);*/
	xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+10, NULL, tskIDLE_PRIORITY+1 , NULL);
	xTaskCreate(adcTask,  "adcTask", configMINIMAL_STACK_SIZE+10, NULL, tskIDLE_PRIORITY+1 , NULL);
	xTaskCreate(dspTask, "dspTask", configMINIMAL_STACK_SIZE+10, NULL, tskIDLE_PRIORITY+1, NULL);
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
    SwTimerHandle_2 = xTimerCreate("SwTimer2",
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
			src_adc[i] = adc_val;
			i++;
			if(i==64){
				i=0;
				DMA_transfer();
				dsp_ready = 1;
			}
//			q_add(&adc_val); //Updating the ADC value to the ADC buffer
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, ADCtask, "ADC Value:");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, ADCtask, "");
#endif
    		Log_Integer(adc_val);


		}
	}
}

static void dspTask(void *pvParameters)
{
	while(1)
	{
		if (dsp_ready)
		{
			dsp_ready = 0;
			min = minimum(dest_adc);
			max = largest(dest_adc);
			avg = average(dest_adc);
			Sd = calculateSD(dest_adc);
	#ifdef DEBUG_MODE
				log_func_Str(DebugMode, DSPtask, "MAX \t MIN \t AVG \t Standard Deviation");
				Log_string("\n\r");
				Log_Integer(max);
				Log_string("\t");
				Log_Integer(min);
				Log_string("\t");
				Log_Integer(avg);
				Log_string("\t");
				Log_Integer(Sd);
	#endif
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

//    q_init(64, 32);



}
