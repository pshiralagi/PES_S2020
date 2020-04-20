



#include "adc_dac.h"


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

void adcInit(void)
{
	ADC16_GetDefaultConfig(&adc16ConfigStruct);
	#ifdef BOARD_ADC_USE_ALT_VREF
	    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
	#endif
    ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false);
	#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
	    if (kStatus_Success == ADC16_DoAutoCalibration(DEMO_ADC16_BASE))
	    {
			#ifdef DEBUG_MODE
	        	log_Str(Debug, main_fun, "ADC16_DoAutoCalibration() Done.");
			#endif
	    }
	    else
	    {
			#ifdef DEBUG_MODE
	        	log_Str(Debug, main_fun, "ADC16_DoAutoCalibration() Failed.");
			#endif
	    }
	#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */

	adc16ChannelConfigStruct.channelNumber = DEMO_ADC16_USER_CHANNEL;
	adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;
	#if defined(FSL_FEATURE_ADC16_HAS_DIFF_MODE) && FSL_FEATURE_ADC16_HAS_DIFF_MODE
	    adc16ChannelConfigStruct.enableDifferentialConversion = false;
	#endif /* FSL_FEATURE_ADC16_HAS_DIFF_MODE */

}
