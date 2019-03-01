/*
 * File:   WCGArg.c
 * Author: root
 *
 * Created on February 15, 2019, 9:27 AM
 */
#include "WCGArg.h"
#include "LCD.h"
#include "PCF8583.h"
#include "UART1.h"
#include "Common.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "projdefs.h"
#include "WCGArg.h"
#include "KEY.h"
#include "WCGDeBug.h"
/*pressure production protocal*/
extern const unsigned char TR04[8];


#define EnterSettingPasswd 0x0001

static struct sGlobalWCGArg WCGArg = {
    {192, 168, 1, 55},
    5055,
    {0},
    {0x12, 0x12, 0x10}, 0x10,
    {0x14, 0x10, 0x0}, 0x30,
    0.0,
    0.0,
    {0x20, 0x11, 0x12, 0x31, 0x23, 0x59, 0x50},
};

/*************************************
 * Function: vSeteMainPage1
 * Description: Set Main page 1 show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSeteMainPage1(void) {
    struct tm tTimes;
    //    tTimes = sPCF8583ReadTime();
    /*for test*/
    tTimes.tm_sec = 0x32;
    tTimes.tm_min = 0x14;
    tTimes.tm_hour = 0x16;
    sLCDArg.sLCDArg1.num0 = tTimes.tm_sec & 0x0f;
    sLCDArg.sLCDArg1.num1 = tTimes.tm_sec >> 4;
    sLCDArg.sLCDArg1.num2 = tTimes.tm_min & 0x0f;
    sLCDArg.sLCDArg1.num3 = tTimes.tm_min >> 4;
    sLCDArg.sLCDArg1.num4 = tTimes.tm_hour & 0x0f;
    sLCDArg.sLCDArg1.num5 = tTimes.tm_hour >> 4;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.KPa = 0;
    /*no cursor*/
    sLCDArg.sLCDArg2.Cursor = NoUseCursor;
}

/*************************************
 * Function: vSeteMainPage2
 * Description:  Set Main page 2 show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSeteMainPage2(void) {
    struct tm tTimes;
    //    tTimes = sPCF8583ReadTime();
    /*for test*/
    tTimes.tm_yday = 0x20;
    tTimes.tm_mon = 0x12;
    tTimes.tm_year = 0x2018;
    sLCDArg.sLCDArg1.num0 = tTimes.tm_yday & 0x0f;
    sLCDArg.sLCDArg1.num1 = tTimes.tm_yday >> 4;
    sLCDArg.sLCDArg1.num2 = tTimes.tm_mon & 0x0f;
    sLCDArg.sLCDArg1.num3 = tTimes.tm_mon >> 4;
    sLCDArg.sLCDArg1.num4 = tTimes.tm_year & 0x0f;
    sLCDArg.sLCDArg1.num5 = tTimes.tm_year >> 4;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.KPa = 0;
    /*no cursor*/
    sLCDArg.sLCDArg2.Cursor = NoUseCursor;
}

/*************************************
 * Function: vSeteMainPage3
 * Description:  Set Main page 3 show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
extern QueueHandle_t xQueuePressureValue;

static void vSeteMainPage3(void) {
    //    float fPress = 0;
    //    unsigned char ucPress[4];
    unsigned char ucTmpNum = 0;
    static unsigned long ulLastPress = 0;
    /*wait for get new pressure data,if not get ,show last pressure*/
    //    if (xQueueReceive(xQueuePressureValue, ucPress, 10) == pdPASS) {
    //        CharToFloat(&fPress, ucPress);
    //        ulLastPress = (unsigned long) (fPress * 100) + 5;
    //    }
    sLCDArg.sLCDArg1.num0 = ulLastPress % 10;
    sLCDArg.sLCDArg1.num1 = ulLastPress / 10 % 10;
    sLCDArg.sLCDArg1.num2 = ulLastPress / 100 % 10;
    ucTmpNum = ulLastPress / 1000 % 10;
    sLCDArg.sLCDArg1.num3 = (ucTmpNum) ? ucTmpNum : NUMHIDE;
    ucTmpNum = ulLastPress / 10000 % 10;
    sLCDArg.sLCDArg1.num4 = (ucTmpNum) ? ucTmpNum : NUMHIDE;
    ucTmpNum = ulLastPress / 100000 % 10;
    sLCDArg.sLCDArg1.num5 = (ucTmpNum) ? ucTmpNum : NUMHIDE;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 2;
    sLCDArg.sLCDArg2.KPa = 1;
    /*no cursor*/
    sLCDArg.sLCDArg2.Cursor = NoUseCursor;
}

/*************************************
 * Function: vSetPasswordPage
 * Description:  Set Password show
 * Input: void
 * Output: void
 * notice: 
 *************************************/

static void vSetPasswordPage(void) {
    sLCDArg.sLCDArg1.num0 = 0;
    sLCDArg.sLCDArg1.num1 = 0;
    sLCDArg.sLCDArg1.num2 = 0;
    sLCDArg.sLCDArg1.num3 = 0;
    sLCDArg.sLCDArg1.num4 = NUMHIDE;
    sLCDArg.sLCDArg1.num5 = NUMHIDE;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.KPa = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vShowInterage
 * Description: show Interage
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vShowInterage(unsigned char ucInterage, unsigned char *pucOutputNum) {
    unsigned char ucNum0, ucNum1, ucNum2;

    ucNum0 = ucInterage / 100 % 10;
    ucNum1 = ucInterage / 10 % 10;
    ucNum2 = ucInterage % 10;

    if (ucNum0) {
        *(pucOutputNum + 2) = ucNum0;
        *(pucOutputNum + 1) = ucNum1;
        *pucOutputNum = ucNum2;
    } else {
        *(pucOutputNum + 2) = 0;
        if (ucNum1) {
            *(pucOutputNum + 1) = ucNum1;
            *pucOutputNum = ucNum2;
        } else {
            *(pucOutputNum + 1) = 0;
            *pucOutputNum = ucNum2;
        }
    }
}

/*************************************
 * Function: vSetPage1
 * Description:  Set Page show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage12(unsigned char* pucArg) {
    unsigned char ucTmp[3];

    vShowInterage(*(pucArg + 1), ucTmp);
    sLCDArg.sLCDArg1.num0 = ucTmp[0];
    sLCDArg.sLCDArg1.num1 = ucTmp[1];
    sLCDArg.sLCDArg1.num2 = ucTmp[2];
    vShowInterage(*pucArg, ucTmp);
    sLCDArg.sLCDArg1.num3 = ucTmp[0];
    sLCDArg.sLCDArg1.num4 = ucTmp[1];
    sLCDArg.sLCDArg1.num5 = ucTmp[2];
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 3;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetNums
 * Description:  set Nums,like 123412
 * Input: ulNums,position like (12345,4) show 1234
 * Output: void
 * notice: 
 *************************************/
extern unsigned int TEN_POW[5];

static void vSetNums(uint32_t ulNums, uint8_t ucPosition) {
    /*set value*/
    sLCDArg.sLCDArg1.num0 = ulNums % 10;
    sLCDArg.sLCDArg1.num1 = ulNums / 10 % 10;
    sLCDArg.sLCDArg1.num2 = ulNums / 100 % 10;
    sLCDArg.sLCDArg1.num3 = ulNums / 1000 % 10;
    sLCDArg.sLCDArg1.num4 = (ucPosition == 5) ? (ulNums / 10000 % 10) : NUMHIDE;
    sLCDArg.sLCDArg1.num5 = NUMHIDE;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
}

/*************************************
 * Function: vSetPage3
 * Description:  Set Page show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage3(void) {
    vSetNums(WCGArg.Port, 5);
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage4
 * Description:  Set Mode
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage4(void) {
    sLCDArg.sLCDArg1.num0 = WCGArg.Configbit1.SampleMode;
    sLCDArg.sLCDArg1.num1 = NUMHIDE;
    sLCDArg.sLCDArg1.num2 = NUMHIDE;
    sLCDArg.sLCDArg1.num3 = WCGArg.Configbit1.SendMode;
    sLCDArg.sLCDArg1.num4 = NUMHIDE;
    sLCDArg.sLCDArg1.num5 = NUMHIDE;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 3;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage5
 * Description:  Set Sample Set Time
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage5(void) {
    sLCDArg.sLCDArg1.num0 = WCGArg.SampleSetTime[2] % 10;
    sLCDArg.sLCDArg1.num1 = WCGArg.SampleSetTime[2] / 10 % 10;
    sLCDArg.sLCDArg1.num2 = WCGArg.SampleSetTime[1] % 10;
    sLCDArg.sLCDArg1.num3 = WCGArg.SampleSetTime[1] / 10 % 10;
    sLCDArg.sLCDArg1.num4 = WCGArg.SampleSetTime[0] % 10;
    sLCDArg.sLCDArg1.num5 = WCGArg.SampleSetTime[0] / 10 % 10;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage6
 * Description:  Set Sample Period 
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage6(void) {
    vSetNums(WCGArg.SamplePeriodTime, 4);
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage7
 * Description:  Set Page show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage7(void) {
    sLCDArg.sLCDArg1.num0 = WCGArg.SendSetTime[2] % 10;
    sLCDArg.sLCDArg1.num1 = WCGArg.SendSetTime[2] / 10 % 10;
    sLCDArg.sLCDArg1.num2 = WCGArg.SendSetTime[1] % 10;
    sLCDArg.sLCDArg1.num3 = WCGArg.SendSetTime[1] / 10 % 10;
    sLCDArg.sLCDArg1.num4 = WCGArg.SendSetTime[0] % 10;
    sLCDArg.sLCDArg1.num5 = WCGArg.SendSetTime[0] / 10 % 10;
    sLCDArg.sLCDArg1.num6 = NUMHIDE;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage8
 * Description:  Set Page show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage8(void) {
    vSetNums(WCGArg.SendPeriodTime, 4);
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetPage9
 * Description:  Set Page show
 * Input: void
 * Output: void
 * notice: 
 *************************************/
static void vSetPage9(void) {
    sLCDArg.sLCDArg1.num0 = 9;
    sLCDArg.sLCDArg1.num1 = 9;
    sLCDArg.sLCDArg1.num2 = 9;
    sLCDArg.sLCDArg1.num3 = 9;
    sLCDArg.sLCDArg1.num4 = 9;
    sLCDArg.sLCDArg1.num5 = 9;
    sLCDArg.sLCDArg1.num6 = 9;
    sLCDArg.sLCDArg2.Point = 0;
    sLCDArg.sLCDArg2.Cursor = 0;
}

/*************************************
 * Function: vSetScreenID
 * Description:  Set ScreenID
 * Input: void
 * Output: void
 * notice: 
 *************************************/

void vSetScreenID(void *ScreenID) {
    unsigned char ucScreenID = *((unsigned char*) ScreenID);
    //    vLCDClearScreen();
    switch (ucScreenID) {
        case eMainPage1:
        {
            vSeteMainPage1();
            break;
        }
        case eMainPage2:
        {
            vSeteMainPage2();
            break;
        }
        case eMainPage3:
        {
            vSeteMainPage3();
            break;
        }
        case ePasswordPage:
        {
            vSetPasswordPage();
            break;
        }
        case eSetPage1:
        {
            vSetPage12(WCGArg.IP);
            break;
        }
        case eSetPage2:
        {
            vSetPage12(WCGArg.IP + 2);
            break;
        }
        case eSetPage3:
        {
            vSetPage3();
            break;
        }
        case eSetPage4:
        {
            vSetPage4();
            break;
        }
        case eSetPage5:
        {
            vSetPage5();
            break;
        }
        case eSetPage6:
        {
            vSetPage6();
            break;
        }
        case eSetPage7:
        {
            vSetPage7();
            break;
        }
        case eSetPage8:
        {
            vSetPage8();
            break;
        }
        case eSetPage9:
        {
            vSetPage9();
            break;
        }
            /*  other page 
            case SetPage10:
                break;
             */
    }
    //    vLCDShowNums();
}

/*************************************
 * Function: vWriteWCGArg
 * Description: write WCG Arg
 * Input: psWriteArg
 * Output: void
 * notice: 
 *************************************/
void vWriteWCGArg(struct sGlobalWCGArg sWriteArg) {
    CopyDat(WCGArg.IP, sWriteArg.IP, 4);
    WCGArg.Port = sWriteArg.Port;
    WCGArg.Configbit1.SampleMode = sWriteArg.Configbit1.SampleMode;
    WCGArg.Configbit1.SendMode = sWriteArg.Configbit1.SendMode;
    CopyDat(WCGArg.SampleSetTime, sWriteArg.SampleSetTime, 3);
    WCGArg.SamplePeriodTime = sWriteArg.SamplePeriodTime;
    CopyDat(WCGArg.SendSetTime, sWriteArg.SendSetTime, 3);
    WCGArg.SendPeriodTime = sWriteArg.SendPeriodTime;
    WCGArg.PressureAlarmHighValue = sWriteArg.PressureAlarmHighValue;
    WCGArg.PressureAlarmLowValue = sWriteArg.PressureAlarmLowValue;
    CopyDat(WCGArg.DataTime, sWriteArg.DataTime, 7);
    /*use pointer maybe storage more 1 byte*/
    //    CopyDat((unsigned char*) &WCGArg, (unsigned char*) &sWriteArg, sizeof (struct sGlobalWCGArg) - 1);
}

/*************************************
 * Function: vReadWCGArg
 * Description:  read arg
 * Input: psReadArg
 * Output: void
 * notice: 
 *************************************/
void vReadWCGArg(struct sGlobalWCGArg *psReadArg) {
    CopyDat(psReadArg->IP, WCGArg.IP, 4);
    psReadArg->Port = WCGArg.Port;
    psReadArg->Configbit1.SampleMode = WCGArg.Configbit1.SampleMode;
    psReadArg->Configbit1.SendMode = WCGArg.Configbit1.SendMode;
    CopyDat(psReadArg->SendSetTime, WCGArg.SampleSetTime, 3);
    psReadArg->SamplePeriodTime = WCGArg.SamplePeriodTime;
    CopyDat(psReadArg->SendSetTime, WCGArg.SendSetTime, 3);
    psReadArg->SendPeriodTime = WCGArg.SendPeriodTime;
    psReadArg->PressureAlarmHighValue = WCGArg.PressureAlarmHighValue;
    psReadArg->PressureAlarmLowValue = WCGArg.PressureAlarmLowValue;
    CopyDat(psReadArg->DataTime, WCGArg.DataTime, 7);
    /*use pointer maybe storage more 1 byte*/
    //    CopyDat((unsigned char*) psReadArg, (unsigned char *) &WCGArg, sizeof (struct sGlobalWCGArg) - 1);
}

/*************************************
 * Function: vWCGGetCurrentTime
 * Description: get year in wcg arg
 * Input: void 
 * Output: struct tm
 * notice: 
 *************************************/
void vWCGGetCurrentTime(unsigned char* ucCurrentTime) {
    struct tm sCurrentTime;
    unsigned int uiYear;
    static unsigned int uiLastYear = 0xFFFF;
    /*get year in wcg arg*/
    uiYear = HCD(WCGArg.DataTime[0])*100 + HCD(WCGArg.DataTime[1]);
    /*read time*/
    sCurrentTime = sPCF8583ReadTime(&uiYear);
    if ((uiLastYear != 0xFFFF)&&(uiYear != uiLastYear)) {
        WCGArg.DataTime[0] = DCH(uiYear / 100);
        WCGArg.DataTime[1] = DCH(uiYear % 100);
    }
    WCGArg.DataTime[2] = DCH(sCurrentTime.tm_mon + 1);
    WCGArg.DataTime[3] = DCH(sCurrentTime.tm_mday);
    WCGArg.DataTime[4] = DCH(sCurrentTime.tm_hour);
    WCGArg.DataTime[5] = DCH(sCurrentTime.tm_min);
    WCGArg.DataTime[6] = DCH(sCurrentTime.tm_sec);
    CopyDat(ucCurrentTime, WCGArg.DataTime, 7);
    uiLastYear = uiYear;
}

/*************************************
 * Function: bPasswordIsRight
 * Description: check password 
 * Input: pucPassword
 * Output: bool
 * notice: 
 *************************************/
bool bPasswordIsRight(unsigned char * pucPassword) {
    bool bSta = false;

    bSta = ((pucPassword[0] == (EnterSettingPasswd & 0x000F))&&(pucPassword[1] == (EnterSettingPasswd & 0x00F0))&&
            (pucPassword[2] == (EnterSettingPasswd & 0x0F00))&&(pucPassword[3] == (EnterSettingPasswd & 0xF000))) ?
            true : false;
    return bSta;
}

