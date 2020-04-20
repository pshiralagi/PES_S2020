/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 */
 
/**
 * @file    PES_project_6_1.c
 * @author	Pavan and Antara
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
#include "timer.h"
#include "log.h"



static bool write_flag = 0;
uint16_t dac_vals[50];
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
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "Blue LED initialized:");
#endif

    LED_BLUE_INIT(1);
    updateDACvals();
#ifdef DEBUG_MODE
    		log_func_Str(DebugMode, mainFunction, "LUT Updated:");
#endif


    dacInit();
    SwTimerHandle = xTimerCreate("SwTimer",
        							 pdMS_TO_TICKS(100),
                                     pdTRUE,
                                     0,
                                     SwTimerCallback);
    xTimerStart(SwTimerHandle, 0);
    assert(xTaskCreate(dacTask,  "dacTask", configMINIMAL_STACK_SIZE+10, NULL, tskIDLE_PRIORITY+1 , NULL) == pdPASS);
    vTaskStartScheduler();
    LED_RED_ON();
    while(1);

}


/*
 * @brief	Timer IRQ called once every 0.1 second
 * @param	Timer handle
 */
static void SwTimerCallback(TimerHandle_t xTimer)
{
	LED_BLUE_TOGGLE();
	write_flag = 1;
	timer_calculation();
}

/*
 * @brief	Task to update DAC pin voltages based on LUT
 */
static void dacTask(void *pvParameters)
{
	static uint16_t i = 0;
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

