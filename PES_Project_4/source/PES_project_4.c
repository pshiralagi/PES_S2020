/**
 * @file    PES_Project_4.c
 * @brief   Application entry point.
 *
 *
 *	Things to do -
 *
 *	Antara :
 *	1. Add i2c_polling function in fsm_1 (create i2c.c and i2c.h files) - On board
 *	2. Add i2c interrupt function in fsm_2
 *	3. Add POST_test
 *	4. Add LED control (blue LED on in POST_test, green in normal states, red if LIS 331 is disconnected
 *	5. Read accelerometer using SPI in fsm_3 (create spi.c and spi.h files) - Loopback
 *	6. Logger Extensions (create logger.c and logger.h files) (apparently you ned to build on work done for project 3)
 *	7. Add CUnittests (in test mode)
 *	8. Add debug messages using logger (debug mode)
 *	9. Add those defines in general.h
 *	10. Check if the systick irq initialization stuff makes sense
 *
 *	Moi :
 *	10. Take and annotate scope measurements for i2c
 *	11. Create Readme
 *	12. Comment code
 *
 *
 *
 *
 *
 *
 */
#include "general.h"

int main(void)
{
	board_init();
//	POST_test();

	while(state_machine_1 | state_machine_2 | state_machine_3)
	{
		fsm_1();
		fsm_2();
		fsm_3();
	}

	/*	If program runs correctly, it will only go hear when program ends	*/
	while(1);

}
