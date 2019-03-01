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
#include "WCGArg.h"

/* Demo task priorities. */
#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 7 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 8 )
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

UBaseType_t start_PRIORITY = 7;
//UBaseType_t vLEDShark_PRIORITY = 3;
//UBaseType_t LED456_PRIORITY = 3;
//uint16_t configMINIMAL_STACK_SIZE = 128;
//uint16_t configMINIMAL_STACK_SIZE 128;
//uint16_t configMINIMAL_STACK_SIZE 128;
/*Create EventGroup*/
EventGroupHandle_t xEventGroupWCGFlag;
//EventGroupHandle_t xEventGroupLCDRefresh;
#define Bit0GetPressureByTime      (1<<0)
#define Bit4GetPressByUser         (1<<4)


BaseType_t CAT24_PC = 0;

xQueueHandle xQueueUart1Pressure;
xQueueHandle xQueuePressureValue;
xQueueHandle xQueuePressureValue1;
xQueueHandle xQueueUart2GPRS;
xQueueHandle xQueueUart3User;

SemaphoreHandle_t xSemBinKey;
SemaphoreHandle_t xSemBinSendByGPRS;
SemaphoreHandle_t xSemBinGPRSIsLink;
SemaphoreHandle_t xSemBinCalaTime;
SemaphoreHandle_t xSemBinReCala;
SemaphoreHandle_t xSemBinQuickShow;
SemaphoreHandle_t xSemBinGetPress;
//TaskHandle_t xLCDUseCursor;

/*
 * Create the demo tasks then start the scheduler.
 */
int main(void) {//2个LED灯闪烁
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

void vApplicationIdleHook(void) {
    /* Schedule the co-routines from within the idle task hook. */
    //    vCoRoutineSchedule();
    /*add low power function*/
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

extern void vTaskKey(void *parameter);
extern void vTaskGetPressure(void* parameter);
extern void vTaskShowLCD(void *parameter);
extern void vTaskCalaClockTime(void* parameter);

void task_start(void *parameter) {
    /*key scan and handle*/
    xTaskCreate(vTaskKey, "vTaskKey", 256, NULL, configMAX_PRIORITIES - 4, NULL);
    /*show lcd*/
    xTaskCreate(vTaskShowLCD, "vTaskShowLCD", 512, NULL, configMAX_PRIORITIES - 2, NULL);
    /*calc  int time*/
    xTaskCreate(vTaskCalaClockTime, "vTaskCalcClockTime", 256, NULL, configMAX_PRIORITIES - 1, NULL);
    vTaskDelete(NULL);
}

/*************************************
Function: vTaskGetPressure
Description: Sample :get Pressure
Input: parameter
Output: 无
Notice: 
 **************************************/
void vTaskGetPressure(void* parameter) {
    unsigned char ucGetData[10];
    unsigned char ucGetOffset;
    unsigned char ucCount = 0;
    ErrCode xErrCodeInPressure = ErrorNoError;

    /*use UART1 and RS485_CON(PEc6),initialization UART2*/
    vUART1Init();
    /*create uart1 receive buffer notify*/
    xQueueUart1Pressure = xQueueCreate(1, UART1_BUFFER_LENGTH);
    /*IEE745 float*/
    xQueuePressureValue = xQueueCreate(1, 4);
    /*create semaphorebinary*/
    //    vSemaphoreCreateBinary(xSemBinGetPress);
    /*create flag event*/
    //    xEventGroupWCGFlag = xEventGroupCreate();
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
                        /*post message to lcd show*/
                        if (xQueueSend(xQueuePressureValue, ucGetData + 4, 0) != pdPASS) {
                            /*error tip*/
                            Nop();
                        }
                        /*post message to storage*/
                        if (xQueueSend(xQueuePressureValue1, ucGetData + 4, 0) != pdPASS) {
                            /*error tip*/
                            Nop();
                        }
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
                sLCDArg.sLCDArg1.Error = 1;
            }
        }
        Nop();
    }
}

/*************************************
Function: vTaskSendByGPRS
Description: GPRS communication
Input: parameter
Output: 无
Notice: 
 **************************************/
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
                vGPRSSendString((unsigned char *) GPRSCmdGetVersion);
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
                    if (Str_Find_Head(ucBuffer, (unsigned char*) GPRSVersion, usGetBufferSize, strlen((char *) GPRSVersion))) { /*GPRS is ready*/
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
                            if (Str_Find_Head(ucBuffer, (unsigned char*) GPRSVersion, usGetBufferSize, strlen((char*) GPRSVersion))) { /*GPRS is ready*/
                                //                                bGPRSIsReady = true;
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
                //error ip:GPRS is not connect ,or not in ready state
                Nop();
            }
        }
    }
}

/*************************************
Function: vTaskKey
Description: key tasK
Input: parameter
Output: 无
Notice: 
 **************************************/
void vTaskKey(void *parameter) {
    unsigned char ucKeyState;
    /*create semaphore*/
    xSemBinKey = xSemaphoreCreateBinary();
    /*Init key*/
    vKeyInit();


    for (;;) {
        if (xSemaphoreTake(xSemBinKey, portMAX_DELAY) == pdTRUE) {
            /*get key state*/
            vKeyScan(&ucKeyState);
            /*delay*/
            vTaskDelay(10);
            /*key function*/
            vKeyUserFunction(ucKeyState, &sLCDArg.ucScreenID);
        }
    }
}

/*************************************
Function: vTaskUserCommunication
Description: user 485 communication
Input: parameter
Output: 无
Notice: 
 **************************************/
void vTaskUserCommunication(void *parameter) {
    vUART3Init();
    xQueueUart3User = xQueueCreate(1, UART3_BUFFER_LENGTH);
    for (;;) {
    }
}

/*************************************
Function: vTaskShowLCD
Description: task degree:show LCD
Input: parameter
Output: 无
Notice: three is 3 modes at least can refresh screen:
        1,mainPage fresh by itself,2s refresh automatically 0x00
        2,by add key S2,fresh quick  0x01 
        3,in other screen page,like passwordpage ,setpage1,so,use falg semaphare is suit
 **************************************/
void vTaskShowLCD(void* parameter) {
    /*init LCD*/
    vLCDInit();
    /*init LED*/
    vLEDInit();
    /*set mainpage in start*/
    sLCDArg.ucScreenID = eMainPage1;
    /*get mainpage show items*/
    vSetScreenID(&sLCDArg.ucScreenID);
    /*show screen*/
    vLCDShowScreen();
    /*create semapharebinary*/
    xSemBinReCala = xSemaphoreCreateBinary();
    xSemBinQuickShow = xSemaphoreCreateBinary();
    for (;;) {
        LEDGreenLAT ^= 1;
        /*wait for sem*/
        xSemaphoreTake(xSemBinQuickShow, sLCDArg.uiRefreshTime);
        /*main screen show*/
        if (sLCDArg.ucScreenID <= eMainPage3) {
            sLCDArg.ucScreenID++;
            /*repeat show main screen*/
            if (sLCDArg.ucScreenID > eMainPage3) {
                sLCDArg.ucScreenID = 0;
            }
            /*change screen*/
            vSetScreenID(&sLCDArg.ucScreenID);
        } else {
            /*show othe rpage,like ePasswordPage*/
            Nop();
        }
        /*show LCD by sLCDArg*/
        vLCDShowScreen();
    }
}

/*************************************
Function: vTaskCalaClockTime
Description: task degree:Calc Alarm time
Input: parameter
Output: 无
Notice: 
 **************************************/
void vTaskCalaClockTime(void *parameter) {
    struct sGlobalWCGArg sArg;
    unsigned int uiSampleTimes;
    unsigned int uiSendTimes;
    static long ulSetTime;
    static long ulLastTime;

    /*read WCGArg*/
    vReadWCGArg(&sArg);
    uiSampleTimes = sArg.SamplePeriodTime;
    uiSendTimes = sArg.SendPeriodTime;
    ulLastTime = 0;

    /*init PCF8583*/
    vPCF8583Init(sArg.DataTime);

    /*calc clock time by set time*/
    xSemBinCalaTime = xSemaphoreCreateBinary();

    for (;;) {
        /*wait for sem to cala time*/
        if (xSemaphoreTake(xSemBinCalaTime, portMAX_DELAY)) {
            /*read wcg arg*/
            vReadWCGArg(&sArg);
            if (xSemaphoreTake(xSemBinReCala, 10)) {
                /*read wcg arg*/
                vReadWCGArg(&sArg);
                uiSampleTimes = sArg.SamplePeriodTime;
                uiSendTimes = sArg.SendPeriodTime;
                ulLastTime = 0;
            }
            /*calc times*/
            if (!uiSampleTimes)
                uiSampleTimes = sArg.SamplePeriodTime;
            if (!uiSendTimes)
                uiSendTimes = sArg.SendPeriodTime;
            if (uiSampleTimes > uiSendTimes) {
                ulSetTime = uiSendTimes;
                uiSampleTimes = uiSampleTimes - uiSendTimes;
                uiSendTimes = sArg.SendPeriodTime;
            } else if (uiSampleTimes < uiSendTimes) {
                ulSetTime = uiSampleTimes;
                uiSendTimes = uiSendTimes - uiSampleTimes;
                uiSampleTimes = sArg.SamplePeriodTime;
            } else {
                ulSetTime = uiSampleTimes;
                uiSendTimes = sArg.SendPeriodTime;
                uiSampleTimes = sArg.SamplePeriodTime;
            }
            ulSetTime = ulLastTime + ulSetTime;
            ulLastTime = ulSetTime;
            vPCF8583SetAlarmTimeByTimestamp(&ulSetTime);
        }

    }
}

/*************************************
Function: vTaskStorageSample
Description: task degree:Storage pressure  and timestamp
Input: parameter
Output: 无
Notice: 
 **************************************/
void vTaskStorageSample(void *parameter) {
    unsigned char pucWriteData[9], pucReadData[9];
    unsigned char ucCnt, ucCopCnt, ucStorageCode = 0;
    unsigned long ulTimeStamp = 0;
    unsigned char ucPress[6];
    unsigned int uiYear;

    xCAT24ReadPointCount(CAT24_PC);
    for (;;) {
        //        for (ucCount = 0; ucCount < 7196; ucCount++) {
        /*MaxValue=0xE0D9*/
        if (CAT24_PC > 0xE0D9) {
            vTaskDelay(10);
            CAT24_PC = 0;
        }
        /*get*/
        //        for (ucNum = 0; ucNum < 8; ucNum++)
        //            pucWriteData[ucNum] = ucCount;
        //        vTaskDelay(10);
        /*packet  timestamp+pressure*/
        ulTimeStamp = tPCF8583ReadTime(&uiYear);
        CopyDat(pucWriteData, (uint8_t*) & ulTimeStamp, 4);
        if (xQueueReceive(xQueuePressureValue1, ucPress, 10) == pdPASS) {
            CopyDat(pucWriteData + 3, ucPress, 4);
            do {
                /*wirte data*/
                xCAT24WriteReadPage(CAT24_PC, pucWriteData, 8, CAT24_WRITE);
                /*read data*/
                xCAT24WriteReadPage(CAT24_PC, pucReadData, 8, CAT24_READ);
                /*repeat 3 times,compare write data and read data*/
                for (ucCnt = 0; ucCnt < 8; ucCnt++) {
                    if (pucReadData[ucCnt] != pucWriteData[ucCnt]) {
                        /*tip error code*/
                        ucStorageCode = 0x10;
                        break;
                    }
                }
                ucCopCnt++;
                if (ucCopCnt > 3) {
                    ucStorageCode = 0x20;
                    break;
                }
            } while (!ucStorageCode);
            if (!ucStorageCode)
                CAT24_PC += 9;
            xCAT24WritePointCount(CAT24_PC);
        }
        /*for test*/
        //        for (ucCount = 0; ucCount < 128; ucCount++) {
        //            WriteData[ucCount] = ucCount;
        //        }
        //        xCAT24WriteReadPage(GPRS_ADD, WriteData, 128, CAT24_WRITE);
        //        vTaskDelay(10);
        //        xCAT24WriteReadPage(GPRS_ADD, ReadData, 128, CAT24_READ);
        //         vUART1Send(ReadData,128);
    }
}




