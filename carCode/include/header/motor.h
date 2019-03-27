#ifndef motor_H
#define motor_H

#include "main.h"

extern uint16_t PWM_SETPOINT;

void closeServo(void);
void openServo(void);

extern uint16_t valveOpen;
extern uint16_t valveClosed;

uint32_t getPosition(void);
void setPosition(uint32_t x);
uint32_t incrementServo(void);
uint32_t decrementServo(void);
uint32_t maintainDistance(void);

#endif
