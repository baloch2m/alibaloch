
#ifndef main_H
#define main_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

static xQueueHandle xQueue;

#include "leds.h"

#include "registers.h"

#include "tim4.h"

#include "irqHandler.h"


#include "adc.h"

#include "motor.h"
  
#include "usart.h"

#endif
