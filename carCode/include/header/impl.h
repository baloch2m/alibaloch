
#ifndef impl_H
#define impl_H

#include "main.h"

//  continuous, free-running countdown timer highest available clock driver frequency
void timer_init(void);

// inits the timer same as timer_int but also enables interrupt and prescales to 1Hz rollover
void timer_init_with_interrupts(void);

// returns the current value of the timer as a 16-bit signed int
int16_t timer_start(void);

// compares it to the current timer value.  
// It returns the number of timer ticks since the supplied start_time
// check for upto one wrap around from timer
int16_t timer_stop(int16_t start_time);

// releases the timer and resets it to its default state
void timer_shutdown(void);

#endif
