/*********************************************************
 *
 * @filename	i2c.c
 * @brief		File containing i2c functions
 * @author		aprakash, pshiralagi
 * @reference	https://github.com/alexander-g-dean/ESF/blob/master/Code/Chapter_8/I2C-Demo/src/i2c.c
 *
 *********************************************************/




#include "i2c.h"


uint8_t lock_detect=0;
uint8_t i2c_lock=0;

/*
 * @brief	Function to initialize i2c0
 */
void i2c_init(void)
{
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);

	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);

	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
 	//~400k = 24M/(64); icr=0x12 sets scl_div to 64

 	I2C0->F = (I2C_F_ICR(0x10) | I2C_F_MULT(0));

	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK);


	// Select high drive mode
	I2C0->C2 |= (I2C_C2_HDRS_MASK);

}

/*
 * @brief Function to enter if i2c is busy
 */
void i2c_busy(void){
	// Start Signal
	lock_detect=0;
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C_TRAN;
	I2C_M_START;
	I2C0->C1 |=  I2C_C1_IICEN_MASK;
	// Write to clear line
	I2C0->C1 |= I2C_C1_MST_MASK; /* set MASTER mode */
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->D = 0xFF;
	while ((I2C0->S & I2C_S_IICIF_MASK) == 0U) {
	} /* wait interrupt */
	I2C0->S |= I2C_S_IICIF_MASK; /* clear interrupt bit */


	/* Clear arbitration error flag*/
	I2C0->S |= I2C_S_ARBL_MASK;


	/* Send start */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_TX_MASK; /* Set transmit (TX) mode */
	I2C0->C1 |= I2C_C1_MST_MASK; /* START signal generated */

	I2C0->C1 |= I2C_C1_IICEN_MASK;
	/*Wait until start is send*/

	/* Send stop */
	I2C0->C1 &= ~I2C_C1_IICEN_MASK;
	I2C0->C1 |= I2C_C1_MST_MASK;
	I2C0->C1 &= ~I2C_C1_MST_MASK; /* set SLAVE mode */
	I2C0->C1 &= ~I2C_C1_TX_MASK; /* Set Rx */
	I2C0->C1 |= I2C_C1_IICEN_MASK;


	/* wait */
	/* Clear arbitration error & interrupt flag*/
	I2C0->S |= I2C_S_IICIF_MASK;
	I2C0->S |= I2C_S_ARBL_MASK;
	lock_detect=0;
	i2c_lock=1;
}

/*
 * @brief	Function to wait for i2c to complete
 */
void i2c_wait(void) {
	lock_detect = 0;
	while(((I2C0->S & I2C_S_IICIF_MASK)==0) & (lock_detect < 200)) {
		lock_detect++;
	}
	if (lock_detect >= 200)
		i2c_busy();
	I2C0->S |= I2C_S_IICIF_MASK;
}

/*
 * @brief Start sequence
 */
void i2c_start()
{
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

/*
 * @brief	send device address, read address
 * @param	dev is the device address
 * @param	address is the read address
 */

void i2c_read_setup(uint8_t dev, uint8_t address)
{
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to receive mode */

}

/*
 * @brief	To read data multiple times (multiple bytes)
 */
uint8_t i2c_repeated_read(uint8_t isLastRead)
{
	uint8_t data;

	lock_detect = 0;

	if(isLastRead)	{
		NACK;								/*set NACK after read	*/
	} else	{
		ACK;								/*ACK after read	*/
	}

	data = I2C0->D;				/*dummy read	*/
	I2C_WAIT							/*wait for completion */

	if(isLastRead)	{
		I2C_M_STOP;					/*send stop	*/
	}
	data = I2C0->D;				/*read data	*/

	return  data;
}


/*
 * @brief 	Function to read a single byte
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address)
{
	uint8_t data;

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT							/*wait for completion */

	I2C0->D =  address;		/*send read address	*/
	I2C_WAIT							/*wait for completion */

	I2C_M_RSTART;				   /*repeated start */
	I2C0->D = (dev|0x1);	 /*send dev address (read)	*/
	I2C_WAIT							 /*wait for completion */

	I2C_REC;						   /*set to recieve mode */
	NACK;									 /*set NACK after read	*/

	data = I2C0->D;					/*dummy read	*/
	I2C_WAIT								/*wait for completion */

	I2C_M_STOP;							/*send stop	*/
	data = I2C0->D;					/*read data	*/

	return data;
}



/*
 * @brief	Function to write a single byte
 */

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data)
{

	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
	I2C0->D = dev;			  /*send dev address	*/
	I2C_WAIT						  /*wait for ack */

	I2C0->D =  address;		/*send write address	*/
	I2C_WAIT

	I2C0->D = data;				/*send data	*/
	I2C_WAIT
	I2C_M_STOP;

}

/*
 * @brief	Function to start interrupt i2c transmit
 */
void I2C_Master_Transmit(void)
{
	I2C0->C1 |= I2C_C1_MST_MASK;		//  Generate START SIGNAL
	I2C0->D = ((0x3A << 1) | 0x2A);		// Write 7-bit Slave Address + READ bit*/

	__disable_irq();
		//set interrupt
		I2C0->C1 |= (I2C_C1_IICIE_MASK);
		__enable_irq();
		//enable i2c and set to master mode
		I2C0->C1 |= (I2C_C1_IICEN_MASK);
		NVIC->ICPR[0] |= 1 << ((I2C0_IRQn)%32);
		NVIC->ISER[0] |= 1 << ((I2C0_IRQn)%32);

}


/*
 * @brief	I2C0 interrupt handler
 */

void I2C0_IRQHandler(void)
{
	//uint8_t status;

	//status = I2C0->S;	// Read status
	I2C0->S |= I2C_S_IICIF_MASK;	// Clear interrupt flag

	if(I2C0->C1 & I2C_C1_TX_MASK) // Transmitter mode?
	{
		if(ACK)
		{
			read_full_xyz();
			//set interrupt
			I2C0->C1 &= ~(I2C_C1_IICIE_MASK);
			I2C_TRAN;
//			I2C_Master_Transmit();
		}
		else
		{
			I2C0->C1 &= ~I2C_C1_MST_MASK;	// Generate STOP signal
		}
	}
	else{
		read_full_xyz();
		I2C_Master_Transmit();
	}

}
