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


/*
 *
 *
 *
• Verify wrap remove (test that your buffer tail point can wrap around the edge boundary when a remove occurs at the boundary)
• Verify wrap add (test that your buffer can wrap around the edge boundary and add to the front)
 *
 *
 */


/********* Unit Test function definition *********/

void unit_test(void){

		//uint8_t buffer_size;
		buffer_t *q;
		uint8_t size = 2;
		uint8_t data1 = 15;
		uint8_t data2 = 16;
		uint8_t data3 = 17;
		buffer_status status;
		q = malloc(sizeof(buffer_t));
    	/*********** Initialization ************/
		UCUNIT_Init();	//initialize framework

		/***************Buffer Init*******************/
		status = init_buffer(q,size);	//initialize buffer
		log_func_Str(Test, initbuffer, "Initializing Circular Buffer");
		UCUNIT_TestcaseBegin("Initializing Circular Buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/****************bufferAdd*****************/
		status = bufferAdd(q,data1);	//
		log_func_Str(Test, bufferAdd_, "Adding data in the buffer");
		UCUNIT_TestcaseBegin("Adding data in the buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/********* bufferAdd ***********/
		status = bufferAdd(q,data2);	//
		log_func_Str(Test, bufferAdd_, "Adding data in the buffer");
		UCUNIT_TestcaseBegin("Adding data in the buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/************* isBufferFull ************/
		status = isBufferFull(q);	//
		log_func_Str(Test, isBufferFull_, "Checking if buffer full");
		UCUNIT_TestcaseBegin("Checking if buffer full");
		UCUNIT_CheckIsEqual(status, 1);
		UCUNIT_TestcaseEnd();

		/************* bufferAdd ************/
		status = bufferAdd(q,data3);	//
		log_func_Str(Test, bufferAdd_, "Adding data in the buffer");
		UCUNIT_TestcaseBegin("Adding data in the buffer");
		UCUNIT_CheckIsEqual(status, 1);
		UCUNIT_TestcaseEnd();

		/******************bufferRemove*********************/
		status = bufferRemove(q,&data3);
		log_func_Str(Test, bufferRemove_, "Removing data from the buffer");
		UCUNIT_TestcaseBegin("Removing data from buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_CheckIsEqual(data3, data1);
		UCUNIT_TestcaseEnd();
		/************ isBufferFull ***********/
		status = bufferExtendAdd(q,data3);
		log_func_Str(Test, isBufferFull_, "Checking if buffer full");
		UCUNIT_TestcaseBegin("Checking if buffer full");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();
		/************ isBufferFull ***********/
		status = bufferExtendAdd(q, data3);
		log_func_Str(Test, isBufferFull_, "Checking if buffer full");
		UCUNIT_TestcaseBegin("Checking if buffer full");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/******************bufferRemove*********************/
		status = bufferRemove(q,&data3);
		log_func_Str(Test, bufferRemove_, "Removing data from the buffer");
		UCUNIT_TestcaseBegin("Removing data from buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/******************bufferRemove*********************/
		status = bufferRemove(q,&data2);
		log_func_Str(Test, bufferRemove_, "Removing data from the buffer");
		UCUNIT_TestcaseBegin("Removing data from buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_CheckIsEqual(data2, data3);
		UCUNIT_TestcaseEnd();

		/************* bufferRemove************/
		status = bufferRemove(q,&data1);
		log_func_Str(Test, bufferRemove_, "Removing data from the buffer");
		UCUNIT_TestcaseBegin("Removing data from buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_CheckIsEqual(data1, data3);
		UCUNIT_TestcaseEnd();

		/************* isBufferEmpty************/
		status = isBufferEmpty(q);
		log_func_Str(Test, isBufferEmpty_, "Checking if buffer is empty");
		UCUNIT_TestcaseBegin("Checking if buffer is empty");
		UCUNIT_CheckIsEqual(status, 2);
		UCUNIT_TestcaseEnd();

		/************* bufferRemove ************/
		status = bufferRemove(q,&data1);
		log_func_Str(Test, bufferRemove_, "Removing data from the empty buffer");
		UCUNIT_TestcaseBegin("Removing data from empty buffer");
		UCUNIT_CheckIsEqual(status, 2);
		UCUNIT_TestcaseEnd();

		/********** destroy_buffer ***********/
		status = destroy_buffer(q);	//
		log_func_Str(Test, bufferRemove_, "Destroying circular buffer");
		UCUNIT_TestcaseBegin("Destroying circular buffer");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/**** Test Shutdown ****/
		UCUNIT_WriteSummary();
		if(ucunit_testcases_failed == 0)
			Success_Test();
		else
			Fail_Test();
		UCUNIT_Shutdown();
	}

