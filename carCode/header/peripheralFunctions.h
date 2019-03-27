#ifndef peripheralFunctions_H
#define peripheralFunctions_H

#include "main.h"

extern bool forwardValid;
extern bool backwardValid;
extern uint16_t GLOBAL_STATE;
extern uint32_t GLOBAL_WHEEL_ENCODER_COUNT;
extern uint16_t GLOBAL_VELOCITY;

void executeState(uint16_t state);
uint16_t readUI(void);
void triggerUltrasonicSensor(void);
void receiveVal(uint32_t *T2F, uint32_t *T2B);
uint32_t get_time(void);
uint32_t time_difference(uint32_t start_time, uint32_t stop_time);

void FL		(void);
void F 		(void);
void FR		(void);
void PL		(void);
void Idle (void);
void PR		(void);
void BL		(void);
void B		(void);
void BR		(void);

void delay(uint32_t time);

#endif
