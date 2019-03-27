#include "LCD.h"
#include "stm32f10x.h" 
#include "clock.h"
#include "IO.h"
#include "string.h"


/*
* Name: commandToLCD
* Type: PUBLIC
* Parameters: a single byte of command information for the LCD controller
* Returns: nothing
* Description: This function generates control timing and data signals to send one command byte to the LCD
*/
void commandToLCD (uint8_t data) {
	GPIOB->BSRR = LCD_CM_ENA; //RS low, E high; command mode enable
	delay(8000);
	GPIOC->ODR &= 0xFF00; //GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; //GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_CM_DIS; //RS low, E low
	delay(80000);
}

/*
* Name: LCDInit
* Type: PUBLIC
* Parameters: N/A
* Returns: N/A
* Description: This function initializes and configures the i/o ports for the LCD
*/
void LCDInit() {
		/* LCD Port Configuration */
	// Configuration Port B 0, 1, 5 - output, gen. purpose push-pull
		GPIOB->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE5;
		GPIOB->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF5;
		/* LCD Data Lines Configuration */
	// Port C [7:0] - output, init the pc0 to pc7 lcd
	GPIOC->CRL |= GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_MODE2 | GPIO_CRL_MODE3 | 
	                GPIO_CRL_MODE4 | GPIO_CRL_MODE5 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7;// LED 1 to LED 4 MODE
	GPIOC->CRL &= ~GPIO_CRL_CNF0 & ~GPIO_CRL_CNF1 & ~GPIO_CRL_CNF2 & ~GPIO_CRL_CNF3 & ~GPIO_CRL_CNF4 & ~GPIO_CRL_CNF5 & 
									~GPIO_CRL_CNF6 & ~GPIO_CRL_CNF7;
	commandToLCD (LCD_8B2L); //Function set: 8 bit, 2 line, font 
	commandToLCD (LCD_MCR); // Entry mode set
	commandToLCD (LCD_CLR); // Display clear
	commandToLCD (LCD_DCB); // Display on
	commandToLCD (LCD_MCR); // Move Cursor Right
}

/*
* Name: dataToLCD
* Type: PUBLIC
* Parameters: a single byte of data information for the LCD controller
* Returns: nothing
* Description: This function prints data sent to the LCD display
*/
void dataToLCD (uint8_t data) {
	GPIOB->BSRR = LCD_DM_ENA; // RS high, E high; data mode enable
	delay(8000);
	GPIOC->ODR &= 0xFF00; // GOOD: clears the low bits without affecting high bits
	GPIOC->ODR |= data; // GOOD: only affects lowest 8 bits of Port C
	delay(8000);
	GPIOB->BSRR = LCD_DM_DIS; // RS low, E low
	delay(80000);
}


void stringToLCD (char* message) {//declare input message as char pointer

	uint16_t messageLength = strlen(message);//find length of message
	int i = 0; 
	for (i = 0; i < messageLength; i++) {
		dataToLCD(*message);
		message++;
	}
}
 void print4Bit (uint32_t switchValue) {

	switch (switchValue) {
			case (0):
				dataToLCD('0');
				break;
			case (1): 
				dataToLCD('1');
				break;
			case (2): 
				dataToLCD('2');
				break;
			case (3): 
				dataToLCD('3');
				break;
			case (4): 
				dataToLCD('4');
				break;
			case (5): 
				dataToLCD('5');
				break;
			case (6): 
				dataToLCD('6');
				break;
			case (7): 
				dataToLCD('7');
				break;
			case (8): 
				dataToLCD('8');
				break;
			case (9): 
				dataToLCD('9');
				break;
			case (10): 
				dataToLCD('A');
				break;
			case (11): 
				dataToLCD('B');
				break;
			case (12): 
				dataToLCD('C');
				break;
			case (13): 
				dataToLCD('D');
				break;
			case (14): 
				dataToLCD('E');
				break;
			case (15): 
				dataToLCD('F');
				break;
			default:
				break;
		}
}

 void print32BitHex (uint32_t i32Num) {
	int i = 28; // shift variable
	char cPrefix[] = "0x"; 
	stringToLCD(cPrefix);

	while (i >= 0) {
		print4Bit((i32Num >> i) & 0x0000000F);		
		i -= 4;
	}
	dataToLCD(',');
}			
	


