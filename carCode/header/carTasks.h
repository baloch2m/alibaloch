#ifndef carTasks_H
#define carTasks_H

#include "main.h"

// think of user input as 3x3 grid
// horizontal 
#define left 		 	(uint16_t)0x3	// 0011
#define straight	(uint16_t)0x2	// 0010
#define right	 		(uint16_t)0x1	// 0001

// vertical 
#define top 		(uint16_t)0xC	// 1100
#define middle	(uint16_t)0x8	// 1000
#define bottom	(uint16_t)0x4	// 0100

//extern xQueueHandle xUIQueue;
extern xQueueHandle xUSFQueue;
extern xQueueHandle xUSBQueue;

extern uint32_t TIMING_SCALE_FACTOR_s;
extern uint16_t TIMING_SCALE_FACTOR_100ms;

void ui( void *pvParameters );
void stateManager( void *pvParameters );
void ultrasonicSensorF ( void *pvParameters );
void velocitySensor ( void *pvParameters );

#endif
