/*
 * @filename : fsm.c
 *
 *  @date : Feb 6, 2020
 *  @description : File containing finite state machines
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#include "fsm.h"

static uint8_t current_state;
volatile uint32_t cap_val;
stateMachine_1 fsm1;
bool interrupt_clear;
static uint16_t x[10], y[10], z[10];
static uint16_t x_avg = 0, x_max = 0, x_min = 0, x_curr = 0;
static uint16_t y_avg = 0, y_max = 0, y_min = 0, y_curr = 0;
static uint16_t z_avg = 0, z_max = 0, z_min = 0, z_curr = 0;
static uint8_t state_count = 0;
static uint32_t sum_x = 0, sum_y = 0, sum_z = 0;

/* @brief : State driven state machine is used for fsm_1 with a polling method of reading I2C values	*/
void fsm_1(void)
{
	Success_Test();
	current_state = readAccelerometer;
	while(state_machine_1)
	{


#ifdef DEBUG_MODE
		log_func_Str(DebugMode, fsm1_, "State Machine 1");
#endif
#ifdef TEST_MODE
		log_func_Str(Test, fsm1_, "State Machine 1");
#endif
		switch(current_state)
		{
			case readAccelerometer:
			{
				read_full_xyz();
				/*	Read accelerometer values using I2C (polling), probably create a separate function for this. I've made these variables global	*/
				x[state_count] =	acc_X;
				y[state_count] =	acc_Y;
				z[state_count] =	acc_Z;

				//i2c_poll_accelerometer();
				//read_xyz();
				/*	If read completed successfully	*/

				current_state = displayData;

				/*	If read is unsuccessful	*/
				//current_state = sensorDisconnect;
				break;
			}
			case displayData:
			{
				sort_data();
				display_data();
				current_state = pollSlider;
				break;
			}
			case pollSlider:
			{
				state_decision();
				break;
			}
			case sensorDisconnect:
			{
				program_end();
				break;

			}


		}
	}
}

/*
 * @brief	fsm2 is the same as fsm1 but uses a table driven state machine to implement interrupt driven i2c
 */
void (*fsm_2_ptr_arr[5])() = {i2c_interrupt_accelerometer, sort_data, display_data, state_decision, program_end};
void fsm_2(void)
{
	Success_Test();

	if(state_machine_2)
	{
#ifdef DEBUG_MODE
	log_func_Str(DebugMode, fsm2, "State machine 2");
#endif
#ifdef TEST_MODE
	log_func_Str(Test, fsm2, "State machine 2");
#endif
	}

	current_state = 0;
	while(state_machine_2)
	{

		(*fsm_2_ptr_arr[current_state])();
		current_state++;
		/*	If sensor is is disconnected in i2c_interrupt_read	*/
//		current_sate = 4;
	}



}
/*
 * @brief	fsm3 uses a table driven state machine to implement SPI loopback
 */
void (*fsm_3_ptr_arr[2])() = {spi_count, state_decision};
void fsm_3(void)
{
	Success_Test();
	////SPI only
	current_state = 0;
	if(state_machine_3)
	{
#ifdef DEBUG_MODE
		log_func_Str(DebugMode, fsm3, "State Machine 3");
#endif
#ifdef TEST_MODE
		log_func_Str(Test, fsm3, "State Machine 3");
#endif
	}

	while(state_machine_3)
	{


		(*fsm_3_ptr_arr[current_state])();
		current_state++;
	}



}

/*
 * @brief	SPI loopback function
 */
void spi_count(void){
	if(Test_SPI_Loopback()){
		Success_Test();
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, spicount, "Data Received on loopback");
	#endif
	#ifdef TEST_MODE
		log_func_Str(Test, spicount, "Data Received on loopback");
	#endif

	}else{
		Fail_Test();
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, spicount, "Data not Received on loopback");
	#endif
	#ifdef TEST_MODE
		log_func_Str(Test, spicount, "Data not Received on loopback");
	#endif
	}
}

/*
 * @brief	interrupt driven i2c
 */
void i2c_interrupt_accelerometer(){
	I2C_Master_Transmit();
	x[state_count] =	acc_X;
	y[state_count] =	acc_Y;
	z[state_count] =	acc_Z;
}

/*
 * @brief Making a decision on next state based on previous state, state machine number and capacitive touch value
 */
void state_decision(void)
{
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, statedecision, "Deciding State number");
	#endif
	#ifdef TEST_MODE
		log_func_Str(Test, statedecision, "Deciding State number");
	#endif
	if(state_machine_1 | state_machine_2)
		state_count++;
//	delay_ms(3000);
	SysTick_delay(3);
	while (interrupt_clear == false)
	{
		cap_val = touch_scan();	//Obtaining capacitance slider value
		wait_ms(50);


	}
	interrupt_clear = false;

	if ((state_count == 6) | ((cap_val < 5001) & (cap_val > 500)))
	{
		if(state_count == 6)
		{
			state_count = 0;
			sum_x = 0;
			sum_y = 0;
			sum_z = 0;
		}
		if (state_machine_1)
		{

			state_machine_1 = 0;
			state_machine_2 = 1;
			state_machine_3 = 0;
		}
		else if (state_machine_2)
		{

			state_machine_1 = 0;
			state_machine_2 = 0;
			state_machine_3 = 1;
		}
		else if (state_machine_3)
		{

			state_machine_1 = 1;
			state_machine_2 = 0;
			state_machine_3 = 0;
		}

	}
	else if ((1 <= state_count) & (state_count <= 5))
	{
		current_state = readAccelerometer;
	}
	else if(state_machine_3)
	{
		state_machine_1 = 1;
		state_machine_2 = 0;
		state_machine_3 = 0;
	}
	if(cap_val > 10500)
	{
		program_end();

	}
}

/*
 * @brief	Function to display accelerometer data
 */
void display_data(void)
{
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, displaydata, "Following Data");
	#endif
	#ifdef TEST_MODE
		log_func_Str(Test, displaydata, "Following Data");
	#endif

	printf("\n\rState Count = %d", state_count);
	printf("\n\rLatest Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_curr, y_curr, z_curr);
	printf("\n\rAverage Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_avg, y_avg, z_avg);
	printf("\n\rMinimum Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_min, y_min, z_min);
	printf("\n\rMax Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_max, y_max, z_max);
}

/*
 * @brief	Function to sort accelerometer data
 */
void sort_data(void)
{
	#ifdef DEBUG_MODE
	log_func_Str(DebugMode, sortdata, "Data sorting");
	#endif
	#ifdef TEST_MODE
	log_func_Str(Test, sortdata, "Data sorting");
	#endif
	x_curr = acc_X;
	y_curr = acc_Y;
	z_curr = acc_Z;

	sum_x += x_curr;
	sum_y += y_curr;
	sum_z += z_curr;
	static uint8_t i = 0, j = 0;
	static uint16_t a = 0;
		for (i = 0; i <= state_count; i++)
		{


			for (j = i + 1; j <= state_count; j++)
			{

				if (x[i] > x[j])
				{

					a =  x[i];
					x[i] = x[j];
					x[j] = a;

				}
				if (y[i] > y[j])
				{

					a =  y[i];
					y[i] = y[j];
					y[j] = a;

				}
				if (z[i] > z[j])
				{

					a =  z[i];
					z[i] = z[j];
					z[j] = a;

				}

			}
	}

	x_max = x[state_count];
	x_min = x[0];
	x_avg = (sum_x/(state_count+1));

	y_max = y[state_count];
	y_min = y[0];
	y_avg = (sum_y/(state_count+1));

	z_max = z[state_count];
	z_min = z[0];
	z_avg = (sum_z/(state_count+1));

}

/*
 * @brief	Function to end program
 */
void program_end(void)
{
	state_machine_1 = 0;
	state_machine_2 = 0;
	state_machine_3 = 0;
#ifdef STATUS
		log_func_Str(Status, statusmode , "");
		Log_string("Program Ended");
	#endif
#ifdef DEBUG_MODE
	log_func_Str(DebugMode, programend, "End of State machine");
#endif
#ifdef TEST_MODE
	log_func_Str(Test, programend, "End of State machine");
#endif
}


