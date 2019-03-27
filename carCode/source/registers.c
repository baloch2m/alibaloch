//#include <stdint.h>
#include "../header/registers.h"

volatile uint32_t * regRCC_APB2ENR;
volatile uint32_t * regRCC_APB1ENR;

volatile uint32_t * regGPIOB_ODR;
volatile uint32_t * regGPIOB_CRH;
volatile uint32_t * regGPIOB_BSRR;
volatile uint32_t * regGPIOB_BRR;


void setupRegs(void)
{
 
	regRCC_APB2ENR = (volatile uint32_t *)RCC_APB2ENR;
	regRCC_APB1ENR = (volatile uint32_t *)RCC_APB1ENR;
	
  regGPIOB_ODR   = (volatile uint32_t *)GPIOB_ODR ; 
	regGPIOB_CRH   = (volatile uint32_t *)GPIOB_CRH ; 
	regGPIOB_BSRR  = (volatile uint32_t *)GPIOB_BSRR ; 
  regGPIOB_BRR   = (volatile uint32_t *)GPIOB_BRR ; 
 
}
