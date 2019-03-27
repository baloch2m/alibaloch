

/* Include files */
#include "stm32f10x.h"
#include <stdint.h>
#include "clock.h"
#include "VR.h"
#include "LCD.h"
#include "IO.h"

int main (void)	
	{

int answer;

	// Initialization Functions and fucntion that are excuted only once	
	clock_Init();
	gpioInit();
	led_IO_init();
	LCDInit();
	usart3Init();
	led_switch_operate();
	endVR();
	// Functions to execute continuously
		GPIOA->ODR |= GPIO_ODR_ODR9 | GPIO_ODR_ODR10 | GPIO_ODR_ODR11 | GPIO_ODR_ODR12;//all outputs off

	while(1)
	{	
		// VR active listening 
		answer = 0x40;
		
		
		
		delay(1000000);	
		comGroup1();
	

		answer=Group1(answer);
				

			// Line 1 Text,Name 
					
				if ( answer == 0x00 ){ //ON

			 GPIOC->ODR ^= GPIO_ODR_ODR9;
				commandToLCD (LCD_CLR);
				commandToLCD(LCD_LN1);
				stringToLCD("Answer is:");
				delay(1000000);
				commandToLCD(LCD_LN2);
				print32BitHex(answer);
					answer = 0x40;
				delay(1000000);


			}
	 
			else if( answer == 0x04 ){//OFF
			
				 GPIOC->ODR ^= GPIO_ODR_ODR9;
					
			 // Line 1 Text,Name
			  commandToLCD (LCD_CLR);
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
				answer = 0x40;
		    delay(1000000);


			}
		 if (answer == 0x01)								
			{
				turn_right();
					
			// Line 1 Text,Name
			  commandToLCD (LCD_CLR);  
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
					answer = 0x40;
		    delay(1000000);


			}
			else if (answer == 0x02)								
			{
				move_forward();	
				
			// Line 1 Text,Name
			  commandToLCD (LCD_CLR);
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
					answer = 0x40;
		    delay(1000000);


			}
			 //endVR();
		 if (answer == 0x03)								
			{
        turn_left();
					
			// Line 1 Text,Name
			  commandToLCD (LCD_CLR);
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
					answer = 0x40;
		    delay(1000000);


			}
		 if (answer == 0x05)								
			{
				stop();
				
			// Line 1 Text,Name
			  commandToLCD (LCD_CLR);
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
					answer = 0x40;
		    delay(1000000);


			}
			else if (answer == 0x06)								
			{
				move_backward();
		// Line 1 Text,Name
			  commandToLCD (LCD_CLR);
		    commandToLCD(LCD_LN1);
		    stringToLCD("Answer is:");
		    delay(1000000);
		    commandToLCD(LCD_LN2);
		    print32BitHex(answer);
				answer = 0x40;
		    delay(1000000);


			}
			}

			}	
