/******************************************************************************
 * Name:   IO.h
 * Description: STM32 peripherals initialization
 * Version: V1.00
 * Authors: Dave Duguid / Trevor Douglas / Mohammed Benhammou
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *****************************************************************************/

#include <stdint.h>
#include "stm32f10x.h"
#include "LCD.h"

//Bit masks for leds on STM32VLDiscovery board PC8 and PC9 using GPIOC_BSRR
//Green LED is on bit 9 of port C, Blue LED is on bit 8.
 #define GREEN_ON	0x00000200 		// set bit
 #define GREEN_OFF 0x02000000 	// reset bit
 #define BLUE_ON	0x00000100 		// set bit
 #define BLUE_OFF	0x01000000 		// reset bit

 //Functions available for public use
 
 void led_IO_init(void); // Initialize the clocks and IO pins for the LEDs and USER switch
 void led_switch_operate (void);
// uint16_t read_switch(void); 
 

void delay(uint32_t count);

void move_forward(void);
void turn_right(void);
void turn_left(void);
void move_backward(void);
void stop(void);
void ON(void);
void OFF(void);



