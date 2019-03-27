
#include "../header/irqHandler.h"

// measure the time that the BACKWARDS ultrasonic sensor responds to the trigger signal
void EXTI0_IRQHandler(void){

	uint32_t T2;
	T2 = get_time();
	
	// reset interupt
	EXTI->PR |= bit(0);

	xQueueSendFromISR( xUSBQueue, &T2, 0 );
	
}

// measure the time that the FORWARDS ultrasonic sensor responds to the trigger signal
void EXTI1_IRQHandler(void){

	uint32_t T2;
	T2 = get_time();
	
	// reset interrupt
	EXTI->PR |= bit(1);

	xQueueSendFromISR( xUSFQueue, &T2, 0 );

}

// increment wheel rotation count when encoder sends a signal to stm32
void EXTI2_IRQHandler(void){

	// reset interrupt
	EXTI->PR |= bit(3);
	GLOBAL_WHEEL_ENCODER_COUNT++;
	
}
