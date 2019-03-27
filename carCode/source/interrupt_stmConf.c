
#include "../header/interrupt_stmConf.h"

// PA0 is backward echo pin
void configureUltrasonicInterruptB(void){
	// bit 0 is afio en rcc apb2enr
	RCC->APB2ENR |= (bit(0) | bit(2));
	
	// set PA0 as input with pull up/down
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= bit(3);
	
	// configure port A as EXTI0 default is port a
	//AFIO->EXTICR[0] &=  bit(0);
	
	// unmask interupt for PA0, set bit 0 exti_imr
	EXTI->IMR |= EXTI_IMR_MR0;
	
	// enable interrupt for falling edge detection
	EXTI->FTSR |= EXTI_FTSR_TR0;
		
	NVIC_SetPriority(EXTI0_IRQn, 4); 
	
}

// PB1 is forward echo pin
void configureUltrasonicInterruptF(void){
	// bit 0 is afio en rcc apb2enr
	RCC->APB2ENR |= (bit(0) | bit(2));
	
	// set PB1 as input with pull up/down
	GPIOB->CRL &= 0xFFFFFF0F;
	GPIOB->CRL |= bit(7);
	
	// configure port B as EXTI1 default is port a
	AFIO->EXTICR[0] |=  bit(4);
	
	// unmask interupt for PB1, 
	EXTI->IMR |= EXTI_IMR_MR1;
	
	// enable interrupt for falling edge detection
	EXTI->FTSR |= EXTI_FTSR_TR1;
		
	NVIC_SetPriority(EXTI1_IRQn, 4); 
	
}

// enable the interrupt on EXT0
void enableUltrasonicInterruptF(void){
	// unmask nvic iser with EXTI0
	NVIC->ISER[0] |= NVIC_ISER_SETENA_6;
}

// enable the interrupt on EXT1
void enableUltrasonicInterruptB(void){
	// unmask nvic iser with EXTI1 
	NVIC->ISER[0] |= NVIC_ISER_SETENA_7;
}

// disable the interrupt on EXT0
void disableUltrasonicInterruptF(void){
	// mask nvic iser with EXTI0
	NVIC->ISER[0] &= ~NVIC_ISER_SETENA_6;
}

// disable the interrupt on EXT1
void disableUltrasonicInterruptB(void){
	// mask nvic iser with EXTI1 
	NVIC->ISER[0] &= ~NVIC_ISER_SETENA_7;
}

void enableWheelEncoderInterrupt(void){
	// bit 0 is afio en rcc apb2enr
	RCC->APB2ENR |= bit(0);
	
	// enable clock to port D
	RCC->APB2ENR |= bit(5);
	
	// set PD2 as input with pull up/down
	GPIOD->CRL &= 0xFFFFF0FF;
	GPIOD->CRL |= bit(11);
	
	// configure port D as EXTI2
	AFIO->EXTICR[0] |= (bit(8) | bit(9));
	
	// unmask interupt for PD2, set bit 2 exti_imr
	EXTI->IMR |= EXTI_IMR_MR2;
	
	// enable interrupt for falling edge detection
	EXTI->FTSR |= EXTI_FTSR_TR2;
	
	// unmask nvic iser with EXTI2 
	NVIC->ISER[0] |= NVIC_ISER_SETENA_8;
	
}

