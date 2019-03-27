/**
   Initialize the timer TIM4.
*/

#include "../header/timers_stmConf.h"

void timer2_init(void){

	// enable time2 clock
	RCC->APB1ENR |= bit(0);
	
	// clock division = 0, bit 9,8 set 0
	//TIM2_BASE = 0x3;
	TIM2->CR1 &= ~bit(8);
	TIM2->CR1 &= ~bit(9);

	// bit 4 set 1 for downcounter
	TIM2->CR1 |= bit(4);
	
	// each count is 1 us 
	TIM2->PSC = 7;
	
	// set reload value
	TIM2->ARR = 0xFFFF;
	
	// bit 0 set 1 enable counter
	TIM2->CR1 |= bit(0);

}
 
void stm32_Timer4Setup (void) { 

	// enable clock for TIM4
	RCC->APB1ENR |= bit(2); 

	// remap timer 4 channels from port B to port D NO PORT D?
	// AFIO->MAPR |= bit(12);

	// reset command register 1 and 2
	TIM4->CR1 = 0;
	TIM4->CR2 = 0;

	// each count is 1 us 
	TIM4->PSC = 72;
	
	// set auto-reload value for duty cycle percentages upto 100%
	TIM4->ARR = 100; 

	// default timers to 0% duty cycle
	TIM4->CCR1 = 0; 
	TIM4->CCR2 = 0; 
	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;

	TIM4->CCMR1 = 0x7070; //__TIM4_CCMR1; //0x6060 *
	TIM4->CCMR2 = 0x7070;//__TIM4_CCMR2; //0x6060
	
	
	TIM4->CCER = 0x3333; //__TIM4_CCER;  //0x1100 set enabling channal one capture/compare enable register *
	
	TIM4->SMCR  = 0; //__TIM4_SMCR;    // 0 set slave mode control register

	TIM4->CR1 = bit(2); // URS: Only counter overflow/underflow
			// generates an update interrupt or DMA
			// request if enabled.

	// enable timer
	TIM4->CR1 |= bit(0); 

} 

