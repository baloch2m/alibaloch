#include "stm32f10x.h"

#define GREEN_ON		0x00000200 		// set bit
#define GREEN_OFF		0x02000000 		// reset bit
#define BLUE_ON			0x00000100 		// set bit
#define BLUE_OFF		0x01000000 		// reset bit
 
 
void clock_Init(void);
void gpioInit(void);
void usart3Init(void);
void usart3TX(int dataChar);
int  usart3RX(void);
int  usart3RX_6thWord(void);
void delay(uint32_t delay);
void comGroup1(void);

void endVR(void);
int Group1(int answer);



