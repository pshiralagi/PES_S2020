/**
 * @file    PES_Project_4.c
 * @brief   Application entry point for Project 4, using i2c and SPI in state machines
 * @author	pshiralagi, aprakash
 * @date	04/01/2020
 * @references:	https://stackoverflow.com/questions/252748/how-can-i-use-an-array-of-function-pointers
 *
 *
 */
#include "general.h"
bool state_machine_1, state_machine_2, state_machine_3;
uint8_t POST_test(void);
/*
 * Code Entry
 */
int main(void)
{
	/*	Board Initialization	*/
	board_init();
	/*	Blue LED On	*/
	Start_Test();
	/*	Initialize i2c	*/
	i2c_init();
	/*	Initialize SPI	*/
	Init_SPI1();
	/*	Initialize on board Accelerometer	*/
	acc_init();

	/*	POST, checks SPI	*/
	if(!(POST_test()))
		state_machine_1 = 0;//If POST fails

	while(state_machine_1 | state_machine_2 | state_machine_3)
	{
		fsm_1();
		fsm_2();
		fsm_3();
	}

	/*	If program runs correctly, it will only go hear when program ends	*/
	Fail_Test();//Red LED
	while(1);

}


/*
 * @brief : Power On Self Test verifies that the SPI loop is complete
 */
uint8_t POST_test(void)
{

	if(Test_SPI_Loopback()==1)
	{
		return 1;
	}
	return 0;
}
