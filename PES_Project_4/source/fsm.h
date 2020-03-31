/*
 * @filename : fsm.h
 *
 *  @date : Feb 6, 2020
 *  @description : Header file for fsm.c
 *
 *    	@author : Pavan Shiralagi and Antara Prakash
 */

#ifndef fsm_h_
#define fsm_h_

	//Includes
#include "general.h"

typedef enum {
	readAccelerometer,
	displayData,
	pollSlider,
	sensorDisconnect,
	numStates
}stateMachine_1;//States for first state machine


void display_data(void);
void sort_data(void);
void program_end(void);
void fsm_1(void);
void fsm_2(void);
void fsm_3(void);
void state_decision(void);
void i2c_interrupt_accelerometer(void);
void spi_count(void);
extern bool state_machine_1, state_machine_2, state_machine_3;


#endif
