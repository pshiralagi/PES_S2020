/*
 * adc_dac.c
 *
 *  Created on: Apr 18, 2020
 *      Author: Pavan and Antara
 */

#ifndef ADC_DAC_H_
#define ADC_DAC_H_
#include "fsl_dac.h"
#include "fsl_adc16.h"
#define DEMO_ADC16_BASE ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL 0U //PTE20, ADC0_SE0
extern adc16_config_t adc16ConfigStruct;
extern adc16_channel_config_t adc16ChannelConfigStruct;

void updateDACvals(void);
void dacInit(void);
void adcInit(void);
extern uint16_t dac_vals[50];
#endif
