#include "stm32f10x.h"
 #include "clock.h"
 #include "IO.h"
 
// CLOCK AND TIMING FUNCTIONS

void clockInit(void)
{
    uint32_t temp = 0x00;
    //If you hover over the RCC you can go to the definition and then
    //see it is a structure of all the RCC registers.  Then you can
    //simply assign a value.
    RCC->CFGR = 0x07050002;     // Output PLL/2 as MCO,   MCO need to go  the second MSB the (7) to work with PWM to (0)
                                // PLLMUL X3, PREDIV1 is PLL input

    RCC->CR =  0x01010081;      // Turn on PLL, HSE, HSI

    while (temp != 0x02000000)  // Wait for the PLL to stabilize
    {
        temp = RCC->CR & 0x02000000; //Check to see if the PLL lock bit is set
    }

    //Enable peripheral clocks for various ports and subsystems
    //Bit 4: Port C Bit3: Port B Bit 2: Port A
    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN |RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    // Write a 0xB ( 1011b ) into the configuration and mode bits for PA8 (AFIO)
    GPIOA->CRH |= GPIO_CRH_CNF8_1 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE8_0 ;
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0 ;
}

/*
* Name:         void delay()
* Paramaters:   32 bit delay value, ( a value of 6000
                gives approximately 1 mS of delay)
* Description:  This function creates a delay
*/
void delay1(uint32_t count)
{
    int i=0;
    for(i=0; i< count; ++i)
    {
    }
}



