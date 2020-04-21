/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * @file    PES_project_6_2.c
 * @author	Pavan Shiralagi and Antara Prakash
 * @brief   Application entry point.
 *  @reference https://github.com/kylemanna/kinetis-sdk2/blob/master/boards/frdmkl43z/rtos_examples/freertos_swtimer/freertos_swtimer.c
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

TaskHandle_t xdacTaskHandle = NULL;
TaskHandle_t xadcTaskHandle = NULL;
TimerHandle_t dacTimerHandle = NULL;
TimerHandle_t adcTimerHandle = NULL;
adc16_config_t adc16ConfigStruct;
adc16_channel_config_t adc16ChannelConfigStruct;
SemaphoreHandle_t xMutex;
const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
static bool write_flag = 0, read_flag = 0, dsp_ready = 0;

uint16_t dac_vals[50];
uint32_t adc_val = 0;
uint32_t min, max, avg, Sd;
void BOARD_Init(void);
static void dacTimerCallback(TimerHandle_t xTimer);
static void adcTimerCallback(TimerHandle_t xTimer);
static void dacTask(void *pvParameters);
static void adcTask(void *pvParameters);
static void dspTask(void *pvParameters);
/*
 * @brief   Application entry point.
 */
int main(void) {


    BOARD_Init();
    LED_BLUE_INIT(1);
    LED_RED_INIT(1);
    LED_GREEN_INIT(1);
    updateDACvals();
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LUT Updated:");
#endif


    assert(xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , &xdacTaskHandle) == pdPASS); 	/*RED LED switched on if assert fails*/
    assert(xTaskCreate(adcTask,  "adcTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1 , &xadcTaskHandle) == pdPASS);
    assert(xTaskCreate(dspTask, "dspTask", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY+1, NULL) == pdPASS);

    vTaskStartScheduler();


    while(1);

}



static void dacTimerCallback(TimerHandle_t xTimer)
{
	 xSemaphoreTake(xMutex, portMAX_DELAY);
	 LED_BLUE_OFF();
	LED_GREEN_TOGGLE();
	xSemaphoreGive(xMutex);
	write_flag = 1;
	timer_calculation();
}

static void adcTimerCallback(TimerHandle_t xTimer)
{
	read_flag = 1;

}

/*DAC Task*/
static void dacTask(void *pvParameters)
{
	static uint16_t i = 0;
    dacTimerHandle = xTimerCreate("dacTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     dacTimerCallback);
    xTimerStart(dacTimerHandle, 0);
    while(1)
    {
    	if (write_flag)
    	{
    		DAC_SetBufferValue(DAC0, 0U, dac_vals[i]);
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, DACtask, "DAC Value:");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, null, "");
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
    		log_func_Str(NormalMode, null, "*********Wave Generation Complete*************");
#endif
    		}

    	}
    }
}

/* ADC task*/
static void adcTask(void *pvParameters)
{
	static uint8_t i = 0;
	memset(src_adc, 0, sizeof(src_adc));
    adcTimerHandle = xTimerCreate("adcTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     adcTimerCallback);
    xTimerStart(adcTimerHandle, 0);
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
			q_copy(&src_adc[i]);
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, ADCtask, "ADC Value:");
#endif
#ifdef NORMAL_MODE
    		log_func_Str(NormalMode, null, "");
#endif
    		Log_Integer(adc_val);
			i++;
			if(i==64){
				i=0;
				xSemaphoreTake(xMutex, portMAX_DELAY);
				LED_GREEN_OFF();
				LED_BLUE_TOGGLE();
				vTaskDelay( xDelay );
				xSemaphoreGive(xMutex);
				DMA_transfer();
				LED_BLUE_OFF();
				q_reset();
				memset(src_adc, 0, sizeof(src_adc));
				dsp_ready = 1;
			}

		}
	}
}
/* DSP Task */
static void dspTask(void *pvParameters)
{
	static uint8_t run_count = 1;

	while(1)
	{
		if (dsp_ready)
		{
			dsp_ready = 0;
			min = minimum(dest_adc);
			max = largest(dest_adc);
			avg = average(dest_adc);
			Sd = calculateSD(dest_adc);
#ifdef NORMAL_MODE
			log_func_Str(NormalMode, DSPtask, "MAX \t MIN \t AVG \t Standard Deviation");
			Log_string("\n\r");
			Log_Integer(max);
			Log_string("\t");
			Log_Integer(min);
			Log_string("\t");
			Log_Integer(avg);
			Log_string("\t");
			Log_Integer(Sd);
#endif
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
				log_func_Str(DebugMode, DSPtask, "Run Number of DSP task ");
				Log_Integer(run_count);
	#endif
				run_count++;
				if (run_count == 6)
				{
#ifdef DEBUG_MODE
					log_func_Str(DebugMode, DSPtask, "DSP task has run 5 times, ending all tasks ");
#endif
					xTimerDelete(adcTimerHandle,0);
					xTimerDelete(dacTimerHandle,0);
					vTaskDelete(xdacTaskHandle);
					vTaskDelete(xadcTaskHandle);
					vTaskDelete(NULL);
					vTaskEndScheduler();
				}
		}
	}
}

/*
 * Board Initialization functions
 */
void BOARD_Init(void)
{
  	/* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();
    SystemCoreClockUpdate();
    xMutex = xSemaphoreCreateMutex();


#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LEDs initialized:");
#endif
    LED_BLUE_INIT(1);
    LED_GREEN_INIT(1);
    LED_RED_INIT(1);

#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "DACinitialized:");
#endif
    dacInit();

#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "ADC initialized:");
#endif
    adcInit();

#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "DMA initialized:");
#endif
    dma_init();

#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "Queue to store ADC values initialized");
#endif
    q_init(64, 4);

}
