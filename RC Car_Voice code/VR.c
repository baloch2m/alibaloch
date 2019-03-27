
#include "stm32f10x.h"
#include <stdint.h>
#include "VR.h"
#include "LCD.h"

void clock_Init(void) {
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
}
void gpioInit(void){
	// Configure Port B10 (USART TX) as alternate function output push-pull.
	GPIOB->CRH &= ~GPIO_CRH_CNF10 & ~GPIO_CRH_MODE10;
	GPIOB->CRH |= GPIO_CRH_CNF10_1 | GPIO_CRH_MODE10;
	
	// Configure Port C8 & C9 as general purpose output push-pull.
	GPIOC->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_MODE8;
	GPIOC->CRH &= ~GPIO_CRH_CNF9 & ~GPIO_CRH_CNF8;
}
void usart3Init(void) {
	// USART enable, and TX & RX enable.
	USART3->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	// Oversampling by 16, 8 data bits, parity control disabled.
	USART3->CR1 &= ~USART_CR1_OVER8 & ~USART_CR1_M & ~USART_CR1_PCE;
	
	// 1 Stop bit
	USART3->CR2 &= ~USART_CR2_STOP;
	
	// 9600 Bps
	USART3->BRR = 0x09C4; 
}

void usart3TX(int dataChar) {
	// Wait for transmit register to clear. 
	// when txe = 1: data transferred to shift register
	// !(txe = 1)
	// when data is not transferred to the shift register, wait. 
	while(!(USART3->SR & USART_SR_TXE)){};
	USART3->DR = dataChar;
}

int usart3RX(void){
	// Wait for transmit register to clear.
	// when RXNE = 1: received data is ready to be read
	// !(RXNE = 1)
	// when data is not shifted to the data register, wait. 
	while(!(USART3->SR & USART_SR_RXNE)){};
	return USART3->DR ;
}
int usart3RX_6thWord()// this function is to return the 6th word in from
{	
	// the recived signal
	// this will act as a filter to id the recongnized command heared
	// the returned value will be one of(00,01,02,03,04,05,06)
	int i , Char;
	for(i=0;i<6;i++){Char = usart3RX();}
	Char = usart3RX();
	//GPIOC->ODR= BLUE_ON;
			return Char;
}

void delay(uint32_t delay){
/* 	Paramaters: 	32 bit delay value, (a value of 6000 gives approximately 1 mS of delay)
 * 	Description: 	This function creates a delay. */
  int i = 0;
	for(i = 0; i < delay; ++i){
	}
}


void comGroup1(){ // all (7) commands are active 
		
			usart3TX(0xAA);//start command
			usart3TX(0x09);//size of commad
			usart3TX(0x30);//recognize
	    usart3TX(0x00);//ON
			usart3TX(0x01);//turn right 
			usart3TX(0x02);//move forward 
			usart3TX(0x03);//turn left
			usart3TX(0x04);//OFF 
			usart3TX(0x05);//stop
			usart3TX(0x06);//move backward 
			usart3TX(0x0A);//end command
}

void endVR()
{
			usart3TX(0xAA);//start command
			usart3TX(0x02);////size of commad
			usart3TX(0x31);// clear recognizer
			usart3TX(0x0A);//end commad
	
}


int Group1(int answer)
{
				while (!(answer == 0x00 || answer==0x01 ||answer== 0x02 || answer==0x03||answer== 0x04 || answer==0x05
								|| answer==0x06)) 
			{	

				delay(1000000);
				answer=usart3RX_6thWord();			
		 }
return answer;


}


