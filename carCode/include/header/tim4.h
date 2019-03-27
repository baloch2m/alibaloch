
#ifndef TIM4_H
#define TIM4_H

#include "main.h"

void setPWM(uint16_t percent);
void stm32_Timer4Setup (void);
void stm32_GpioTim4Setup (void);
void delay(int x);

#endif
