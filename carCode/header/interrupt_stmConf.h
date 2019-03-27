#ifndef interrupt_stmConf_H
#define interrupt_stmConf_H

#include "main.h"

void configureUltrasonicInterruptF(void);
void configureUltrasonicInterruptB(void);
void enableUltrasonicInterruptF(void);
void enableUltrasonicInterruptB(void);
void disableUltrasonicInterruptF(void);
void disableUltrasonicInterruptB(void);

void enableWheelEncoderInterrupt(void);

#endif
