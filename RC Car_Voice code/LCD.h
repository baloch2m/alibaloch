/******************************************************************************
 * Name:    LCD.h
 * Description: 44780 initialization
 * Version: V1.00
 * Authors: Mohammed Benhammou
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 *
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *****************************************************************************/
#include <stdint.h>

// Commands for Hitachi 44780 compatible LCD controllers
#define LCD_8B2L 0x38   // Enable 8 bit data, 2 display lines
#define LCD_DCB  0x0F 	// Enable Display, Cursor, Blink
#define LCD_DON	 0x0C	  // Enable Display only
#define LCD_MCR  0x06 	// Set Move Cursor Right
#define LCD_CLR  0x01 	// Home and clear LCD
#define LCD_LN1  0x80 	// Set DDRAM to start of line 1
#define LCD_LN2  0xC0 	// Set DDRAM to start of line 2
// Control signal manipulation for LCDs on 352/384/387 board
// PB0:RS PB1:ENA PB5:R/W*
#define LCD_CM_ENA 0x00210002 // Command mode enable
#define LCD_CM_DIS 0x00230000 // Command mode disable
#define LCD_DM_ENA 0x00200003 // Data mode enable
#define LCD_DM_DIS 0x00220001 // Data mode disable

void commandToLCD(uint8_t data);	// LCD command initialization function
void dataToLCD(uint8_t data); // LCD data
void LCDInit(void);
void stringToLCD(char*message);// this will write the hole string to the screen.

 void print4Bit (uint32_t switchValue);
 void print32BitHex (uint32_t i32Num);


