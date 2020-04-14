/**
 * @file    PES_Project_5.c
 * @brief   Application entry point for Project 5, using UART and circular buffers
 * @author	pshiralagi, aprakash
 * @date	04/01/2020
 * @references:	https://github.com/peterfillmore/frdm-kl25z-exploit-practice-code/blob/master/uart.c
 * https://github.com/manuelnaranjo/bare-metal-arm-frdm-kl25z/blob/master/common.h
 * http://www.simplyembedded.org/tutorials/interrupt-free-ring-buffer/
 * https://github.com/alexander-g-dean/ESF/tree/master/Code
 *
 *
 */
#include "general.h"
void buffers_init(void);

/*
 * Code Entry
 */
int main(void)
{
	/*	Board Initialization	*/

	board_init();
	printf("\n\rProgram Start");
	buffers_init();
	Start_Test();
	SysTick_delay();

#ifdef TEST_MODE
	unit_test();
#endif
	/*----------------------------------------------------------------------------
	  MAIN function

		Change definition of USE_UART_INTERRUPTS in UART.h to select polled or
		interrupt-driven communication.
		 *----------------------------------------------------------------------------*/

		Init_UART0(115200);	//initializing UART to 115200 baud rate
#ifdef ECHO_MODE

	 	log_func_Str(DebugMode, mainfunc, "Echo Mode");
	#if USE_UART_INTERRUPTS==0// Polling version of code
#ifdef NORMAL_MODE
	 	log_func_Str(normalmode, mainfunc, "Polling mode UART");
#endif
#ifdef DEBUG_MODE
	 	log_func_Str(DebugMode, mainfunc, "Polling mode UART");
#endif

		while (1) {
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "Echoed Character");
#endif
			uart_echo_blocking(); //Echo's back the characters
			Success_Test();

		}
	#elif USE_UART_INTERRUPTS==1 // Interrupt version of code
#ifdef NORMAL_MODE
	 	log_func_Str(normalmode, mainfunc, "Interrupt mode UART");
#endif
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "Interrupt mode UART mode");
#endif
		while (1) {
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "Echoed Character");
#endif
			uart_echo(); //Echo's back the characters
			Success_Test();
		}
	#endif
#endif

#ifdef APPLICATION_MODE
#ifdef NORMAL_MODE
		log_func_Str(normalmode, mainfunc, "Application Mode");
#endif
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "Application Mode");
#endif
#if USE_UART_INTERRUPTS==0 // Polling version of code
#ifdef NORMAL_MODE
		log_func_Str(normalmode, mainfunc, "UART Application mode Polling");
#endif
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "UART Application mode Polling");
#endif
		while(1){
#ifdef DEBUG_MODE
			log_func_Str(DebugMode, uartappmode, "Character Read");
#endif
			uart_app_mode(); //application mode function
		}
#elif USE_UART_INTERRUPTS==1 // Interrupt version of code
#ifdef NORMAL_MODE
		log_func_Str(normalmode, mainfunc, "UART Application mode interrupt");
#endif
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, mainfunc, "UART Application mode interrupt");
#endif
		while(1){
#ifdef DEBUG_MODE
			log_func_Str(DebugMode, uartappmodeint, "Character Read");
#endif
			uart_app_mode_int(); //application mode function
		}
#endif

#endif
	while(1);

}


/**********initializing buffer size************/
void buffers_init(void)
{
	START_CRITICAL();
	Tx = malloc(sizeof(buffer_t));
	Rx = malloc(sizeof(buffer_t));
	END_CRITICAL();
	init_buffer(Rx, 100);
	init_buffer(Tx, 100);
}
