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
#include "event_groups.h"
#include "Common.h"
extern xSemaphoreHandle xSemBinKey;
#endif

const unsigned int TEN_POW[5] = {1, 10, 100, 1000, 10000};

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
    _CNIP = 2;
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
    return ((!ReadKey1State) | ((!ReadKey2State) << 1) | ((!ReadKey3State) << 2));
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
        //        vKeyDelay10ms(1);
        /*check key is really push*/
        //        usKeyIOCurrent = usReadKeyIO();
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
        } else {
            ucKeyState = (ShortKEY << 6) | usKeyIOCurrent;
        }
        //        } else if (ucCount > 20) {
        //            ucKeyState = (ShortKEY << 6) | usKeyIOCurrent;
        //        } else {
        //            ucKeyState = (InvalidKEY << 6) | usKeyIOCurrent;
        //        }
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
//extern EventGroupHandle_t xEventGroupLCDRefresh;
extern SemaphoreHandle_t xSemBinQuickShow;

static void vMainScreenKey2ShortHandle(void) {
    /*page +1*/
    sLCDArg.ucScreenID += 1;
    /*overflow handle*/
    if (sLCDArg.ucScreenID > eMainPage3)
        sLCDArg.ucScreenID = 0;
    /*set quick fresh screen*/
    vSetScreenID(&sLCDArg.ucScreenID);
    /*give show tip*/
    xSemaphoreGive(xSemBinQuickShow);
    //    xEventGroupSetBits(xEventGroupLCDRefresh, 0x01);
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
    sLCDArg.uiRefreshTime = 500;
    vSetScreenID(&sLCDArg.ucScreenID);

    //    xEventGroupSetBits(xEventGroupLCDRefresh, 0x02);
}

/*************************************
Function: vNumAdd
Description: 数字加一
Input: ucNum 
Output: new num
 *************************************/
static unsigned char vNumAdd(unsigned char ucNum) {
    unsigned char ucTemp;
    unsigned char ucMaxValue;

    ucTemp = ucNum + 1;
    switch (sLCDArg.ucScreenID) {
        case eSetPage1:
        case eSetPage2:
        {
            ucMaxValue = ((sLCDArg.sLCDArg2.Cursor == 2) || (sLCDArg.sLCDArg2.Cursor == 5)) ? 2 : 9;
            break;
        }
        default:
        {
            ucMaxValue = 9;
            break;
        }
    }
    /*overflow handle*/
    if (ucTemp > ucMaxValue)
        ucTemp = 0;
    return ucTemp;
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
            //            switch (sLCDArg.ucScreenID) {
            //                case e
            //                default:
            //                {
            sLCDArg.sLCDArg1.num0 = vNumAdd(sLCDArg.sLCDArg1.num0);
            //                    break;
            //                }
            //            }

            break;
        }
        case 1:
        {
            sLCDArg.sLCDArg1.num1 = vNumAdd(sLCDArg.sLCDArg1.num1);
            break;
        }
        case 2:
        {
            sLCDArg.sLCDArg1.num2 = vNumAdd(sLCDArg.sLCDArg1.num2);
            break;
        }
        case 3:
        {
            sLCDArg.sLCDArg1.num3 = vNumAdd(sLCDArg.sLCDArg1.num3);
            break;
        }
        case 4:
        {
            sLCDArg.sLCDArg1.num4 = vNumAdd(sLCDArg.sLCDArg1.num4);
            break;
        }
        case 5:
        {
            sLCDArg.sLCDArg1.num5 = vNumAdd(sLCDArg.sLCDArg1.num5);
            break;
        }
        case 6:
        {
            sLCDArg.sLCDArg1.num6 = vNumAdd(sLCDArg.sLCDArg1.num6);
            break;
        }
    }
}

/*************************************
Function: vSetScreenLongKey2Handle
Description: deal witch key by keystate 
Input: void 
Output: void
 *************************************/

static void vSetScreenLongKey2Handle(void) {
    sLCDArg.ucScreenID = eMainPage1;
    sLCDArg.uiRefreshTime = 5000;
    vSetScreenID(&sLCDArg.ucScreenID);
}

/*************************************
Function: bSharkNumIsValue
Description: 
Input: void 
Output: bool
 *************************************/
static bool bSharkNumIsValue(unsigned char ucNum) {
    bool bValueNum = false;
    if (ucNum == NUMHIDE) {
        sLCDArg.sLCDArg2.Cursor++;
    } else {
        bValueNum = true;
    }
    return bValueNum;
}

/*************************************
Function: vSetScreenShortKey2Handle
Description: deal witch key by keystate 
Input: void 
Output: void
 *************************************/
void vSetScreenShortKey2Handle(void) {
    unsigned char ucMaxPosition;
    bool bValueNum = false;
    /*get max shark position*/
    switch (sLCDArg.ucScreenID) {
        case ePasswordPage:
        {
            ucMaxPosition = 4;
            break;
        }
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
            ucMaxPosition = 6;
            break;
        }
        default:
        {
            ucMaxPosition = NoUseCursor;
            break;
        }
    }/*cursor +1*/
    sLCDArg.sLCDArg2.Cursor++;
    do {
        switch (sLCDArg.sLCDArg2.Cursor) {
            case 0:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num0);
                break;
            }
            case 1:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num1);
                break;
            }
            case 2:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num2);
                break;
            }
            case 3:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num3);
                break;
            }
            case 4:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num4);
                break;
            }
            case 5:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num5);
                break;
            }
            case 6:
            {
                bValueNum = bSharkNumIsValue(sLCDArg.sLCDArg1.num6);
            }
        }
        if (sLCDArg.sLCDArg2.Cursor >= ucMaxPosition) {
            sLCDArg.sLCDArg2.Cursor = 0;
            break;
        }
    } while (!bValueNum);
}

static unsigned long ulCalaNumsByLCD(unsigned char* ucData, unsigned char ucHighestID,
        unsigned long ulMaxValue) {
    unsigned long ulOffset = 0;
    bool bGetFirstNum = false;
    char ucCnt;

    if (!ucHighestID) {
        ulOffset = ucData[ucHighestID];
    } else {
        for (ucCnt = ucHighestID; ucCnt >= 0; ucCnt--) {
            if (!bGetFirstNum) {
                if (*(ucData + ucCnt) != NUMHIDE) {
                    bGetFirstNum = true;
                } else {
                    continue;
                }
            }
            ulOffset += *(ucData + ucCnt) * (TEN_POW[(unsigned char) ucCnt]);
        }
    }
    if (ulOffset > ulMaxValue)
        ulOffset = ulMaxValue;

    return ulOffset;
}

/*************************************
Function: vSetScreenShortKey3Handle
Description: deal witch key by keystate 
Input: void 
Output: void
 *************************************/
extern SemaphoreHandle_t xSemBinReCala;

static void vSetScreenShortKey3Handle(void) {
    struct sGlobalWCGArg arg1;
//    unsigned int uiOffset;
    unsigned char ucTemp[7];

    /*get lcd Num*/
    ucTemp[0] = sLCDArg.sLCDArg1.num0;
    ucTemp[1] = sLCDArg.sLCDArg1.num1;
    ucTemp[2] = sLCDArg.sLCDArg1.num2;
    ucTemp[3] = sLCDArg.sLCDArg1.num3;
    ucTemp[4] = sLCDArg.sLCDArg1.num4;
    ucTemp[5] = sLCDArg.sLCDArg1.num5;
    ucTemp[6] = sLCDArg.sLCDArg1.num6;
    /*get password*/
    if (sLCDArg.ucScreenID == ePasswordPage) {
        /*password right*/
        if (bPasswordIsRight(ucTemp)) {
            sLCDArg.ucScreenID = eSetPage1;
            vSetScreenID(&sLCDArg.ucScreenID);
        } else {
            /*password error*/
            sLCDArg.sLCDArg1.num0 = 0;
            sLCDArg.sLCDArg1.num1 = 0;
            sLCDArg.sLCDArg1.num2 = 0;
            sLCDArg.sLCDArg1.num3 = 0;
        }
    } else if (sLCDArg.ucScreenID > ePasswordPage) {
        vReadWCGArg(&arg1);
        switch (sLCDArg.ucScreenID) {
            case eSetPage1:
            {
                /*IP address HH HL*/
                arg1.IP[1] = ulCalaNumsByLCD(ucTemp, 2, 0xFF);
                arg1.IP[0] = ulCalaNumsByLCD(ucTemp + 3, 2, 0xFF);
                break;
            }
            case eSetPage2:
            {
                /*IP address LH LL*/
                arg1.IP[3] = ulCalaNumsByLCD(ucTemp, 2, 0xFF);
                arg1.IP[2] = ulCalaNumsByLCD(ucTemp + 3, 2, 0xFF);
                break;
            }
            case eSetPage3:
            {
                /*Port*/
                arg1.Port = ulCalaNumsByLCD(ucTemp, 4, 0xFFFF);
                break;
            }
            case eSetPage4:
            {
                /*work mode*/
                arg1.Configbit1.SampleMode = ucTemp[0];
                arg1.Configbit1.SendMode = ucTemp[3];
                break;
            }
            case eSetPage5:
            {
                /*sample set time*/
                arg1.SampleSetTime[0] = ulCalaNumsByLCD(ucTemp, 1, 100);
                arg1.SampleSetTime[1] = ulCalaNumsByLCD(ucTemp + 2, 1, 100);
                arg1.SampleSetTime[2] = ulCalaNumsByLCD(ucTemp + 4, 1, 100);
                break;
            }
            case eSetPage6:
            {
                /*sample period*/
                arg1.SamplePeriodTime = ulCalaNumsByLCD(ucTemp, 4, 100);
                break;
            }
            case eSetPage7:
            {
                /*send set time*/
                arg1.SendSetTime[0] = ulCalaNumsByLCD(ucTemp, 1, 100);
                arg1.SendSetTime[1] = ulCalaNumsByLCD(ucTemp + 2, 1, 100);
                arg1.SendSetTime[2] = ulCalaNumsByLCD(ucTemp + 4, 1, 100);
                break;
            }
            case eSetPage8:
            {
                /*send period time*/
                arg1.SamplePeriodTime = ulCalaNumsByLCD(ucTemp, 4, 0xFFFF);
                break;
            }
            case eSetPage9:
            {
                /*restart set arg*/
                xSemaphoreGive(xSemBinReCala);
                break;
            }
        }
        /*write arg*/
        vWriteWCGArg(arg1);
        sLCDArg.ucScreenID++;
        if (sLCDArg.ucScreenID > eSetPage9) {
            sLCDArg.ucScreenID = eSetPage1;
        }
        vSetScreenID(&sLCDArg.ucScreenID);
    } else {

        Nop();
    }
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
                    vSetScreenShortKey2Handle();
                    break;
                }
                case 0x44://ShortKEY3
                {
                    vSetScreenShortKey3Handle();
                    break;
                }
            }
            break;
        }
    }
    //return ucScreeID;
}






