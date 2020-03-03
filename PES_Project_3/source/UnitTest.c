/*
 * UnitTest.c
 *
 *  Created on: Mar 2, 2020
 *      Author: Antara and Pavan

/***************************************** References **************************************************
https://mcuoneclipse.com/2018/08/26/tutorial-%CE%BCcunit-a-unit-test-framework-for-microcontrollers/
********************************************************************************************************/

/***********************************************************************************
 * UNIT TESTING [1]
 ***********************************************************************************/

/********* Standard Header Files *********/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/********* User defined Header Files *********/
#include "allocate_bytes.h"
#include "general.h"
#include "logger.h"
#include "memory.h"
#include "pattern.h"
#include "uCUnit.h"


/********* Unit Test function definition *********/
void unit_test(void)
{
		log_disable();
		mem_status status;
		struct data_type type;
		type.offset = 9;
		type.length = 2;
		type.size = 16;
		type.value = 0xFFEE;
		type.seed = 143;


    	/************ Memory allocation *************/
    	status = allocate_memory(type);

    	/************ Pattern write to memory *************/
    	status = write_pattern(type);
    	UCUNIT_Init(); /* initialize framework */
    	UCUNIT_TestcaseBegin("Pattern Write to Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		status = compare_pattern(type);
		UCUNIT_TestcaseBegin("Pattern Verification after writing a new pattern");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/********** Writing 0xFFEE to the memory ***********/
		status = write_memory(type);
		UCUNIT_TestcaseBegin("First Data 0xFFEE written to Memory");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		status = compare_pattern(type);
		UCUNIT_TestcaseBegin("Pattern Verification after changing the data in memory");
		UCUNIT_CheckIsEqual(status, 1);
		UCUNIT_TestcaseEnd();

    	/************ Pattern write to memory *************/
    	status = write_pattern(type);
    	UCUNIT_TestcaseBegin("Pattern Write to Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		status = compare_pattern(type);
		UCUNIT_TestcaseBegin("Pattern Verification after writing a new pattern");
		UCUNIT_CheckIsEqual(status, 1);
		UCUNIT_TestcaseEnd();

	    /********** Inverting the memory ***********/
	    status = invert_block(type);
    	UCUNIT_TestcaseBegin("Inverting Memory");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		status = compare_pattern(type);
		UCUNIT_TestcaseBegin("Pattern Verification after inverting a block of memory");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

	    /********** Inverting the memory ***********/
	    status = invert_block(type);
    	UCUNIT_TestcaseBegin("Inverting Memory back again into original form");
    	UCUNIT_CheckIsEqual(status, 0);
    	UCUNIT_TestcaseEnd();

		/********** Verifying the memory ***********/
		status = compare_pattern(type);
		UCUNIT_TestcaseBegin("Pattern Verification after 2nd inversion of the same block of memory");
		UCUNIT_CheckIsEqual(status, 0);
		UCUNIT_TestcaseEnd();

		/************ Freeing the allocated memory *************/
		free_words();

		/* Finish all the tests */
		UCUNIT_WriteSummary();
		UCUNIT_Shutdown();
}

