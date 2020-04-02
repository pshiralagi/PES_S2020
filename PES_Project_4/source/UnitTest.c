/*
 * UnitTest.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Antara and Pavan
 *      /


 ***************************************** References **************************************************
 * https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
 ********************************************************************************************************/

/***********************************************************************************
 * UNIT TESTING [1]
 ***********************************************************************************/


#include "UnitTest.h"





/********* Unit Test function definition *********/

#define ADDRESS 0x3A
#define REG_CTRL1 0x2A
#define REG_XHI 0x01

void unit_test(void){

		uint8_t status;
		uint16_t data;
		int i=0;
    	/************ Initialization *************/
		UCUNIT_Init();	//initialize framework

		/****************I2C Init********************/
		i2c_init();	//
		log_func_Str(Test, initmma, "Initializing I2C");
		UCUNIT_TestcaseBegin("Initializing I2C");
		//UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/*****************SPI INIT******************/
		Init_SPI1();	//
		log_func_Str(Test, initmma, "Initializing SPI");
		UCUNIT_TestcaseBegin("Initializing SPI");
		//UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/********** I2C Read test **********/
		status = i2c_read_byte(ADDRESS, REG_XHI);
		UCUNIT_TestcaseBegin("I2C read");
		log_func_Str(Test, i2creadbyte, "reading data");
		if(status > 0){
			i = 1;
		}
		UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/********** Accelerometer initialization **********/
		init_mma();
		log_func_Str(Test, initmma, "Initializing accelerometer");
		UCUNIT_TestcaseBegin("Initializing accelerometer");
		//UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/************ Read full Xyz**********************/
		read_full_xyz();
		log_func_Str(Test, initmma, "READING XYZ");
		UCUNIT_TestcaseBegin("READING XYZ");
		UCUNIT_TestcaseEnd();

		/************** Accelerometer Read X*************/
		data = readx();
		log_func_Str(Test, readx_, "READ X");
		UCUNIT_TestcaseBegin("READ X");
		if(data >= 0){
			i = 1;
		}
		UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/************** Accelerometer Read Y*************/
		data = ready();
		log_func_Str(Test, ready_, "READ Y");
		UCUNIT_TestcaseBegin("READ Y");
		if(data >= 0){
			i = 1;
		}
		UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/************** Accelerometer Read Z*************/
		data = readz();
		log_func_Str(Test, readz_, "READ Z");
		UCUNIT_TestcaseBegin("READ Z");
		if(data >= 0){
			i = 1;
		}
		UCUNIT_CheckIsEqual(i, 1);
		UCUNIT_TestcaseEnd();

		/*********** Touch Screen Test ************/
    	data = touch_scan();
    	log_func_Str(Test, touchscan, "capacitive touch test");
    	UCUNIT_TestcaseBegin("Capacitive Touch");
    	if(data >= 0){
    		i = 1;
    	}
    	UCUNIT_CheckIsEqual(i, 1);
    	UCUNIT_TestcaseEnd();
    	/***************SPI Loopback*******************/

    	status = Test_SPI_Loopback();
    	UCUNIT_TestcaseBegin("SPI Loopback");
    	log_func_Str(Test, TestSPILoopback, "reading data through SPI");
    	UCUNIT_CheckIsEqual(status, 1);
    	UCUNIT_TestcaseEnd();

    	/************************************************/


		/*** Test Shutdown ****/
		UCUNIT_WriteSummary();
		if(ucunit_testcases_failed == 0)
			Success_Test();
		else
			Fail_Test();
		UCUNIT_Shutdown();
	}

