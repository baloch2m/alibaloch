
#include "../header/GPIO_RCC_stmConf.h"

// returns a bit pattern for a specific bit
uint32_t bit(int b){

	uint32_t ret = 0x1;
	ret = ret << b;
	
	return ret;

}
 
// setup PB5 for use as the trigger for interfacing an ultrasonic sensor
void setPB5(void){
	// EN=1, enable GPIOB clock
	RCC->APB2ENR |= bit(3); 
	
	// clear PB5
	GPIOB->CRL &= 0xFF0FFFFF;
	// set PB5 as GPO 50MHz
	GPIOB->CRL |= bit(21) | bit(20);
}

// setup PB10 - PB15 to read input from RF receiver
void setUIPins(void){
	// EN=1, enable GPIOB clock
	RCC->APB2ENR |= bit(3); 
	
	// clear PB10 - PB15
	GPIOB->CRH &= 0x000000FF;
	// set PB10 - PB15 as GPI input with pull up/down
	GPIOB->CRH |=  bit(31) | bit(27) | bit(23) | bit(19) | bit(15) | bit(11);
}

// configure ports for interfacing the motors
void stm32_GpioTim4Setup (void) {
  
	// EN=1, enable GPIOB clock
	RCC->APB2ENR |= bit(3); 
	
	// clear Ports 6, 7, 8, 9
	GPIOB->CRL = 0x00444444; 
	GPIOB->CRH = 0x44444400;
	
	// configure ports 6, 7, 8, 9 as outputs for timer 4
	GPIOB->CRL  |= 	bit(31) |						// PB7 AFO push/pull
									bit(29) | bit(28) |	// PB7 output 50MHz
									bit(27) | 					// PB6 AFO push/pull
									bit(25) | bit(24);	// PB6 output 50MHz
	
	GPIOB->CRH  |=  bit(7)  |						// PB9 AFO push/pull
									bit(5)  | bit(4) |  // PB9 output 50MHz
									bit(3)  | 					// PB8 AFO push/pull
									bit(1)  | bit(0);   // PB8 otput 50MHz
	
}
