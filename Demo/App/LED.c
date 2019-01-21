/*
 * File:   LED.c
 * Author: zw
 *
 * Created on 2019年1月8日, 下午2:50
 */
#include "LED.h"


#if  (UseFreeRTOS == 0)

/*************************************
Function: vDelay100ms
Description: 延时100ms
Input: 时间
Output: 无
 *************************************/
static void vDelay100ms(unsigned int usDelay100ms) {//延时100ms
    unsigned int usCount;

    while (usDelay100ms-- > 0)
        for (usCount = 0; usCount < DELAY100MS; usCount++)
            Nop();
}
#else
#include "FreeRTOS.h"
#include "task.h"
#endif

/*************************************
Function: vLEDInit
Description: initialization LED IO
Input: 无
Output: 无
 *************************************/
void vLEDInit(void) {//LATBbits.LATB15=1
    /*set led light*/
    LEDGreenTRIS = 0;
    LEDRedTRIS = 0;
}

/*************************************
Function: vLEDHandle
Description: handle led
Input: ucLEDIO,which LED ;bLEDSta:high:lignt;low:dark
Output: 无
 *************************************/
void vLEDHandle(unsigned char ucLEDIO, bool bLEDSta) {//LATBbits.LATB15=1
    /*set led light*/
    switch (ucLEDIO) {
            /*only Green led*/
        case 1:
        {
            LEDGreenLAT = bLEDSta;
            break;
        }
            /*only Red led*/
        case 2:
        {
            LEDRedLAT = bLEDSta;
            break;
        }
            /*only both led*/
        case 3:
        {
            LEDGreenLAT = bLEDSta;
            LEDRedLAT = bLEDSta;
            break;
        }
    }
}

/*************************************
Function: vLEDShark
Description: LED显示
Input: 亮、灭时间，执行次数
Output: 无
 *************************************/
void vLEDShark(unsigned char ucLEDIO,
        unsigned int usLedOnTimeMs,
        unsigned int usLedOffTimeMs,
        unsigned char ucSharkCnt) {
    unsigned char ucCount;
    for (ucCount = 0; ucCount < ucSharkCnt; ucCount++) {
        /*always in shark*/
        if (ucSharkCnt == 255)
            ucSharkCnt = 0;
        /*set led light*/
        vLEDHandle(ucLEDIO, 1);
#if (UseFreeRTOS==1)
        vTaskDelay(usLedOnTimeMs);
#else
        vDelay100ms(usLedOnTimeMs);
#endif
        /*Set led dark*/
        vLEDHandle(ucLEDIO, 0);
#if (UseFreeRTOS==1)
        vTaskDelay(usLedOffTimeMs);
#else
        vDelay100ms(usLedOffTimeMs);
#endif
    }
}

