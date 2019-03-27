#ifndef carTasks_c
#define carTasks_c

#include "../header/carTasks.h"

// define timing constants for converting ticks to real time
uint32_t TIMING_SCALE_FACTOR_s = 100;
uint16_t TIMING_SCALE_FACTOR_100ms = 10; 

// acquire input from the user
void ui(void *pvParameters )
{
  portTickType xCurrentWakeTime = xTaskGetTickCount();
	
	setUIPins();
	
	uint16_t ReceivedValue;
	uint16_t UI_mutex = 1;

	while(1){
		
		xCurrentWakeTime = xTaskGetTickCount();
		
		// consider making this critical
		ReceivedValue = readUI();
		
		// check if critical
		if (ReceivedValue == 0x0){
			// perform critical task and block UI
			//UI_mutex = 0;
		}

		// check if accepting noncritical user input
		if (UI_mutex == 1){
			// set state
			GLOBAL_STATE = ReceivedValue;
			//xQueueSend( xStateQueue, &ReceivedValue, 0 );
		}
		
		vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_100ms*4);
		
	}

}

// use input from the user and sensors to determine what state the vehicle should be in
void stateManager( void *pvParameters ){
	portTickType xCurrentWakeTime;

	uint16_t state;
	
	while (1) {
		xCurrentWakeTime = xTaskGetTickCount();
		
		// make local copy of global state set by the ui task
		state = GLOBAL_STATE;
		
		// determine if the state sent from the user is invalid
		if ( (forwardValid  == false && (state & 0xC) == top)    ||
			   (backwardValid == false && (state & 0xC) == bottom) ){
		
			// change state to middle row  
			state = middle | (0x3 & state); // mask the horizontal portion of state
			
		}
		
		executeState(state); 		
		
		vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_100ms);
	}

}

// check for obstacles in the vehicles path
void ultrasonicSensorF ( void *pvParameters ){

	portTickType xCurrentWakeTime;
	uint32_t T1;
	uint32_t T2F, T2B;

	uint16_t distanceF, distanceB;

	// minimum distance allowed between vehicle and an object in its path in cm
	uint16_t minimumDistance = 2000;
	
	// setup PB5 as a trigger to ultrasonic sensor
	setPB5();
	configureUltrasonicInterruptF();
	configureUltrasonicInterruptB();
	
	enableUltrasonicInterruptF();
	enableUltrasonicInterruptB();
	
	while (1) {
		xCurrentWakeTime = xTaskGetTickCount();
		
		// reset T2  
		T2F = 0;
		T2B = 0;
		
		// clear contents of the smaple data queues
		xQueueReset(xUSFQueue);
		xQueueReset(xUSBQueue);
		
		//taskENTER_CRITICAL();
			
		// store time that function began
		T1 = get_time();
		
		// send trigger to both forward and backward sensor
		triggerUltrasonicSensor();
		
		// receive value from each forward and backward sensor
		xQueueReceive( xUSFQueue, &T2F, TIMING_SCALE_FACTOR_100ms);
		xQueueReceive( xUSBQueue, &T2B, TIMING_SCALE_FACTOR_100ms);
		
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
		vTaskDelayUntil(&xCurrentWakeTime, TIMING_SCALE_FACTOR_100ms);
	}
}

// measure the speed at which the vehicle is travelling at
void velocitySensor ( void *pvParameters ){
	
	// declare variables for storing relative time and count samples
	//uint16_t T1, T2, T;
	uint32_t C1, C2;
	
	enableWheelEncoderInterrupt();
	
	while(1){
	
		// acquire initial measurements
		C1 = GLOBAL_WHEEL_ENCODER_COUNT;
		//T1 = get_time();
	
		// wait approximately 100ms as a sampling period
		vTaskDelay(TIMING_SCALE_FACTOR_100ms);
	
		// acquire final measurements
		C2 = GLOBAL_WHEEL_ENCODER_COUNT;
		//T2 = get_time();
				
		// calculate velocity observed over sampling period adjust timing
		GLOBAL_VELOCITY = (C2 - C1) ;
		//T =  (time_difference(T1, T2));
		
	}
}

#endif
