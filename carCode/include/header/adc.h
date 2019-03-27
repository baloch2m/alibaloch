#ifndef adc_H
#define adc_H

#include "main.h"

extern uint32_t ADC1_GLOBAL_DATA_VALUE;
extern bool ADC1_READY;
extern int DELAY;

uint32_t bit(int b);

bool EOC(void);
void swstart(void);
void setupADC(void);

#endif
