

#ifndef DAC_H_
#define DAC_H_

#include "fsl_dac.h"
void updateDACvals(void);
void dacInit(void);
extern uint16_t dac_vals[500];
#endif
