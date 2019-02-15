/*
 * File:   KEY.c
 * Author: zw
 *
 * Created on 2019年1月10日, 下午2:36
 */

#include "KEY.h"

#if (UseFreeRTOSInKey == 1)
#include "FreeRTOS.h"
#include "semphr.h"
#include "WCGArg.h"
#include "LCD.h"
extern xSemaphoreHandle xSemBinKey;
#endif

/*************************************
Function: vDelay10ms
Description: 延时10ms
Input: 时间
Output: 无
 *************************************/
static void vKeyDelay10ms(unsigned int usDelay10ms) {
    unsigned int usConut;
    while (usDelay10ms-- > 0)
        for (usConut = 0; usConut < DELAY10MS; usConut++)
            Nop();
}

/*************************************
Function: vDelay100ms
Description: 延时100ms
Input: 时间
Output: 无
 *************************************/
/*static void vKeyDelay100ms(unsigned int usDelay100ms) {
    unsigned int usConut;
    while (usDelay100ms-- > 0)
        for (usConut = 0; usConut < DELAY100MS; usConut++)
            Nop();
}*/

#if  (UseKeyInterrupt == 1)

/*************************************
Function: vIOCInit
Description: key interrupt initialization
Input: void 
Output: void
 *************************************/
void vKeyInterruptInit(void) {
    _CN14PUE = 1;
    _CN15PUE = 1;
    _CN16PUE = 1;
    _CN14IE = 1;
    _CN15IE = 1;
    _CN16IE = 1;
    /*freertos priority is 2*/
    _CNIP = 1;
    /*清除标志位*/
    _CNIF = 0;
    _CNIE = 1;
}
#endif 

#if (UseKeyInterrupt == 1)

/*************************************
Function: IOC
Description: 按键输入
Input: void 
Output: void
 *************************************/

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
#if (UseFreeRTOSInKey == 1)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#else
    unsigned char ucKeyState;
#endif
    if (!ReadKey1State | !ReadKey2State | !ReadKey3State)
#if (UseFreeRTOSInKey == 1)    
        xSemaphoreGiveFromISR(xSemBinKey, &xHigherPriorityTaskWoken);
    //        portYIELD_WITHIN_API(xHigherPriorityTaskWoken);
#else
        vKeyScan(&ucKeyState);
#endif         
    _CNIF = 0; //清除标志位;
}
#endif 

/*************************************
Function: vKeyInit
Description: IO设置数字输入
Input: 无 
Output:无 
 *************************************/
void vKeyInit(void) {
    /*key1设置数字输入*/
    SetKey1ANS = 0;
    /*key1设置输入*/
    SetKey1Tris = 1;
    /*key2设置数字输入*/
    SetKey2ANS = 0;
    /*key2设置输入*/
    SetKey2Tris = 1;
    //    /*key3设置数字输入*/
    //    SetKey3ANS = 0;
    /*key3设置输入*/
    SetKey3Tris = 1;
#if (UseKeyInterrupt == 1)
    /*定义配置IOC*/
    vKeyInterruptInit();
#endif 
}

/*************************************
Function: usReadKeyIO
Description: read key IO
Input: 无 
Output:key IO Port
 *************************************/
static unsigned int usReadKeyIO(void) {
    return (ReadKey1State || (ReadKey2State << 1) || (ReadKey3State << 2));
}

/*************************************
Function: vKeyScan
Description: 按键处理
Input: 无 
Output:按键类型
 *************************************/
void vKeyScan(void* vKeyState) {
    unsigned char ucKeyState = InvalidKEY;
    unsigned char ucCount = 0;
    unsigned int usKeyIOCurrent, usKeyIONext;

    usKeyIOCurrent = usReadKeyIO();
    if (usKeyIOCurrent) {
        /*前沿消抖*/
        vKeyDelay10ms(1);
        /*check key is really push*/
        usKeyIOCurrent = usReadKeyIO();
        if (usKeyIOCurrent) {
            for (ucCount = 0; ucCount < 200; ucCount++) {
                vKeyDelay10ms(1);
                usKeyIONext = usReadKeyIO();
                if (usKeyIONext != usKeyIOCurrent) {
                    break;
                }
                /*for*/
            }
            /*end if (usKeyIOCurrent)*/
        }

        if (ucCount >= 200) {
            ucKeyState = (LongKEY << 6) | usKeyIOCurrent;
        } else if (ucCount > 20) {
            ucKeyState = (ShortKEY << 6) | usKeyIOCurrent;
        } else {
            ucKeyState = (InvalidKEY << 6) | usKeyIOCurrent;
        }
    }
    /*return which key and key state*/
    *((unsigned char*) vKeyState) = ucKeyState;
}

/*************************************
Function: vMainScreenKey2ShortHandle
Description: 主界面下,切换到下一个界面, use sLCDArg.ucLCDArg3
Input: void 
Output: void
 *************************************/

static void vMainScreenKey2ShortHandle(void) {
    /*page +1*/
    sLCDArg.ucScreenID += 1;
    /*overflow handle*/
    if (sLCDArg.ucScreenID >= MaxScreenPage)
        sLCDArg.ucScreenID = 0;
}

/*************************************
Function: vMainScreenKey3LongHandle
Description: 主界面下,切换到下一个界面, use sLCDArg.ucLCDArg3
Input: void 
Output: void
 *************************************/

static void vMainScreenKey3LongHandle(void) {
    /*page set password*/
    sLCDArg.ucScreenID = ePasswordPage;
}

/*************************************
Function: vSetScreenShortKey1Handle
Description: 数字加一
Input: ucKeyState 
Output: void
 *************************************/

static void vSetScreenShortKey1Handle(void) {
    /*select set number*/
    switch (sLCDArg.sLCDArg2.Cursor) {
        case 0:
        {
            sLCDArg.sLCDArg1.num0 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num0 > 9)
                sLCDArg.sLCDArg1.num0 = 0;
            break;
        }
        case 1:
        {
            sLCDArg.sLCDArg1.num1 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num1 > 9)
                sLCDArg.sLCDArg1.num1 = 0;
            break;
        }
        case 2:
        {
            sLCDArg.sLCDArg1.num2 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num2 > 9)
                sLCDArg.sLCDArg1.num2 = 0;
            break;
        }
        case 3:
        {
            sLCDArg.sLCDArg1.num3 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num3 > 9)
                sLCDArg.sLCDArg1.num3 = 0;
            break;
        }
        case 4:
        {
            sLCDArg.sLCDArg1.num4 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num4 > 9)
                sLCDArg.sLCDArg1.num4 = 0;
            break;
        }
        case 5:
        {
            sLCDArg.sLCDArg1.num5 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num5 > 9)
                sLCDArg.sLCDArg1.num5 = 0;
            break;
        }
        case 6:
        {
            sLCDArg.sLCDArg1.num6 += 1;
            /*overflow handle*/
            if (sLCDArg.sLCDArg1.num6 > 9)
                sLCDArg.sLCDArg1.num6 = 0;
            break;
        }
    }
}

/*************************************
Function: vSetScreenLongKey2Handle
Description: deal witch key by keystate 
Input: ucKeyState 
Output: void
 *************************************/

static void vSetScreenLongKey2Handle(void) {
    //    unsigned char ucLCDNum;

    //    ucLCDNum = *((unsigned char *) parameter);
    /*increase*/
    //    ucLCDNum++;
    /*mod*/
    //    ucLCDNum %= 10;
    //    /*return parameter*/
    //    *((unsigned char *) parameter) = ucLCDNum;
}

/*************************************
Function: vKeyUserFunction
Description: deal witch key by keystate 
Input: ucKeyState 
Output: void
 *************************************/
void vKeyUserFunction(unsigned char ucKeyState, unsigned char* pcuScreenID) {

    switch (*pcuScreenID) {
        case eMainPage1:
        case eMainPage2:
        case eMainPage3:
        {
            /*switch key function*/
            switch (ucKeyState) {
                case 0xC1://LongKEY1 +              
                case 0x41://ShortKEY1 +
                case 0xC2://LongKEY2 >
                case 0x44://ShortKEY3 OK
                {
                    /*无动作*/
                    Nop();
                    break;
                }
                case 0x42://ShortKEY2 >
                {
                    vMainScreenKey2ShortHandle();
                    break;
                }
                case 0xC4://LongKEY3 OK
                {
                    vMainScreenKey3LongHandle();
                    break;
                }
            }
            break;
        }
        case ePasswordPage:
        case eSetPage1:
        case eSetPage2:
        case eSetPage3:
        case eSetPage4:
        case eSetPage5:
        case eSetPage6:
        case eSetPage7:
        case eSetPage8:
        case eSetPage9:
        {
            switch (ucKeyState) {
                case 0xC1://LongKEY1
                case 0xC4://LongKEY3
                {
                    /*无动作*/
                    Nop();
                    break;
                }
                case 0x41://ShortKEY1
                {
                    vSetScreenShortKey1Handle();
                    break;
                }
                case 0xC2://LongKEY2
                {
                    vSetScreenLongKey2Handle();
                    break;
                }
                case 0x42://ShortKEY2
                {
                    break;
                }
                case 0x44://ShortKEY3
                {
                    break;
                }
            }
            break;
        }
    }
    //return ucScreeID;
}






