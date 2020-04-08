/*
 * @file uart.h
 *
 *  @date: Apr 7, 2020
 *      @author: pshiralagi, aprakash
 */

#ifndef UART_H
#define UART_H

#include "general.h"

#define USE_UART_INTERRUPTS 	(0) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(24e6)

void Init_UART0(uint32_t baud_rate);
void UART0_Transmit_Poll(uint8_t data);
uint8_t UART0_Receive_Poll(void);

void Send_String_Poll(uint8_t * str);
void Send_String(uint8_t * str);

uint8_t	* Get_Rx_Char(void);
uint8_t tx_ready(void);
void tx_data(uint8_t data);
uint8_t rx_ready(void);
uint8_t rx_data(void);
void uart_echo_blocking(void);
void uart_echo(void);







#endif
