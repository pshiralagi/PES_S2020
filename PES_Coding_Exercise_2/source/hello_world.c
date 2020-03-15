/*
 * Reference - Code taken from PES Coding Exercise document provided my Prof. Bruce Montgomery
 * Date : 03/14/2020
 * Author : Pavan Shiralagi
 */


#include <MKL25Z4.h>

/* Uncomment required example */
//#define EXAMPLE_1
#define EXAMPLE_2
//#define EXAMPLE_3

/* LED Defines	*/
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)		// on port B
#define BLUE_LED_POS (1)		// on port D
#define MASK(x) (1UL << (x))
/* Function prototypes */
void Init_RGB_LEDs(void);
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);
void Delay(volatile unsigned int time_del);
void RunIt(void);
void Init_SysTick(void);
void Test_SPI_Loopback(void) ;
void Init_SPI1(void) ;

int main(void)
{
	/*	Initialize LEDs as output	*/
    Init_RGB_LEDs();
    /* Initialize SPI 1 */
    Init_SPI1();

    /*	Initialize SysTick timer for EXAMPLE_2	*/
#ifdef EXAMPLE_2
    Init_SysTick();
#endif
#ifdef EXAMPLE_3
    Test_SPI_Loopback();
#endif
    while (1)
    {
    	/*	RGB function for EXAMPLE_1	*/
#ifdef EXAMPLE_1
        RunIt();
#endif

    }
}

void Init_RGB_LEDs(void)
{
	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	// Make 3 pins GPIO
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);
	// Set ports to outputs using the data direction register
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);
}
// for on, use clear output register, for off use set output register
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on)
{
	if (red_on) { PTB->PCOR = MASK(RED_LED_POS);}
else {	PTB->PSOR = MASK(RED_LED_POS);}
	if (green_on) {PTB->PCOR = MASK(GREEN_LED_POS);}
	else {PTB->PSOR = MASK(GREEN_LED_POS);}
	if (blue_on) {PTD->PCOR = MASK(BLUE_LED_POS);}
	else {	PTD->PSOR = MASK(BLUE_LED_POS);}
}
void Delay(volatile unsigned int time_del)
{
  while (time_del--) {
	;
  }
}
void RunIt(void) {
for (int num = 0; num < 4; num++)
{
	if (num==1) Control_RGB_LEDs(1,0,0);
	if (num==2) Control_RGB_LEDs(0,1,0);
	if (num==3) { Control_RGB_LEDs(0,0,1); num=0; }
	Delay(2000000);
}
}

void Init_SysTick(void)
{
	//Interrupt at 3Hz
	SysTick->LOAD = (48000000L/144);
	NVIC_SetPriority(SysTick_IRQn, 3);
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler()
{
	static int n=1;
	if (n == 3)
	{
		Control_RGB_LEDs(1,1,1);//On every 1 second
	}
	if (n == 6)
	{
		Control_RGB_LEDs(0,0,0);//Off every 1 second
		n = 0;
	}
	n++;
}



void Init_SPI1(void) {
	SIM->SCGC4 |= SIM_SCGC4_SPI1_MASK;	// enable clock to SPI1
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SPI1->C1 &= ~SPI_C1_SPE_MASK;		// disable SPI1 to allow configuration

	PORTE->PCR[2] &= ~PORT_PCR_MUX_MASK;	// set SPI1_SCK -- ALT2
	PORTE->PCR[2] |= PORT_PCR_MUX(2);
	PORTE->PCR[3] &= ~PORT_PCR_MUX_MASK;	// set SPI1_MOSI -- ALT5
	PORTE->PCR[3] |= PORT_PCR_MUX(5);
	PORTE->PCR[1] &= ~PORT_PCR_MUX_MASK;	// set SPI1_MISO -- ALT5
	PORTE->PCR[1] |= PORT_PCR_MUX(5);
	PORTE->PCR[4] &= ~PORT_PCR_MUX_MASK;	// set SPI1_PCS0 -- ALT2
	PORTE->PCR[4] |= PORT_PCR_MUX(2);

	SPI1->C1 = SPI_C1_MSTR_MASK | SPI_C1_SSOE_MASK;  // Select master mode, enable SS output
	SPI1->C2 = SPI_C2_MODFEN_MASK;
	SPI1->C1 &= ~SPI_C1_CPHA_MASK; 		// Select active high clock, first edge sample
SPI1->C1 &= ~SPI_C1_CPOL_MASK;

	SPI1->BR = SPI_BR_SPPR(1) | SPI_BR_SPR(3);  // BaudRate = BusClock / ((zzzz+1)*2^(www+1))

	SPI1->C1 |= SPI_C1_SPE_MASK;	// enable SPI1
}
uint8_t test_SPIsend(uint8_t d_out)
{
	while(!(SPI1->S & SPI_S_SPTEF_MASK));  //Wait for transmit buffer empty, put data on data buffer
	SPI1->D = d_out;
	while (!(SPI1->S & SPI_S_SPRF_MASK)); // wait for receive buffer full, read from data buffer
	return SPI1->D;
}
void Test_SPI_Loopback(void)
{
	uint8_t out='A', in;
	while (1) {
		in = test_SPIsend(out);
		if (in != out) { Control_RGB_LEDs(1, 0, 0); }  // Red: error, data doesn't match
		else {	Control_RGB_LEDs(0, 1, 0); }  	   	 // Green: data matches
		out++;
		if (out > 'z') out = 'A';
	}
}

