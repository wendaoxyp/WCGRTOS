/*
 * File:   WCGDebug.c
 * Author: root
 *
 * Created on January 11, 2019, 10:14 AM
 */
#include "Debug.h"
#include "FreeRTOS.h"
#include "task.h"
#include "WCGDeBug.h"
#include <xc.h>

/*set all control debug*/
#if (ENABLE_DEBUG == 1)

/*debug LCD*/
#if (DebugLCD == 1)
#include "LCD.h"

void vTaskTestLCD(void*parameter) {
    uint8_t ucCnt, ucCnt1;
    /*Initialization LCD*/
    vLCDInit();
    /*use rs485*/
    _LATE6 = 1;

    for (;;) {
#if (TestSpecialSign == 1)
        /*print information*/
        vDeBugPrintInformation("test special sign");
        /*clear screen*/
        vLCDClearScreen();
        /*delay*/
        vTaskDelay(1000);
        /*show external power*/
        vLCDShowPoint(ePower, SEGSHOW);
        /*show error*/
        vLCDShowPoint(eError, SEGSHOW);
        /*show forword*/
        vLCDShowPoint(eForword, SEGSHOW);
        /*show backword*/
        vLCDShowPoint(eBackword, SEGSHOW);
        /*show kPa*/
        vLCDShowPoint(eKPa, SEGSHOW);
        /*show m3*/
        vLCDShowPoint(em3, SEGSHOW);
        /*show per hour*/
        vLCDShowPoint(ePerh, SEGSHOW);
        /*show temperature unit*/
        vLCDShowPoint(eCC, SEGSHOW);
        /*show battery power*/
        for (ucCnt = 0; ucCnt < 4; ucCnt++)
            vLCDShowBattery(ucCnt);
        /*show GPRS signal*/
        for (ucCnt = 0; ucCnt < 5; ucCnt++)
            vLCDShowGPRSSign(ucCnt);
        /*endif (TestSpecialSign == 1)*/
#endif
#if (TestNum == 1)
        /*show digital point*/
        for (ucCnt = 0; ucCnt < 5; ucCnt++)
            vLCDShowDigitalPoint(ucCnt);
        /*show one position nums*/
        for (ucCnt1 = 0; ucCnt1 < 7; ucCnt1++) {
            for (ucCnt = 0; ucCnt < 10; ucCnt++) {
                vLCDShowNum(ucCnt, ucCnt1);
                vTaskDelay(200);
            }
        }
        /*shou all zero*/
        vLCDShowNums(0L, FristZeroShow);
        vTaskDelay(1000);
        /*show one zero*/
        vLCDShowNums(0L, FristZeroHide);
        vTaskDelay(1000);
        /*show 1234567*/
        vLCDShowNums(1234567L, FristZeroShow);
        vTaskDelay(1000);
        /*show 123*/
        vLCDShowNums(123L, FristZeroHide);
        vTaskDelay(1000);
        /*override test*/
        vLCDShowNums(10000000L, FristZeroShow);
        vTaskDelay(1000);
        /*show  111111*/
        vLCDShowNums(1111111L, FristZeroShow);
        vTaskDelay(1000);
        /*endif(TestNum == 1)*/
#endif
    }
}
/*endif (DebugLCD==1)*/
#endif

#if  (DebugPCF8583 == 1)
#include "PCF8583.h"
#include "FreeRTOS.h"
#include "semphr.h"

SemaphoreHandle_t xSemBinaryAlarm;

void vTaskTestPCF(void*parameter) {
    /*Initialization PCF8583*/
    vPCF8583Init();
    /*use rs485*/
    _LATE6 = 1;
    struct tm sReadTime;
    time_t tReadTimestamp;
    time_t tSetAlarmTimestamp;

    /*set clock time*/
    vPCF8583SetTimeByTimestamp((time_t*) & tNowTimestamp);
    /*set alrarm ttime*/
    tSetAlarmTimestamp = tNowTimestamp + 10;
    vPCF8583SetAlarmTimeByTimestamp(&tSetAlarmTimestamp);
    /*create semaphorebinary*/
    xSemBinaryAlarm = xSemaphoreCreateBinary();
    for (;;) {
#if (TestReadTime == 1)
        /**test  read time**/
        sReadTime = sPCF8583ReadTime();
        vDeBugPrintStringAndNums("year is ", sReadTime.tm_year);
        vDeBugPrintStringAndNums("month is ", sReadTime.tm_mon);
        vDeBugPrintStringAndNums("mday is ", sReadTime.tm_mday);
        vDeBugPrintStringAndNums("hour is ", sReadTime.tm_hour);
        vDeBugPrintStringAndNums("minute is ", sReadTime.tm_min);
        vDeBugPrintStringAndNums("second is ", sReadTime.tm_sec);
        vTaskDelay(1000);
        /*endif (TestReadTime == 1)*/
#endif
#if (TestReadTimestamp == 1)
        /*test write and read time by timestamp*/
        vDeBugPrintInformation("test PCF8583  read time (timestame)\r\n");
        tReadTimestamp = tPCF8583ReadTime();
        vDeBugPrintStringAndNums("\r\ntimestamp high is ", (unsigned int) (tReadTimestamp >> 16));
        vDeBugPrintStringAndNums("\r\ntimestamp low is ", (unsigned int) tReadTimestamp);
        vDeBugPrintInformation("\r\n");
        vTaskDelay(1000);
        /*endif(TestReadTimestamp == 1)*/
#endif
#if (TestAlarm == 1)
        /*test set alarm by set time*/
        vDeBugPrintInformation("test PCF8583  Alarm time \r\n");
        if (xSemaphoreTake(xSemBinaryAlarm, 0)) {
            /*clear alarm flag*/
            vPCF8583WriteRegister(PCF_CON_STA, PCF_START_VALUE);
            /*calculate new alarm time*/
            tSetAlarmTimestamp += 10;
            vPCF8583SetAlarmTimeByTimestamp(&tSetAlarmTimestamp);
            vDeBugPrintStringAndNums("tSetAlarmTimestamp is ", (unsigned int) tSetAlarmTimestamp);
            vDeBugPrintStringAndNums("tNowTimestamp is ", (unsigned int) tNowTimestamp);
            vTaskDelay(1000);
        }
        /*endif (TestAlarm == 1)*/
#endif
#if (TestWriteReadRegister == 1)
        /**test write read register**/
        vDeBugPrintStringAndNums("PCF_CON_STA is ", HCD(ucPCF8583ReadRegister(PCF_CON_STA)));
        vDeBugPrintStringAndNums("PCF_CON_ALARM is ", HCD(ucPCF8583ReadRegister(PCF_CON_ALARM)));
        vDeBugPrintStringAndNums("PCF_A_SEC_100 is ", HCD(ucPCF8583ReadRegister(PCF_A_SEC_100)));
        vDeBugPrintStringAndNums("PCF_A_SEC is ", HCD(ucPCF8583ReadRegister(PCF_A_SEC)));
        vDeBugPrintStringAndNums("PCF_A_MIN is ", HCD(ucPCF8583ReadRegister(PCF_A_MIN)));
        vDeBugPrintStringAndNums("PCF_A_HOUR is ", HCD(ucPCF8583ReadRegister(PCF_A_HOUR)));
        vDeBugPrintStringAndNums("PCF_A_DAY is ", HCD(ucPCF8583ReadRegister(PCF_A_DAY)));
        vDeBugPrintStringAndNums("PCF_A_MONTH is ", HCD(ucPCF8583ReadRegister(PCF_A_MONTH)));
        vDeBugPrintStringAndNums("PCF_T_SEC_100 is ", HCD(ucPCF8583ReadRegister(PCF_T_SEC_100)));
        vDeBugPrintStringAndNums("PCF_T_SEC is ", HCD(ucPCF8583ReadRegister(PCF_T_SEC)));
        vDeBugPrintStringAndNums("PCF_T_MIN is ", HCD(ucPCF8583ReadRegister(PCF_T_MIN)));
        vDeBugPrintStringAndNums("PCF_T_HOUR is ", HCD(ucPCF8583ReadRegister(PCF_T_HOUR)&0x3F));
        vDeBugPrintStringAndNums("PCF_T_DAY is ", HCD(ucPCF8583ReadRegister(PCF_T_DAY)&0x3F));
        vDeBugPrintStringAndNums("PCF_T_MONTH is ", HCD(ucPCF8583ReadRegister(PCF_T_MONTH)&0x3F));
        vTaskDelay(1000);
        /*endif (TestWriteReadRegister == 1)*/
#endif
    }
}
/*end (DebugPCF8583 == 1)*/
#endif 

#if (DebugCAT24C512 == 1)
#include "CAT24C512.h"
#include <string.h>

/*define test cat24C512 function*/
void vTaskTestCAT(void* parameter) {
    unsigned char ucWriteArray[10], ucReadArray[10];
    unsigned char ucCnt;

    _LATE6 = 1;
    memset(ucReadArray, 10, 0);
    memcpy(ucWriteArray, "1234567890", 10);
    /*initialize CAT24C512,maybe initialize I2C_S*/
    vCAT24Init();

    for (;;) {
#if  (TestReadByte == 1)
        /*write 1 byte*/
        xCAT24WriteByte(0x0000, ucWriteArray[0]);
        vDeBugPrintStringAndNums("test write byte is ", ucWriteArray[0]);
        vTaskDelay(1000);
        /*read 1 byte*/
        ucReadArray[0] = 0xaa;
        xCAT24ReadByte(0x0000, ucReadArray[0]);
        vDeBugPrintStringAndNums("test read byte is ", ucReadArray[0]);
        /*delay*/
        vTaskDelay(1000);
        /*endif(TestReadByte == 1)*/
#endif
#if (TestReadBytes == 1)
        /*write bytes*/
        vDeBugPrintInformation("test Init readarry :");
        xCAT24WriteBytes(0x000A, ucWriteArray, sizeof (ucWriteArray));
        /*print array of read*/
        memset(ucReadArray, 0xa, sizeof (ucReadArray));
        for (ucCnt = 0; ucCnt<sizeof (ucReadArray); ucCnt++) {
            vDeBugPrintStringAndNums("\t\t", ucReadArray[ucCnt]);
        }
        vTaskDelay(1000);
        /*read bytes*/
        vDeBugPrintInformation("test read bytes :");
        xCAT24ReadBytes(0x000A, ucReadArray, sizeof (ucReadArray));
        /*print array of read*/
        for (ucCnt = 0; ucCnt<sizeof (ucReadArray); ucCnt++) {
            vDeBugPrintStringAndNums("\t\t", ucReadArray[ucCnt]);
        }
        vTaskDelay(1000);
        /*endif (TestReadBytes == 1)*/
#endif  
    }
}
/*endif (DebugCAT24C512==1)*/
#endif 
/*endif ENABLE_DEBUG==1*/
#endif 




#define tskDebugPCFStack  256
#define tskDebugPCFPriority 4 

void vDebugTaskHook(void) {
#if (DebugLCD == 1)
    /*Create Test LCD task*/
    xTaskCreate(vTaskTestLCD, "debug LCD", tskDebugPCFStack, NULL, tskDebugPCFPriority, NULL);
    /*endif (DebugLCD==1)*/
#endif 
#if (DebugPCF8583 == 1)
    /*Create Test PCF8583 task*/
    xTaskCreate(vTaskTestPCF, "debug PCF", tskDebugPCFStack, NULL, tskDebugPCFPriority, NULL);
    /*endif (DebugPCF8583==1)*/
#endif
#if (DebugCAT24C512 == 1)
    /*Create Test CAT24C512 task*/
    xTaskCreate(vTaskTestCAT, "debug CAT", tskDebugPCFStack, NULL, tskDebugPCFPriority, NULL);
    /*endif (DebugCAT24C512 == 1)*/
#endif
}


