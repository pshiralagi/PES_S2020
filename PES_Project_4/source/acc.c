/*
 * acc.c
 *
 *  Created on: Mar 21, 2020
 *      Author: praka
 */



#include "acc.h"


int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;



//initializes mma8451 sensor
//i2c has to already be enabled
int init_mma(void)
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

/*********Interrupt based accelerometer read**********/


uint16_t readx(void){

	uint8_t datahigh, datalow;
	int16_t temp;
	i2c_start();
	datahigh = i2c_read_byte(MMA_ADDR , REG_XHI);
	datalow = i2c_read_byte(MMA_ADDR , REG_XLO);
	//data[i] = i2c_repeated_read(1);
	temp = (int16_t) ((datahigh<<8) | datalow);
	temp = temp/4;
	return temp;
}

uint16_t ready(void){

	uint8_t datahigh, datalow;
	int16_t temp;
	i2c_start();
	datahigh = i2c_read_byte(MMA_ADDR , REG_YHI);
	datalow = i2c_read_byte(MMA_ADDR , REG_YLO);
	//data[i] = i2c_repeated_read(1);
	temp = (int16_t) ((datahigh<<8) | datalow);
	temp = temp/4;
	return temp;
}

uint16_t readz(void){

	uint8_t datahigh, datalow;
	int16_t temp;
	i2c_start();
	datahigh = i2c_read_byte(MMA_ADDR , REG_ZHI);
	datalow = i2c_read_byte(MMA_ADDR , REG_ZLO);
	//data[i] = i2c_repeated_read(1);
	temp = (int16_t) ((datahigh<<8) | datalow);
	temp = temp/4;
	return temp;
}

void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}

	// Align for 14 bits
	acc_X = temp[0]/4;
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, readfullxyz, "Green LED is on");
		Log_Integer(acc_X);
	#endif

		acc_Y = temp[1]/4;
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, readfullxyz, "Green LED is on");
		Log_Integer(acc_Y);
	#endif

		acc_Z = temp[2]/4;
	#ifdef DEBUG_MODE
		log_func_Str(DebugMode, readfullxyz, "Green LED is on");
		Log_Integer(acc_Z);
	#endif
}

void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	wait_ms(100);
	PRINTF("\n\r x:%d", acc_X);
	acc_Y = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	wait_ms(100);
	PRINTF("    y:%d", acc_Y);
	acc_Z = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
	wait_ms(100);
	PRINTF("    z:%d", acc_Z);
}

/*void read_xyz_int(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	acc_X = (int8_t) I2C_Master_Transmit(MMA_ADDR, REG_XHI);
	wait_ms(100);
	PRINTF("\n\r x:%d", acc_X);
	acc_Y = (int8_t) I2C_Master_Transmit(MMA_ADDR, REG_YHI);
	wait_ms(100);
	PRINTF("    y:%d", acc_Y);
	acc_Z = (int8_t) I2C_Master_Transmit(MMA_ADDR, REG_ZHI);
	wait_ms(100);
	PRINTF("    z:%d", acc_Z);
}*/

//void convert_xyz_to_roll_pitch(void) {
//	float ax = acc_X/COUNTS_PER_G,
//				ay = acc_Y/COUNTS_PER_G,
//				az = acc_Z/COUNTS_PER_G;
//
//	roll = atan2(ay, az)*180/M_PI;
//	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/M_PI;
//
//}
