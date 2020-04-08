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

	/*----------------------------------------------------------------------------
	  MAIN function

		Change definition of USE_UART_INTERRUPTS in UART.h to select polled or
		interrupt-driven communication.
		 *----------------------------------------------------------------------------*/

		Init_UART0(115200);

	 	printf("\n\rGood morning!\n\r");

	#if USE_UART_INTERRUPTS==0// Polling version of code
		Send_String_Poll("\n\rHello, World!\n\r");

		while (1) {
			uart_echo_blocking();
		}
	#elif USE_UART_INTERRUPTS==1 // Interrupt version of code
		Send_String("\n\rHello, World!\n\r");
		while (1) {
			uart_echo();
		}
	#endif


	while(1);

}



void buffers_init(void)
{
	Tx = malloc(sizeof(buffer_t));
	Rx = malloc(sizeof(buffer_t));
	init_buffer(Rx, 100);
	init_buffer(Tx, 100);
}
