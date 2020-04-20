/**
 * @file    dac.c
 * @author	Pavan and Antara
 * @brief   This file contains DAC related functions
 *
 */



#include "dac.h"

/*
 * @param	Function to create DAC LUT
 */
void updateDACvals(void)
{
	static uint16_t count = 1;
	const uint16_t increment_val = (2482/50);
	dac_vals[0] = 1241;

	for (count = 1; count < 25; count++)
		{
			dac_vals[count] = dac_vals[count-1]+increment_val;
		}
	dac_vals[count] = dac_vals[count-1];
	count++;
	while (count < 50)
	{
		dac_vals[count] = dac_vals[count-1]-increment_val;
		count++;
	}
}

/*
 * @brief	Function to initialize DAC
 */
void dacInit(void)
{
	dac_config_t dacConfigStruct;
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, true); /* Enable output. */
}
