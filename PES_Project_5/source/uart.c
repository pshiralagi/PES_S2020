/*
 * @file uart.c
 *
 *  @date: Apr 7, 2020
 *  @reference
 *  	Code created by Shannon Strutz
 *  	Licensed under CC BY-NC-SA 3.0
 *  	http://creativecommons.org/licenses/by-nc-sa/3.0/
 *
 *      @author: pshiralagi, aprakash
 */

#include "UART.h"

buffer_t * Tx;
buffer_t * Rx;

struct __FILE
{
  int handle;
};

FILE __stdout;  //Use with printf
FILE __stdin;		//use with fget/sscanf, or scanf


//Retarget the fputc method to use the UART0
int fputc(int ch, FILE *f){
	while(!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK));
	UART0->D = ch;
	return ch;
}

//Retarget the fgetc method to use the UART0
int fgetc(FILE *f){
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	return UART0->D;
}

// Code listing 8.8, p. 231
void Init_UART0(uint32_t baud_rate) {
	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#if USE_UART_INTERRUPTS

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}


uint8_t tx_ready(void)
{
	if (UART0->S1 & UART0_S1_TDRE_MASK)
		return 1;
	return 0;
}

void tx_data(uint8_t data)
{
	UART0->D = data;
}
// Code listing 8.9, p. 233
void UART0_Transmit_Poll(uint8_t data) {
		while (!(tx_ready()))
			;
		tx_data(data);

}

uint8_t rx_ready(void)
{
	if (UART0->S1 & UART0_S1_RDRF_MASK)
		return 1;
	return 0;
}

uint8_t rx_data (void)
{
	return UART0->D;
}
uint8_t UART0_Receive_Poll(void) {
		while (!(rx_ready()))
			;
		return rx_data();
}

void uart_echo_blocking(void)
{
	uint8_t c;
	c = UART0_Receive_Poll();
	UART0_Transmit_Poll(c);
}

void uart_echo(void)
{
	uint8_t buffer[80], *c = 0, * bp;
	// Blocking receive
	while (isBufferEmpty(Rx) == buff_empty)
		; // wait for character to arrive
	bufferRemove(Rx, &c);

	// Blocking transmit
	sprintf((char *) buffer, "You pressed %c\n\r", c);
	// enqueue string
	bp = buffer;
	while (*bp != '\0') {
		// copy characters up to null terminator
		while (isBufferFull(Tx) == buff_full)
			; // wait for space to open up
		bufferAdd(Tx, *bp);
		bp++;
	}
	// start transmitter if it isn't already running
	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		bufferRemove(Tx, &c);
		UART0->D = c;
		UART0->C2 |= UART0_C2_TIE(1);
	}
}

// UART0 IRQ Handler. Listing 8.12 on p. 235
void UART0_IRQHandler(void) {
	uint8_t ch, *c;

	if (UART0->S1 & (UART_S1_OR_MASK |UART_S1_NF_MASK |
		UART_S1_FE_MASK | UART_S1_PF_MASK)) {
			// clear the error flags
			UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;
			// read the data register to clear RDRF
			ch = UART0->D;
	}
	if (UART0->S1 & UART0_S1_RDRF_MASK) {
		// received a character
		ch = UART0->D;
		if (isBufferFull(Rx) != buff_full) {
			bufferAdd(Rx, ch);
		} else {
			// error - queue full.
			// discard character
		}
	}
	if ( (UART0->C2 & UART0_C2_TIE_MASK) && // transmitter interrupt enabled
			(UART0->S1 & UART0_S1_TDRE_MASK) ) { // tx buffer empty
		// can send another character
		if (isBufferEmpty(Tx)!=buff_empty) {
			bufferRemove(Tx, &c);
			UART0->D = c;
		} else {
			// queue is empty so disable transmitter interrupt
			UART0->C2 &= ~UART0_C2_TIE_MASK;
		}
	}
}

void Send_String_Poll(uint8_t * str) {
	// enqueue string
	while (*str != '\0') { // Send characters up to null terminator
		UART0_Transmit_Poll(*str++);
	}
}

void Send_String(uint8_t * str) {
	uint8_t *recv = 0;
	// enqueue string
	while (*str != '\0') { // copy characters up to null terminator
		while (isBufferFull(Tx) == buff_full)
			; // wait for space to open up
		bufferAdd(Tx, *str);
		str++;
	}
	// start transmitter if it isn't already running
	if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
		bufferRemove(Tx, &recv);
		UART0->D = recv;
		UART0->C2 |= UART0_C2_TIE(1);
	}
}


uint8_t	* Get_Rx_Char(void) {
	uint8_t *rec = 0;
	bufferRemove(Tx, rec);
	return rec;
}

