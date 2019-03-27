
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

#include "stm32f10x.h"

#include "test.h"
#include "carTasks.h"
#include "peripheralFunctions.h"
#include "irqHandler.h"
#include "timers_stmConf.h"
#include "interrupt_stmConf.h"
#include "GPIO_RCC_stmConf.h"

#endif
