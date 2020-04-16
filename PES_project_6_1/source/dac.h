

#ifndef DAC_H_
#define DAC_H_

#include "fsl_dac.h"
static uint16_t dac_vals[500];
void updateDACvals(void);
void dacInit(void);

#endif
