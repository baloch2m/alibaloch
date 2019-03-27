/*
    FreeRTOS V7.2.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!
    
    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?                                      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    
    http://www.FreeRTOS.org - Documentation, training, latest information, 
    license and contact details.
    
    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool.

    Real Time Engineers ltd license FreeRTOS to High Integrity Systems, who sell 
    the code with commercial support, indemnification, and middleware, under 
    the OpenRTOS brand: http://www.OpenRTOS.com.  High Integrity Systems also
    provide a safety engineered and independently SIL3 certified version under 
    the SafeRTOS brand: http://www.SafeRTOS.com.
*/

/*
 * This is a very simple demo that demonstrates task and queue usages only in
 * a simple and minimal FreeRTOS configuration.  Details of other FreeRTOS 
 * features (API functions, tracing features, diagnostic hook functions, memory
 * management, etc.) can be found on the FreeRTOS web site 
 * (http://www.FreeRTOS.org) and in the FreeRTOS book.
 *
 * Details of this demo (what it does, how it should behave, etc.) can be found
 * in the accompanying PDF application note.
 *
*/

#include "header/main.h"


/* Priorities at which the tasks are created. */
#define usf_PRIORITY                  			( tskIDLE_PRIORITY + 3 )
#define velocitySensor_PRIORITY             ( tskIDLE_PRIORITY + 2 )
#define stateManager_PRIORITY               ( tskIDLE_PRIORITY + 1 )
#define ui_PRIORITY                  				( tskIDLE_PRIORITY + 4 )


/* The ITM port is used to direct the printf() output to the serial window in 
the Keil simulator IDE. */
#define mainITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define mainITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define mainDEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define mainTRCENA          0x01000000

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */ // not sure if this is required
//xQueueHandle xUIQueue ;// = NULL;
xQueueHandle xUSFQueue;// = NULL;
xQueueHandle xUSBQueue;// = NULL;

/*
 * Redirects the printf() output to the serial window in the Keil simulator
 * IDE.
 */
int fputc( int iChar, FILE *pxNotUsed );

/*-----------------------------------------------------------*/

/* One array position is used for each task created by this demo.  The 
variables in this array are set and cleared by the trace macros within
FreeRTOS, and displayed on the logic analyzer window within the Keil IDE -
the result of which being that the logic analyzer shows which task is
running when. */
unsigned long ulTaskNumber[ configEXPECTED_NO_RUNNING_TASKS ];

/*-----------------------------------------------------------*/

int main(void)
{

		//ulTaskNumber[0] = 1;
	
		// initilize a timer for prescision measurements
		timer2_init();
	
		// setup timer for pwm output to motors
		stm32_Timer4Setup();
		stm32_GpioTim4Setup();
	
		//testPWM();
		
    /* Create the queues. */
    //xUIQueue 		= xQueueCreate(1, sizeof( uint16_t ));
	  xUSFQueue 	= xQueueCreate(1, sizeof( uint32_t ));
		xUSBQueue 	= xQueueCreate(1, sizeof( uint32_t ));
	
		//testInterruptUSF();
	
		//testUSF();

		if(xUSFQueue != 0 && xUSBQueue != 0) //xUIQueue != 0 &&
    {
			
//			// create task for sensing objects infront of vehicle
//			xTaskCreate( ultrasonicSensorTest, (signed char *) "usf",
//							 configMINIMAL_STACK_SIZE, NULL,
//							 usf_PRIORITY, NULL );
			
			// create task for sensing objects infront of vehicle
			xTaskCreate( ultrasonicSensorF, (signed char *) "usf",
							 configMINIMAL_STACK_SIZE, NULL,
							 usf_PRIORITY, NULL );
			
			// create task for sensing the vehicles velocity
//			xTaskCreate( velocitySensor, (signed char *) "VelocitySensor",
//							 configMINIMAL_STACK_SIZE, NULL,
//							 velocitySensor_PRIORITY, NULL );

			// create task to manage what state the vehicle should be in terms of motion
			xTaskCreate( stateManager, (signed char *) "stateManager",
							 configMINIMAL_STACK_SIZE, NULL,
							 stateManager_PRIORITY, NULL );
			
			// create a task to acquire input from the user
			xTaskCreate( ui, (signed char *) "UI",
							 configMINIMAL_STACK_SIZE, NULL,
							 ui_PRIORITY, NULL );
			
//			xTaskCreate( testUI, (signed char *) "TEST_UI",
//							 configMINIMAL_STACK_SIZE, NULL,
//							 ui_PRIORITY-1, NULL );
		
	
			/* Start the tasks running. */
			vTaskStartScheduler();
			
		}

    /* If all is well we will never reach here as the scheduler will now be
    running.  If we do reach here then it is likely that there was insufficient
    heap available for the idle task to be created. */
    for( ;; );
        
}

/*-----------------------------------------------------------*/

int fputc( int iChar, FILE *pxNotUsed ) 
{
    /* Just to avoid compiler warnings. */
    ( void ) pxNotUsed;

    if( mainDEMCR & mainTRCENA ) 
    {
        while( mainITM_Port32( 0 ) == 0 );
        mainITM_Port8( 0 ) = iChar;
    }

    return( iChar );
}
