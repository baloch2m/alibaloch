#ifndef test_c
#define test_c

#include "../header/test.h"

// This file contains code used for testing different parts of the project

void testPWM(void){

	while(1){};

}

// check for obstacles in the vehicles path
void ultrasonicSensorTest ( void *pvParameters ){

	portTickType xCurrentWakeTime;
	uint32_t T1;
	uint32_t T2F, T2B;

	uint16_t distanceF, distanceB;

	// minimum distance allowed between vehicle and an object in its path in cm
	uint16_t minimumDistance = 10;
	
	// setup PB5 as a trigger to ultrasonic sensor
	setPB5();
	configureUltrasonicInterruptF();
	configureUltrasonicInterruptB();
	
	enableUltrasonicInterruptF();
	enableUltrasonicInterruptB();
	
	while (1) {
		xCurrentWakeTime = xTaskGetTickCount();
		
		// reset T2  
		T2F = 0xF;
		T2B = 0xB;
		
		//taskENTER_CRITICAL();
			
		// store time that function began
		T1 = get_time();
		
		// send trigger to both forward and backward sensor
		triggerUltrasonicSensor();
		
		// receive value from each forward and backward sensor
		//receiveVal(&T2F, &T2B);
		//receiveVal(&T2F, &T2B);	
		
		EXTI0_IRQHandler();
		EXTI1_IRQHandler();
		
		xQueueReceive( xUSFQueue, &T2F, TIMING_SCALE_FACTOR_100ms*60);		
		xQueueReceive( xUSBQueue, &T2B, TIMING_SCALE_FACTOR_100ms*60);
		
		//taskEXIT_CRITICAL();
		
		// determine if no object was detected 
		
		// determine the distance to object that was detected in cm
		distanceF = (time_difference(T1, T2F) );/// 58);
		distanceB = (time_difference(T1, T2B) );/// 58);
		
		// determine if the forward distance is too short to continue driving
		if (distanceF < minimumDistance){
			forwardValid = false;
		}else{
			forwardValid = true;
		}
		
		// determine if the backward distance is too short to continue driving
		if (distanceB < minimumDistance){
			backwardValid = false;
		}else{
			backwardValid = true;
		}
				
		// delay 100ms for next measurement
		vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_100ms*100);
	}
}

void testInterruptUSF(void){

	//enableUltrasonicInterrupt();
	
	while(1){};
}

void testUI( void *pvParameters ){
    portTickType xCurrentWakeTime;
	
    while (1) {
			
			xCurrentWakeTime = xTaskGetTickCount();
			
			// idle
			sendUI(middle | straight);
			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
			xCurrentWakeTime = xTaskGetTickCount();
			
			// FL
//			sendUI(top | left);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
		
			// F
			sendUI(top | straight);
			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
			xCurrentWakeTime = xTaskGetTickCount();
			
			// FR
//			sendUI(top | right);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
//			
//			// PL
//			sendUI(middle | left);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
//			
//			// PR
//			sendUI(middle | right);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
//			
//			// BL
//			sendUI(bottom | left);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
			
			// B
			sendUI(bottom | straight);
			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
			//xCurrentWakeTime = xTaskGetTickCount();
			
			// BR
//			sendUI(bottom | right);
//			vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_s*5);
//			xCurrentWakeTime = xTaskGetTickCount();
							
    }

}

void sendUI(uint16_t input){	
	
	// reset ui pins PB10 - PB13
	GPIOB->BSRR |= bit(26) | bit(27) | bit(28) | bit(29);
	
	// set ui pins
	GPIOB->BSRR |= (input << 10);

}

#endif
