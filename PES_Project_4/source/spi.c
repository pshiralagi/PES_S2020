/*
 * @filename	 spi.c
 *
 *  @date: Mar 20, 2020
 *      @author: aprakash, pshiralagi
 *      @reference	parts of code taken from the in class coding exercise
 */

#include "spi.h"

/*
 * @brief	Function to initialize SPI
 */
void Init_SPI1(void) {

	// enable clock to SPI1
		SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;
		SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

		// disable SPI1 to allow configuration
		SPI1->C1 &= ~SPI_C1_SPE_MASK;

		// set PTE2 as SPI1_SCK -- ALT2
		PORTE->PCR[2] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[2] |= PORT_PCR_MUX(2);
		// set PTE3 as SPI1_MOSI -- ALT5
		PORTE->PCR[3] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[3] |= PORT_PCR_MUX(5);
		// set PTE1 as SPI1_MISO -- ALT5
		PORTE->PCR[1] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[1] |= PORT_PCR_MUX(5);
		// Enable pull-up resistor on input data
		PORTE->PCR[1] |= PORT_PCR_PE_MASK;

		// set PTE4 as SPI1_PCS0 -- ALT2
		PORTE->PCR[4] &= ~PORT_PCR_MUX_MASK;
		PORTE->PCR[4] |= PORT_PCR_MUX(2);

		// Select master mode, enable SS output
		SPI1->C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;
		SPI1->C2 = SPI_C2_MODFEN_MASK;
		// Select active high clock, first edge sample
		SPI1->C1 &= ~SPI_C1_CPHA_MASK;
	  SPI1->C1 &= ~SPI_C1_CPOL_MASK;

		//BaudRate = BusClock / ((SPPR+1)*2^(SPR+1))
		SPI1->BR = SPI_BR_SPPR(7) | SPI_BR_SPR(3);

		// enable SPI1
		SPI1->C1 |= SPI_C1_SPE_MASK;
}

/*
 * @brief	Test SPI send
 */
uint8_t test_SPIsend(uint8_t d_out)
{
	while(!(SPI1->S & SPI_S_SPTEF_MASK))
		;  //Wait for transmit buffer empty
	SPI1->D = d_out;

	while (!(SPI1->S & SPI_S_SPRF_MASK))
		; // wait for receive buffer full
	return SPI1->D;
}

/*
 * @brief	SPI Loopback function
 */
uint8_t Test_SPI_Loopback(void) {
	uint8_t out='A', in, output;
	in = test_SPIsend(out);
	if (in != out) {
		output = 0;
		return output;
	} // Red: error, data doesn't match
	else {
		output = 1;
		return output;
	} // Green: data matches
	//out++;
	//if (out > 'z') out = 'A';
	//}
}
