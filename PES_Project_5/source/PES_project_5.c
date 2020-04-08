/**
 * @file    PES_Project_5.c
 * @brief   Application entry point for Project 5, using UART and circular buffers
 * @author	pshiralagi, aprakash
 * @date	04/01/2020
 * @references:	https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
 * https://community.nxp.com/thread/319111
 * https://github.com/alexander-g-dean/ESF/tree/master/Code/Chapter_8/I2C-Demo
 *
 *
 */
#include "general.h"
bool state_machine_1, state_machine_2, state_machine_3;
uint8_t POST_test(void);
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

		// Code listing 8.9, p. 233
		while (1) {
			uart_echo_blocking();
		}
	#elif USE_UART_INTERRUPTS==1 // Interrupt version of code
		Send_String("\n\rHello, World!\n\r");

		// Code listing 8.10, p. 234
		while (1) {
			uart_echo();
		}
	#endif


	while(1);

}


/*
 * @brief : Power On Self Test verifies that the SPI loop is complete
 */
uint8_t POST_test(void)
{
	if(Test_SPI_Loopback()==1)
	{
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, POST, "Test Passed");
#endif
		return 1;
	}
	return 0;
}



void buffers_init(void)
{
	Tx = malloc(sizeof(buffer_t));
	Rx = malloc(sizeof(buffer_t));
	init_buffer(Rx, 100);
	init_buffer(Tx, 100);
}
