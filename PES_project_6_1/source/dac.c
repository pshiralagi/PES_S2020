



#include "dac.h"


void updateDACvals(void)
{
	static uint16_t count = 1;
	const uint16_t increment_val = (2482/50);
	dac_vals[0] = 1241;

	for (count = 1; count < 25; count++)
		{
			dac_vals[count] = dac_vals[count-1]+increment_val;
		}
	while (count < 50)
	{
		dac_vals[count] = dac_vals[count-1]-increment_val;
		count++;
	}
}

void dacInit(void)
{
	dac_config_t dacConfigStruct;
    DAC_GetDefaultConfig(&dacConfigStruct);
    DAC_Init(DAC0, &dacConfigStruct);
    DAC_Enable(DAC0, true); /* Enable output. */
}
