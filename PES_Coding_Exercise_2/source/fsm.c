/*
 * @filename : fsm.c
 *
 *  @date : Feb 6, 2020
 *  @description : File containing finite state machines
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#include "fsm.h"

stateMachine_1 fsm1;

static uint8_t x[250], y[250], z[250];
static uint8_t x_avg = 0, x_max = 0, x_min = 0;
static uint8_t y_avg = 0, y_max = 0, y_min = 0;
static uint8_t z_avg = 0, z_max = 0, z_min = 0;
static uint8_t state_count = 0;

/* @brief : State driven state machine is used for fsm_1 with a polling method of reading I2C values	*/
void fsm_1(void)
{
	current_state = readAccelerometer;
	while(state_machine_1)
	{
		switch(current_state)
		{
			case readAccelerometer:
			{
				/*	Read accelerometer values using I2C (polling), probably create a separate function for this. I've made these variables global	*/
//				x[state_count] =
//				y[state_count] =
//				i2c_poll_accelerometer();

				/*	If read completed successfully	*/
				current_state = displayData;

				/*	If read is unsuccessful	*/
				current_state = sensorDisconnect;
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


void fsm_2(void)
{
	/*Function to read accelerometer data based on interrupt i2c method, store data in x[], y[] etc. (same as above)	*/
//	static void (*i2c_read_accelerometer_ptr) = &i2c_interrupt_accelerometer;
//	static void (*dataSort) = &sort_data;
//	static void (*dataDisplay) = &display_data;
//	static void (*nextStateDecision) = &state_decision;
//	static void (*endProgram) = &program_end;
	current_state = 0;
	void (*fsm_2_ptr_arr[]) = {&sort_data, &display_data, &state_decision, &program_end};

	while(state_machine_2)
	{

		(*fsm_2_ptr_arr[current_state]);
		current_state++;
		/*	If sensor is is disconnected in i2c_interrupt_read	*/
//		current_sate = 4;
	}



}

void fsm_3(void)
{

	current_state = 0;
	void (*fsm_3_ptr_arr[]) = {&sort_data, &display_data, &state_decision, &program_end};

	while(state_machine_3)
	{

		(*fsm_3_ptr_arr[current_state]);
		current_state++;
		/*	If sensor is is disconnected in i2c_interrupt_read	*/
//		current_sate = 4;
	}



}

void state_decision(void)
{
	state_count++;
//	delay_ms(3000);
	SysTick_delay(3);
	while (interrupt_clear == false)
	{
		cap_val = touch_scan();	//Obtaining capacitance slider value
	}
	interrupt_clear = false;

	if ((state_count == 6) | (cap_val < 5001))
	{
		if(state_count == 6)
		{
			state_count = 0;
		}
		if (state_machine_1)
		{
			state_machine_1 = 0;
			state_machine_2 = 1;
			state_machine_3 = 0;
		}
		if (state_machine_2)
		{
			state_machine_1 = 0;
			state_machine_2 = 0;
			state_machine_3 = 1;
		}
		if (state_machine_3)
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
	if(cap_val > 14500)
	{
		program_end();
	}
}
void display_data(void)
{
	printf("\n\rState Count = %d", state_count);
	printf("\n\rLatest Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x[state_count], y[state_count], z[state_count]);
	printf("\n\rAverage Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_avg, y_avg, z_avg);
	printf("\n\rMinimum Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_min, y_min, z_min);
	printf("\n\rMax Accelerometer Readings - \n\rX | Y | Z \n\r%d | %d | %d", x_max, y_max, z_max);
}

void sort_data(void)
{
	static uint8_t i = 0, j = 0, a = 0;
	uint16_t sum_x = 0, sum_y = 0, sum_z = 0;
	for (i = 0; i < state_count; ++i)
	{
		sum_x += x[i];
		sum_y += y[i];
		sum_z += z[i];

		for (j = i + 1; j < state_count; ++j)
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
	x_avg = (sum_x/state_count);

	y_max = y[state_count];
	y_min = y[0];
	y_avg = (sum_y/state_count);

	z_max = z[state_count];
	z_min = z[0];
	z_avg = (sum_z/state_count);

}

void program_end(void)
{
	state_machine_1 = 0;
	state_machine_2 = 0;
#if debug
	printf("In program_end state");
#endif
}


