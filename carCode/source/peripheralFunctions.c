#ifndef peripheralFunctions_c
#define peripheralFunctions_c

#include "../header/peripheralFunctions.h"

// initialize vehicle to have idle state
uint16_t GLOBAL_STATE = 0xA;
uint32_t GLOBAL_WHEEL_ENCODER_COUNT = 0;
uint16_t GLOBAL_VELOCITY = 0;

// initialize vehicle to not allow forward/backward motion
bool forwardValid  = false;
bool backwardValid = false;

uint16_t high = 90;
uint16_t midHigh = 80;
uint16_t midLow = 70;
//uint16_t low = 60;

void executeState(uint16_t state){

	// select the motion that the vehicle will perform
	
	switch (state){
		
		case (top | left) 			: FL(); break;
		case (top | straight)		: F (); break;
		case (top | right) 			: FR(); break;
		
		case (middle | left) 		: PL(); 	break;
		case (middle | straight): Idle(); break;
		case (middle | right) 	: PR();	  break;
	
		case (bottom | left) 		: BL(); break;
		case (bottom | straight): B (); break;
		case (bottom | right) 	: BR(); break;
	}

}

uint16_t readUI(void){

	uint16_t input = 0;
	
	input = GPIOB->IDR >> 10;
	
	//return (bottom | straight);
	return input;

}

// trigger the ultrasonic sensor for a new sample
void triggerUltrasonicSensor(void){

	// set bit for 10us to trigger ultrasonic sensor
	GPIOB->BSRR |= bit(5);
	delay(10);
	GPIOB->BSRR |= bit(21);

}

void receiveVal(uint32_t *T2F, uint32_t *T2B){

	uint32_t Ttemp;
	
	/* Wait until something arrives in the queue - this task will block for a maximum of 60ms */
	xQueueReceive( xUSFQueue, &Ttemp, TIMING_SCALE_FACTOR_100ms);
	
	// detetmine if the value is from the forward or backward sensor
	if (Ttemp & 1){
		*T2B = Ttemp;
	}else{
		*T2F = Ttemp;
	}
}

uint32_t get_time(void){

	int32_t ret = TIM2->CNT;
	return ret;

}

uint32_t time_difference(uint32_t start_time, uint32_t stop_time){
	
	uint32_t ret = 0x0;
	
	// dtermine if the counter has wrapped around
	if ((unsigned)stop_time > (unsigned)start_time){
	
		// offset count
		ret = 0xFFFF - (unsigned)stop_time + (unsigned)start_time;
	
	}else{
	
		// calculate difference
		ret = start_time - stop_time;
		
	}
	
	return ret;

}

// set rotation for left side tires PB6, 7
void leftSide(int16_t dutyCycle, bool forwardRotation){

	// determine if the tire rotation is forward
	if (forwardRotation){
	
		TIM4->CCR1 = dutyCycle;
		TIM4->CCR2 = 0;
	}else{
	
		TIM4->CCR1 = 0;
		TIM4->CCR2 = dutyCycle;
	}

}

// set rotation for right side tires PB8, 9
void rightSide(int16_t dutyCycle, bool forwardRotation){

	// determine if the tire rotation is forward
	if (forwardRotation){
	
		TIM4->CCR3 = 0;
		TIM4->CCR4 = dutyCycle;
	}else{
	
		TIM4->CCR3 = dutyCycle;
		TIM4->CCR4 = 0;
	}

}

void FL(void){

	// left side forward midLow%
	leftSide(midLow, true);
	
	// right side forward midHigh%
	rightSide(midHigh, true);

}

void F(void){

	// left side forward high%
	leftSide(high, true);
	
	// right side forward high%
	rightSide(high, true);

}

void FR(void){

	// left side forward midHigh%
	leftSide(midHigh, true);
	
	// right side forward midLow%
	rightSide(midLow, true);

}

void PL(void){

	// left side backward low%
	leftSide(midLow, false);
	
	// right side forward low%
	rightSide(midLow, true);

}

void Idle(void){

	// left side forward 0%
	leftSide(0, true);
	
	// right side forward 0%
	rightSide(0, true);

}

void PR(void){

	// left side forward low%
	leftSide(midLow, true);
	
	// right side forward low%
	rightSide(midLow, false);

}

void BL(void){

	// left side backward midLow%
	leftSide(midLow, false);
	
	// right side backward midHigh%
	rightSide(midHigh, false);

}

void B(void){

	// left side backward high%
	leftSide(high, false);
	
	// right side forward high%
	rightSide(high, false);

}

void BR(void){

	// left side backward midHigh%
	leftSide(midHigh, false);
	
	// right side backward midLow%
	rightSide(midLow, false);

}

// delay for an inputted amount of clock cycles, 1 cycle = 1us
void delay(uint32_t time){

	for (int i=0; i<time; i++){}

}

#endif
