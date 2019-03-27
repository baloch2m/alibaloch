#ifndef usart_H
#define usart_H

#include "math.h"
#include "main.h"

typedef struct _input{

	char command[5];
	uint16_t arg_val;
	char* arg_ptr;
	
}Input;

extern uint32_t USER_INPUT_VALUE;

void setupUSART2(void);
void sendByte(uint32_t tx);
uint32_t getByte(void);
void print(char const str[]);
void println(char const str[]);
bool queryLed(uint32_t led);
void setLed(uint32_t led);
void resetLed(uint32_t led);
void help(void);
void date(void);
uint32_t getLed(char arg[]);
char* extractArg(char arg[], int pos, int len);
Input readInput(char input[], int l);
void timer(void);
void driver(void);
uint16_t parseInt(char str[], int pos, int len);
void convert_16(char ary[], int16_t num);
void convert_32(char ary[], int32_t num);
void processInput(uint32_t tx);
#endif
