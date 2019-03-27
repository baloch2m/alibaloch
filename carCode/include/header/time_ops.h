
#ifndef ops_H
#define ops_H

#include "main.h"

struct byte_8{

	int8_t a[8];

};

struct byte_128{

	int8_t a[128];

};

struct byte_1024{

	int8_t a[1024];

};

int16_t add_32();
int16_t add_64();
int16_t mul_32();
int16_t mul_64();
int16_t div_32();
int16_t div_64();
int16_t copy_8();
int16_t copy_128();
int16_t copy_1024();
int16_t base();
int16_t trial(int16_t (*f)(void));
  
#endif
