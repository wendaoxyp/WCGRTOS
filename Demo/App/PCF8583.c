#include "PCF8583.h"
#include "I2C_S.h"
#include "Common.h"
#include "INT.h"


static sI2CDeviceAttribute sPCF8583;

/*time around 2019 1 1 0:0:0 UTC*/
volatile time_t tNowTimestamp = 1546272000; //every 24hour once upgrade 

/*************************************
Function: vPCF8583Init 
Description: set INT0
Input: void
Output: void
 *************************************/
void vPCF8583Init(void) {
#ifndef Have_Initialized_I2C
    vI2CInit();
#define Have_Initialized_I2C
#endif 
    INT0_Init();
    SetPCFINT0Tris = 1; //外部RTCC闹钟中断设置为输入 INT0
    /*set PCF8583 time*/
    vPCF8583SetTimeByTimestamp((time_t*) & tNowTimestamp);
}

/*************************************
Function: vPCF8583SetTime
Description: Set PCF Register to real time
Input: stimes 
Output: void
 * ep: 
 *  setarg = PCF_INIT_VALUE;
    PCF8583_Write(PCF_CON_STA, &setarg, 1); //初始化状态控制器0x00    
    PCF_Set_Time(settime); //设置时钟时间
    setarg = PCF_ALARM_VALUE;
    PCF8583_Write(PCF_CON_ALARM, &setarg, 1); //初始化报警控制器0x08
    PCF_Set_Alarm(settime, 0); //设置报警时间
 *************************************/
void vPCF8583SetTime(struct tm stimes) {
    /*Set 00h equal 0x85*/
    unsigned char ucTmp[15];
    /*set control status register*/
    vPCF8583WriteRegister(PCF_CON_STA, PCF_INIT_VALUE);
    /*set 1/100s */
    ucTmp[PCF_T_SEC_100] = 0x00;
    /*set seconds BCD*/
    ucTmp[PCF_T_SEC] = DCH(stimes.tm_sec);
    /*set minutes */
    ucTmp[PCF_T_MIN] = DCH(stimes.tm_min);
    /*set hour :format[7];am,pm[6];ten hour[4:5];unit hour[0:3]*/
    ucTmp[PCF_T_HOUR] = (DCH(stimes.tm_hour) & 0x3F); //24hour
    /*set year and day:year[6:7];ten day[4:5];unit day[0-3]*/
    ucTmp[PCF_T_DAY] = (GetMod(stimes.tm_year, 2) << 6) + (DCH(stimes.tm_mday) & 0x3F);
    /*set weekday and month:weekday[5:7;ten months[4];unit months[0-3] */
    ucTmp[PCF_T_MONTH] = (DCH(stimes.tm_wday) << 5) + (DCH(stimes.tm_mon + 1) & 0x1F); //注意tm结构的数据，1月份表示0
    /*设置定时器*/
    ucTmp[7] = 0;
    /*设置报警控制器*/
    ucTmp[PCF_CON_ALARM] = PCF_ALARM_VALUE; //0x90;
    /*报警百分秒*/
    ucTmp[PCF_A_SEC_100] = 00;
    /*报警秒*/
    ucTmp[PCF_A_SEC] = 4; //GetMod(alarmtime, 30); 
    /*报警分钟*/
    ucTmp[PCF_A_MIN] = 0; //GetMod(alarmtime / 30, 60); 
    /*报警小时*/
    ucTmp[PCF_A_HOUR] = 0; //GetMod(alarmtime / 1800, 60); 
    /*报警日期和月份*/
    ucTmp[PCF_A_DAY] = ucTmp[PCF_A_MONTH] = 0;

    /*set PCF8583 atrribute*/
    sPCF8583.ucSlaveAddress = PCF_ADD;
    sPCF8583.usRegisterAddress = PCF_T_SEC_100;
    sPCF8583.bIs16BitDevice = false;
    sPCF8583.ucNeedDataBytes = PCF_A_MONTH - PCF_T_SEC_100 + 1;
    sPCF8583.pucNeedData = ucTmp + PCF_T_SEC_100;

    /*write register*/
    bI2CWriteSlave(&sPCF8583);
    /*start count*/
    vPCF8583WriteRegister(PCF_CON_STA, PCF_START_VALUE);
    /*if use rtos,enable tick interrupt*/
}

/*************************************
Function: vPCF8583SetTimeByTimestamp
Description: set real time by timestamp
Input: ultimestamp
Output: void
 * notice:时间戳单位是1s，报警时间单位是2s
 *************************************/
void vPCF8583SetTimeByTimestamp(time_t* ultimestamp) {
    struct tm stime_tmp;
#ifdef TIME_ZONE
    *ultimestamp += TIME_ZONE;
#endif
    /*timestamp convert stuct tm*/
    stime_tmp = *gmtime((time_t*) ultimestamp);
    /*set real time*/
    vPCF8583SetTime(stime_tmp);
}

/*************************************
Function: sPCF8583ReadTime
Description: read real time ,output struct tm tpye varialbe
Input: data 
Output: is finish complete 
 *************************************/
struct tm sPCF8583ReadTime(void) {
    struct tm sReadTime;
    unsigned char ucTmp[7] = {0, 0, 0, 0, 0, 0, 0};
    /*set PCF atrribute*/
    sPCF8583.ucSlaveAddress = PCF_ADD;
    sPCF8583.usRegisterAddress = PCF_CON_STA;
    sPCF8583.bIs16BitDevice = false;
    sPCF8583.ucNeedDataBytes = 7;
    sPCF8583.pucNeedData = ucTmp;

    /*read PCF8583 register*/
    bI2CReadSlave(&sPCF8583);

    /*get second*/
    sReadTime.tm_sec = HCD(ucTmp[PCF_T_SEC]);
    /*get min*/
    sReadTime.tm_min = HCD(ucTmp[PCF_T_MIN]);
    /*get hour*/
    sReadTime.tm_hour = HCD(ucTmp[PCF_T_HOUR]&0x3F);
    /*get day*/
    sReadTime.tm_mday = HCD(ucTmp[PCF_T_DAY]&0x3F);
    /*get month*/
    sReadTime.tm_mon = HCD(ucTmp[PCF_T_MONTH]&0x1F) - 1;
    /*get year 注意是否需要更新年份见2016这个变量放入E2ROM*/
    sReadTime.tm_year = ucTmp[PCF_T_DAY] >> 6;
    return sReadTime;
}

/*************************************
Function: tPCF8583ReadTime 
Description: read real time
Input: void  
Output: time_t
 *************************************/
time_t tPCF8583ReadTime(void) {
    struct tm sReadTime, sNowTime;
    time_t tReadTime;
    /*read real time ,output struct time type*/
    sReadTime = sPCF8583ReadTime();
    sReadTime.tm_yday = 0;
    sReadTime.tm_wday = 0;
    sReadTime.tm_isdst = 0;
    /*get time struct*/
    sNowTime = *gmtime((time_t *) & tNowTimestamp);
    /*claculate year*/
    sReadTime.tm_year = sNowTime.tm_year; //OffsetYear;
    /*struct time to timeStampe*/
    tReadTime = mktime(&sReadTime);
    Nop();
    return tReadTime;
}

/*************************************
Function: vPCF8583SetAlarmTime
Description: Set alarm
Input: sAlarmTime
Output: void
 *************************************/
void vPCF8583SetAlarmTime(struct tm sAlarmTime) {
    unsigned char ucTemp[6];
    unsigned char ucOffset;

    /*Calc offset*/
    ucOffset = 0;
    /*set alarm 10ms*/
    ucTemp[ucOffset++] = 0;
    /*set alarm seconds 报警秒*/
    ucTemp[ucOffset++] = DCH(sAlarmTime.tm_sec);
    /*set alarm minute 报警分钟*/
    ucTemp[ucOffset++] = DCH(sAlarmTime.tm_min);
    /*set alarm hour 报警小时*/
    ucTemp[ucOffset++] = DCH(sAlarmTime.tm_hour);
    /*set alarm day and month 报警日期和月份*/
    ucTemp[ucOffset++] = 0;
    ucTemp[ucOffset] = 0;

    sPCF8583.ucSlaveAddress = PCF_ADD;
    sPCF8583.usRegisterAddress = PCF_A_SEC_100;
    sPCF8583.bIs16BitDevice = false;
    sPCF8583.pucNeedData = ucTemp;
    sPCF8583.ucNeedDataBytes = 6;
    /*set alarm time*/
    bI2CWriteSlave(&sPCF8583);
    /*for test*/
    Nop();
}

/*************************************
Function: vPCF8583SetAlarmTimeByTimestamp
Description: set alarm by timestamp
Input: tSetAlarmTimestamp
Output: void 
 *************************************/
void vPCF8583SetAlarmTimeByTimestamp(time_t *tSetAlarmTimestamp) {
    struct tm sSetTime;

    /*get time struct*/
    sSetTime = *gmtime(tSetAlarmTimestamp);
    /*set alarm time*/
    vPCF8583SetAlarmTime(sSetTime);
}

/*************************************
Function: vPCF8583WriteRegister 
Description: Write data to I2C device
Input: data 
Output: is finish complete 
 *************************************/
void vPCF8583WriteRegister(unsigned char ucRegisterAddress, unsigned char ucRegisterContext) {//包含
    unsigned char ucControlStatusRegister = ucRegisterContext;

    /*set PCF8583 attribute*/
    sPCF8583.ucSlaveAddress = PCF_ADD;
    sPCF8583.usRegisterAddress = ucRegisterAddress;
    sPCF8583.bIs16BitDevice = false;
    sPCF8583.ucNeedDataBytes = 1;
    sPCF8583.pucNeedData = &ucControlStatusRegister;
    /*read PCF8583 register*/
    bI2CWriteSlave(&sPCF8583);
}

/*************************************
Function: vPCF8583ReadStatus 
Description: read data to I2C device
Input: ucRegisterAddress 
Output: register data
 *************************************/
unsigned char ucPCF8583ReadRegister(unsigned char ucRegisterAddress) {
    unsigned char ucControlStatusRegister;

    /*set PCF8585 attribute*/
    sPCF8583.ucSlaveAddress = PCF_ADD;
    sPCF8583.usRegisterAddress = ucRegisterAddress;
    sPCF8583.bIs16BitDevice = false;
    sPCF8583.ucNeedDataBytes = 1;
    sPCF8583.pucNeedData = &ucControlStatusRegister;
    /*read PCF8583 register*/
    bI2CReadSlave(&sPCF8583);
    return ucControlStatusRegister;
}


