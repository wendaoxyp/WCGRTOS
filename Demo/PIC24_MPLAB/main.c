/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

 ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
 ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

 ***************************************************************************
 *                                                                       *
 *    FreeRTOS provides completely free yet professionally developed,    *
 *    robust, strictly quality controlled, supported, and cross          *
 *    platform software that is more than just the market leader, it     *
 *    is the industry's de facto standard.                               *
 *                                                                       *
 *    Help yourself get started quickly while simultaneously helping     *
 *    to support the FreeRTOS project by purchasing a FreeRTOS           *
 *    tutorial book, reference manual, or both:                          *
 *    http://www.FreeRTOS.org/Documentation                              *
 *                                                                       *
 ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
 */
// ****************************************************************************
/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the standard demo application tasks.
 * In addition to the standard demo tasks, the following tasks and tests are
 * defined and/or created within this file:
 *
 * "Fast Interrupt Test" - A high frequency periodic interrupt is generated
 * using a free running timer to demonstrate the use of the 
 * configKERNEL_INTERRUPT_PRIORITY configuration constant.  The interrupt 
 * service routine measures the number of processor clocks that occur between
 * each interrupt - and in so doing measures the jitter in the interrupt 
 * timing.  The maximum measured jitter time is latched in the usMaxJitter 
 * variable, and displayed on the LCD by the 'Check' as described below.  
 * The fast interrupt is configured and handled in the timer_test.c source 
 * file.
 *
 * "LCD" task - the LCD task is a 'gatekeeper' task.  It is the only task that
 * is permitted to access the LCD directly.  Other tasks wishing to write a
 * message to the LCD send the message on a queue to the LCD task instead of 
 * accessing the LCD themselves.  The LCD task just blocks on the queue waiting 
 * for messages - waking and displaying the messages as they arrive.  The LCD
 * task is defined in lcd.c.  
 * 
 * "Check" task -  This only executes every three seconds but has the highest 
 * priority so is guaranteed to get processor time.  Its main function is to 
 * check that all the standard demo tasks are still operational.  Should any
 * unexpected behaviour within a demo task be discovered the 'check' task will
 * write "FAIL #n" to the LCD (via the LCD task).  If all the demo tasks are 
 * executing with their expected behaviour then the check task writes the max
 * jitter time to the LCD (again via the LCD task), as described above.
 */

/* Standard includes. */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "semphr.h"
#include "event_groups.h"

/* Demo application includes. */
#include "Config_Bit.h"
#include "BlockQ.h"
#include "crflash.h"
#include "blocktim.h"
#include "integer.h"
#include "comtest2.h"
#include "partest.h"
#include "LCD.h"
#include "timertest.h"
#include "WCGDeBug.h"
#include "PCF8583.h"
#include "CAT24C512.h"
#include "UART1.h"
#include "UART2.h"
#include "TR04.h"
#include "LED.h"
#include "KEY.h"
#include "Common.h"
#include "CheckData.h"
#include "Error.h"
#include "DW02.h"

/* Demo task priorities. */
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainCOM_TEST_PRIORITY				( 2 )

/* The check task may require a bit more stack as it calls sprintf(). */
#define mainCHECK_TAKS_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )

/* The execution period of the check task. */
#define mainCHECK_TASK_PERIOD				( ( TickType_t ) 3000 / portTICK_PERIOD_MS )

/* The number of flash co-routines to create. */
//#define mainNUM_FLASH_COROUTINES			( 5 )

/* Baud rate used by the comtest tasks. */
#define mainCOM_TEST_BAUD_RATE				( 19200 )

/* The LED used by the comtest tasks.  mainCOM_TEST_LED + 1 is also used.
See the comtest.c file for more information. */
#define mainCOM_TEST_LED					( 6 )

/* The frequency at which the "fast interrupt test" interrupt will occur. */
#define mainTEST_INTERRUPT_FREQUENCY		( 20000 )

/* The number of processor clocks we expect to occur between each "fast
interrupt test" interrupt. */
#define mainEXPECTED_CLOCKS_BETWEEN_INTERRUPTS ( configCPU_CLOCK_HZ / mainTEST_INTERRUPT_FREQUENCY )

/* The number of nano seconds between each processor clock. */
#define mainNS_PER_CLOCK ( ( unsigned short ) ( ( 1.0 / ( double ) configCPU_CLOCK_HZ ) * 1000000000.0 ) )

/* Dimension the buffer used to hold the value of the maximum jitter time when
it is converted to a string. */
#define mainMAX_STRING_LENGTH				( 20 )

/*-----------------------------------------------------------*/

/*
 * The check task as described at the top of this file.
 */
//static void vCheckTask(void *pvParameters);

/*
 * Setup the processor ready for the demo.
 */
//static void prvSetupHardware(void);

/* Prototypes for the standard FreeRTOS callback/hook functions implemented
within this file. */
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);

/*-----------------------------------------------------------*/

/* The queue used to send messages to the LCD task. */
//static QueueHandle_t xLCDQueue;

/*-----------------------------------------------------------*/
void task_start(void *parameter);
//void vLEDShark(void *pvParameters);
//void LED456(void *pvParameters);

UBaseType_t start_PRIORITY = 4;
UBaseType_t vLEDShark_PRIORITY = 3;
//UBaseType_t LED456_PRIORITY = 3;
//uint16_t configMINIMAL_STACK_SIZE = 128;
//uint16_t configMINIMAL_STACK_SIZE 128;
//uint16_t configMINIMAL_STACK_SIZE 128;
/*Create EventGroup*/
EventGroupHandle_t xEventGroupWCGFlag;
#define Bit0GetPressureByTime      (1<<0)
#define Bit4GetPressByUser         (1<<4)
SemaphoreHandle_t xSemBinGetPress;

BaseType_t CAT24_PC = 0;

xQueueHandle xQueueUart1Pressure;
xQueueHandle xQueueUart2GPRS;
xQueueHandle xQueueUart3User;

SemaphoreHandle_t xSemBinKey;
SemaphoreHandle_t xSemBinSendByGPRS;
SemaphoreHandle_t xSemBinGPRSIsLink;

/*
 * Create the demo tasks then start the scheduler.
 */
int main(void) {//2¸öLEDµÆÉÁË¸
    /* Configure any hardware required for this demo. */
    //    prvSetupHardware();

    /* Create the standard demo tasks. */
    //    vStartBlockingQueueTasks(mainBLOCK_Q_PRIORITY);
    //    vStartIntegerMathTasks(tskIDLE_PRIORITY);
    //    vStartFlashCoRoutines(mainNUM_FLASH_COROUTINES);
    //    vAltStartComTestTasks(mainCOM_TEST_PRIORITY, mainCOM_TEST_BAUD_RATE, mainCOM_TEST_LED);
    //    vCreateBlockTimeTasks();

    /* Create the test tasks defined within this file. */
    //    xTaskCreate(vCheckTask, "Check", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL);
#if (ENABLE_DEBUG==1)   
    vDebugTaskHook();
#endif
    /* Start the task that will control the LCD.  This returns the handle
    to the queue used to write text out to the task. */
    //	xLCDQueue = xStartLCDTask();
    xTaskCreate(task_start, "start_task", configMINIMAL_STACK_SIZE, NULL, start_PRIORITY, NULL); /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
    /* Start the high frequency interrupt test. */
    //    vSetupTimerTest(mainTEST_INTERRUPT_FREQUENCY);

    /* Finally start the scheduler. */
    vTaskStartScheduler();

    /* Will only reach here if there is insufficient heap available to start
    the scheduler. */
    return 0;
}

/*-----------------------------------------------------------*/

//static void prvSetupHardware(void) {
//    vParTestInitialise();
//}

/*-----------------------------------------------------------*/

//static void vCheckTask(void *pvParameters) {
//    /* Used to wake the task at the correct frequency. */
//    TickType_t xLastExecutionTime;
//
//    /* The maximum jitter time measured by the fast interrupt test. */
//    extern unsigned short usMaxJitter;
//
//    /* Buffer into which the maximum jitter time is written as a string. */
//    static char cStringBuffer[ mainMAX_STRING_LENGTH ];
//
//    /* The message that is sent on the queue to the LCD task.  The first
//    parameter is the minimum time (in ticks) that the message should be
//    left on the LCD without being overwritten.  The second parameter is a pointer
//    to the message to display itself. */
//    xLCDMessage xMessage = {0, cStringBuffer};
//
//    /* Set to pdTRUE should an error be detected in any of the standard demo tasks. */
//    unsigned short usErrorDetected = pdFALSE;
//
//    /* Remove compiler warnings. */
//    (void) pvParameters;
//
//    /* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
//    works correctly. */
//    xLastExecutionTime = xTaskGetTickCount();
//
//    for (;;) {
//        /* Wait until it is time for the next cycle. */
//        vTaskDelayUntil(&xLastExecutionTime, mainCHECK_TASK_PERIOD);
//
//        /* Has an error been found in any of the standard demo tasks? */
//
//        if (xAreIntegerMathsTaskStillRunning() != pdTRUE) {
//            usErrorDetected = pdTRUE;
//            sprintf(cStringBuffer, "FAIL #1");
//        }
//
//        if (xAreComTestTasksStillRunning() != pdTRUE) {
//            usErrorDetected = pdTRUE;
//            sprintf(cStringBuffer, "FAIL #2");
//        }
//
//        if (xAreBlockTimeTestTasksStillRunning() != pdTRUE) {
//            usErrorDetected = pdTRUE;
//            sprintf(cStringBuffer, "FAIL #3");
//        }
//
//        if (xAreBlockingQueuesStillRunning() != pdTRUE) {
//            usErrorDetected = pdTRUE;
//            sprintf(cStringBuffer, "FAIL #4");
//        }
//
//        if (usErrorDetected == pdFALSE) {
//            /* No errors have been discovered, so display the maximum jitter
//            timer discovered by the "fast interrupt test". */
//            sprintf(cStringBuffer, "%dns max jitter", (short) (usMaxJitter - mainEXPECTED_CLOCKS_BETWEEN_INTERRUPTS) * mainNS_PER_CLOCK);
//        }
//
//        /* Send the message to the LCD gatekeeper for display. */
//        xQueueSend(xLCDQueue, &xMessage, portMAX_DELAY);
//    }
//}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void) {
    /* Schedule the co-routines from within the idle task hook. */
    //    vCoRoutineSchedule();
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName) {
    (void) pcTaskName;
    (void) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();
    for (;;);
}

void vLEDShark1(void *pvParameters) {
    pvParameters = pvParameters;
    vLEDInit();

    for (;;) {
        _LATE7 ^= 1; //green led
        vTaskDelay(500);
    }
}

//void LED456(void *pvParameters) {
//    pvParameters = pvParameters;
//    vLEDInit();
//    for (;;) {
//        vLEDShark(LEDGreen, 1000, 300, 4);
//    }
//}
extern void vTaskKey(void *parameter);
extern void vTaskGetPressure(void* parameter);

void task_start(void *parameter) {
    vLCDInit();
    //    UART3_Init();
    xTaskCreate(vTaskGetPressure, "vTaskGetPressure", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL);
    xTaskCreate(vTaskKey, "led456", mainCHECK_TAKS_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY - 1, NULL);
    /*Get EEPROM Write Point Count*/
    //    xCAT24ReadPointCount(CAT24_PC);
    vTaskDelete(NULL);
}

void vTaskGetPressure(void* parameter) {
    unsigned char ucGetData[10];
    unsigned char ucGetOffset;
    unsigned char ucCount = 0;
    float fPress;
    ErrCode xErrCodeInPressure = ErrorNoError;

    /*use UART1 and RS485_CON(PEc6),initialization UART2*/
    vUART1Init();
    /*create uart1 receive buffer notify*/
    xQueueUart1Pressure = xQueueCreate(1, UART1_BUFFER_LENGTH);
    /*create semaphorebinary*/
    //    vSemaphoreCreateBinary(xSemBinGetPress);
    /*create flag event*/
    xEventGroupWCGFlag = xEventGroupCreate();
    for (;;) {
        /* it's time to get pressure or user need get pressure,then wake up WCG,and send xGetPressSem*/
        /*wait for uart1 receive data*/
        if (xQueueReceive(xQueueUart1Pressure, ucUart1Buffer, portMAX_DELAY) != pdFALSE) {
            /*xEventGropWCGFlag bit0|bit4 is One,every 30ms*/
            /*delay for get last byte*/
            vTaskDelay(3);
            vUART1RxGet4Byte();
            ucCount = 0;
            while (bUART1BufferRead(ucGetData + ucCount++));

            if (ucCount >= PressReciveLength) {
                ucGetOffset = Str_Find_Head(ucGetData, TR04, 9, 2);
                if (ucGetOffset) {
                    if (bCRC16IsRight1(ucGetData + ucGetOffset - 1, 7)) {
                        CharToFloat(&fPress, ucGetData + ucGetOffset + 2);
                        vLCDShowNums((unsigned int) (fPress * 100), false);
                        vLCDShowDigitalPoint(2);
                    } else {
                        xErrCodeInPressure = ErrorGetPressureValueCRCNoRight;
                    }
                } else
                    xErrCodeInPressure = ErrorGetPressureValueInvaildHead;
            } else if (ucCount == 0) {
                xErrCodeInPressure = ErrorGetPressureValueNoAck;
            } else
                xErrCodeInPressure = ErrorGetPressureValueLossBytes;
            if (xErrCodeInPressure != ErrorNoError) {
                vErrorPrintCode(xErrCodeInPressure, OutputInLCD);
                vLCDShowPoint(eError, SEGSHOW);
            }
        }
        Nop();
    }
}

void vTaskSendByGPRS(void*parameter) {
    uint8_t ucCount;
    uint8_t ucBuffer[256];
    uint16_t usGetBufferSize = 0;
    bool bGPRSIsReady = false;

    /*Init UART2*/
    vUART2Init();
    /*create semaphorebinary*/
    xSemBinSendByGPRS = xSemaphoreCreateBinary();
    /*clear ucBuffer*/
    //    memset(ucBuffer,1,256);
    for (;;) {
        /*wait for time to send data by GPRS*/
        if (xSemaphoreTake(xSemBinSendByGPRS, portMAX_DELAY) == pdTRUE) {
            /*GPRS EN is High*/
            for (ucCount = 0; ucCount < 5; ucCount++) {
                GPRSEnable();
                vTaskDelay(100);
                /*send "+TURONG TECH"*/
                vGPRSSendString((uint8_t *) GPRSCmdGetVersion);
                /*Receive "+TXYBJT DTU Software,VERtrkj_v04.0??"*/
                vUART2SetGetLength(36);
                /*wait for get buffer*/
                if (xQueueReceive(xQueueUart2GPRS, ucUart2Buffer, pdMS_TO_TICKS(1000)) == pdTRUE) {
                    /*get last byte*/
                    vUART2RxGet4Byte();
                    /*clear buffer*/
                    usGetBufferSize = 0;
                    /*receive data*/
                    while (bUART2BufferRead(ucBuffer + usGetBufferSize++));
                    /*check data*/
                    if (Str_Find_Head(ucBuffer, (unsigned char*) GPRSVersion, usGetBufferSize, strlen(GPRSVersion))) { /*GPRS is ready*/
                        bGPRSIsReady = true;
                    }
                }
            }
            if (bGPRSIsReady) {
                /*Send GPRS */
                vGPRSSendString((uint8_t *) GPRSCmdDialing);
                /*Wait for GPRS link*/
                if (xSemaphoreTake(xSemBinGPRSIsLink, pdMS_TO_TICKS(50000)) == pdTRUE) {
                    /*packet send to GPRS protocal*/

                    for (ucCount = 0; ucCount < 3; ucCount++) {
                        /*send GPSR*/
                        vGPRSSendString("it's pressure protocal");
                        vUART2SetGetLength(4);
                        /*wait for get buffer*/
                        if (xQueueReceive(xQueueUart2GPRS, ucUart2Buffer, pdMS_TO_TICKS(3000)) == pdTRUE) {
                            /*get last byte*/
                            vUART2RxGet4Byte();
                            /*clear buffer*/
                            usGetBufferSize = 0;
                            /*receive data*/
                            while (bUART2BufferRead(ucBuffer + usGetBufferSize++));
                            /*check data*/
                            if (Str_Find_Head(ucBuffer, (unsigned char*) GPRSVersion, usGetBufferSize, strlen(GPRSVersion))) { /*GPRS is ready*/
                                bGPRSIsReady = true;
                            }
                        }
                    }
                    Nop();
                } else {
                    //                FailGPRSConnectCount++;
                    //ERRORSend();
                    Nop();
                }
                /*GPRS EN is Low*/
                GPRSDisable();
            } else {
                //error
                Nop();
            }
        }
    }
}

void vTaskKey(void *parameter) {
    unsigned char ucKeyState;
    /*create semaphore*/
    xSemBinKey = xSemaphoreCreateBinary();
    /*Init key*/
    vKeyInit();
    vLEDInit();
    for (;;) {
        if (xSemaphoreTake(xSemBinKey, portMAX_DELAY) == pdTRUE) {
            //            vKeyScan(&ucKeyState);
            //            vTaskDelay(10);
            //            vKeyUserFunction(ucKeyState);
            vUART1Send((unsigned char*) TR04, sizeof (TR04));
            vLEDShark(LEDGreen, 300, 100, 3);
        }
    }
}

void vTaskUserCommunication(void *parameter) {
    xQueueUart3User = xQueueCreate(1, UART3_BUFFER_LENGTH);
    for (;;) {
    }
}

void vTaskShowLCD(void *parameter) {
    vLCDInit();

    for (;;) {

    }
}

void vTaskCalaClockTime(void *parameter) {

    for (;;) {
    }
}

void vTaskStorageSample(void *parameter) {
    for (;;) {
        /*packet data in eeprom*/
        //            xCAT24WriteBytes(CAT24_PC, Data, length);
        //            CAT24_PC += length;            
        //            xCAT24WritePointCount(CAT24_PC );
    }
}



