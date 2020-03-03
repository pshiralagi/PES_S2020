/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    PES_Project_3.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
/**************** Customised Header File ****************************/

#include "allocate_bytes.h"
#include "led.h"
#include "memory.h"
#include "pattern.h"
#include "logger.h"
#include "general.h"

/******************************Function Pointer Definition**************************************/
typedef mem_status(*functionPointerType)(struct data_type o);
struct commandStruct {
char const *name;
functionPointerType execute;
char const *help;
};
/*************************** Command Procesor Script *************************************/
const struct commandStruct commands[] =
{
{"A", &allocate_memory, "Allocate bytes using malloc"},
{"M", &verify_memory, "Verify if memory is allocated"},
{"P", &write_pattern, "Write pattern to allocated memory"},
{"D", &display_memory, "display the allocated memory"},
{"C", &compare_pattern, "Verify if pattern matches"},
{"W", &write_memory, "Write to a memory"},
{"I", &invert_block, "Invert memory"},
{"F", &free_mem, "Free allocated memory"},
{" ",0,""} //End of table indicator. MUST BE LAST!!!
};

/****************** Test Script ********************************************/
struct data_type value[]={
	{"A",0,0,32,0,0},
	{"M",0,0,0,0,0},
	{"P",0,32,0,0,143},
	{"D",0,32,0,0,0},
	{"D",0,34,0,0,0},
	{"C",0,32,0,0,143},
	{"W",12,2,0,0xFFEE,0},
	{"D",0,32,0,0,0},
	{"C",0,32,0,0,143},
	{"P",0,16,0,0,127},
	{"D",0,32,0,0,0},
	{"C",0,16,0,0,127},
	{"I",35,2,0,0,0},
	{"I",9,2,0,0,0},
	{"D",0,16,0,0,0},
	{"C",0,16,0,0,127},
	{"I",9,2,0,0,0},
	{"C",0,16,0,0,127},
	{"D",0,16,0,0,0},
	{"F",0,0,0,0,0},
	{"M",0,0,0,0}
};

/********************************************************************/
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
    mem_status status;
    /*******************LED Initialization********************************/

    led_init();

    /***********************Memory Test Start*****************************/

    Start_Test();

    /**********************Memory and pointers operation******************************/

    PRINTF("BEGIN");
    status = (*commands[0].execute)(value[0]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();
           }
    Log_string("\n\r command 1");
    status = (*commands[1].execute)(value[1]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();
           }
    Log_string("\n\r command 2");
    status = (*commands[2].execute)(value[2]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();
           }
    Log_string("\n\r command 3");
    status = (*commands[3].execute)(value[3]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();
           }
    Log_string("\n\r command 4");
    status = (*commands[3].execute)(value[4]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 5");
    status = (*commands[4].execute)(value[5]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 6");
    status = (*commands[5].execute)(value[6]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();
           }
    Log_string("\n\r command 7");
    status = (*commands[3].execute)(value[7]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 8");
    status = (*commands[4].execute)(value[8]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 9");
    status = (*commands[2].execute)(value[9]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 10");
    status = (*commands[3].execute)(value[10]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 11");
    status = (*commands[4].execute)(value[11]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 12");
    status = (*commands[6].execute)(value[12]);
    if(status == SUCCESS){
               Success_Test();
           }else{
               Fail_Test();

           }
    Log_string("\n\r command 13");
    status = (*commands[6].execute)(value[13]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }
    Log_string("\n\r command 14");
    status = (*commands[3].execute)(value[14]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }
    Log_string("\n\r command 15");
    status = (*commands[4].execute)(value[15]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }
    Log_string("\n\r command 16");
    status = (*commands[6].execute)(value[16]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }
    Log_string("\n\r command 17");
    status = (*commands[4].execute)(value[17]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }
    Log_string("\n\r command 18");
    status = (*commands[3].execute)(value[18]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();
               }
    Log_string("\n\r command 19");
    status = (*commands[7].execute)(value[19]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();
               }
    Log_string("\n\r command 20");
    status = (*commands[1].execute)(value[20]);
    if(status == SUCCESS){
                   Success_Test();
               }else{
                   Fail_Test();

               }

    PRINTF("ENDED");


    return 0;
}
