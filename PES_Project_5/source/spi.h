/*
 * @file spi.h
 *
 *  @date: Mar 20, 2020
 *      @author: aprakash, pshiralagi
 */

#ifndef SPI_H_
#define SPI_H_
#include "general.h"
void Init_SPI1(void);
uint8_t test_SPIsend(uint8_t d_out);
uint8_t Test_SPI_Loopback(void);


#endif /* SPI_H_ */
