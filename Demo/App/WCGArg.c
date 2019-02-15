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


/*pressure production protocal*/
extern const unsigned char TR04[8];

union sConfigbit {
    unsigned char SampleMode : 2;
    unsigned char SendMode : 2;
    unsigned char None : 4;
};

struct sGlobalWCGArg {
    unsigned char IP[4];
    unsigned int Port;
    union sConfigbit Configbit1;
    unsigned char SampleSetTime[3];
    unsigned int SamplePeriodTime;
    unsigned char SendSetTime[3];
    unsigned int SendPeriodTime;
    float PressureAlarmHighValue;
    float PressureAlarmLowValue;
    unsigned char DataTime[7];
};
static struct sGlobalWCGArg WCGArg = {
    {192, 168, 1, 55},
    5055,
    {0},
    {12, 12, 10}, 10,
    {14, 10, 0}, 30,
    0.0,
    0.0,
    {20, 10, 9, 17, 8, 12, 30},
};

void vArgShowInLCD(void *ScreenID) {
    unsigned char ucScreenID = *((unsigned char*) ScreenID);
    struct tm tTimes;

    //    vLCDClearScreen();
    switch (ucScreenID) {
        case eMainPage1:
        {
            tTimes = sPCF8583ReadTime();
            sLCDArg.sLCDArg1.num0 = tTimes.tm_sec & 0x0f;
            sLCDArg.sLCDArg1.num1 = tTimes.tm_sec >> 4;
            sLCDArg.sLCDArg1.num2 = tTimes.tm_min & 0x0f;
            sLCDArg.sLCDArg1.num3 = tTimes.tm_min >> 4;
            sLCDArg.sLCDArg1.num4 = tTimes.tm_hour & 0x0f;
            sLCDArg.sLCDArg1.num5 = tTimes.tm_hour >> 4;
            sLCDArg.sLCDArg1.num6 = NUMHIDE;
            break;
        }
        case eMainPage2:
        {
            tTimes = sPCF8583ReadTime();
            sLCDArg.sLCDArg1.num0 = tTimes.tm_yday & 0x0f;
            sLCDArg.sLCDArg1.num1 = tTimes.tm_yday >> 4;
            sLCDArg.sLCDArg1.num2 = tTimes.tm_mon & 0x0f;
            sLCDArg.sLCDArg1.num3 = tTimes.tm_mon >> 4;
            sLCDArg.sLCDArg1.num4 = tTimes.tm_year & 0x0f;
            sLCDArg.sLCDArg1.num5 = tTimes.tm_year >> 4;
            sLCDArg.sLCDArg1.num6 = NUMHIDE;
            break;
        }
        case eMainPage3:
        {
            /*must open vTaskGetPressure task*/
            //            vUART1Send((unsigned char*) TR04, sizeof (TR04));
            //            /*wait for get pressure*/
            //            sLCDArg.sLCDArg1.num0 = tTimes.tm_yday & 0x0f;
            //            sLCDArg.sLCDArg1.num1 = tTimes.tm_yday >> 4;
            //            sLCDArg.sLCDArg1.num2 = tTimes.tm_mon & 0x0f;
            //            sLCDArg.sLCDArg1.num3 = tTimes.tm_mon >> 4;
            //            sLCDArg.sLCDArg1.num4 = tTimes.tm_year & 0x0f;
            //            sLCDArg.sLCDArg1.num5 = tTimes.tm_year >> 4;
            //            sLCDArg.sLCDArg1.num6 = NUMHIDE;
            break;
        }
        case ePasswordPage:
        {
            sLCDArg.sLCDArg1.num0 = 0;
            sLCDArg.sLCDArg1.num1 = 0;
            sLCDArg.sLCDArg1.num2 = 0;
            sLCDArg.sLCDArg1.num3 = 0;
            sLCDArg.sLCDArg1.num4 = NUMHIDE;
            sLCDArg.sLCDArg1.num5 = NUMHIDE;
            sLCDArg.sLCDArg1.num6 = NUMHIDE;
            break;
        }
        case eSetPage1:
        {
            sLCDArg.sLCDArg1.num0 = WCGArg.IP[1] % 10;
            sLCDArg.sLCDArg1.num1 = WCGArg.IP[1] / 10 % 10;
            sLCDArg.sLCDArg1.num2 = WCGArg.IP[0] / 100 % 10;
            sLCDArg.sLCDArg1.num3 = WCGArg.IP[0] % 10;
            sLCDArg.sLCDArg1.num4 = WCGArg.IP[0] / 10 % 10;
            sLCDArg.sLCDArg1.num5 = WCGArg.IP[0] / 100;
            sLCDArg.sLCDArg1.num6 = NUMHIDE;
            sLCDArg.sLCDArg2.Point = 3;
            break;
        }
        case eSetPage2:

            break;
        case eSetPage3:

            break;
        case eSetPage4:

            break;
        case eSetPage5:

            break;
        case eSetPage6:

            break;
        case eSetPage7:

            break;
        case eSetPage8:

            break;
        case eSetPage9:

            break;
            /*  other page 
            case SetPage10:
                break;
             */
    }
    //    vLCDShowNums();
}



