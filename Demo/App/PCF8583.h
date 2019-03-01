#ifndef PCF8583_H
#define PCF8583_H

#include <p24FJ64GA306.h> 
#include <time.h>
/***************************************************************************
 *Define  
 ***************************************************************************/
#define PCF_ADD                 0xA0
/****************************PCF IIC**************************************/
#define PCF_ERR_W_IC_ADD        0x30    //写IC地址(含操作码)失败
#define PCF_ERR_W_ADD           0x31    //写地址失败
//#define PCF_ERR_W_ADDL          0x32    //写低位地址失败
#define PCF_ERR_W_DATA          0x33    //写数据失败
#define PCF_NO_ERR              0x34    //操作完成
#define PCF_ERR_WR_IC_ADD       0x35    //（读取操作）写IC地址失败
#define PCF_ERR_WR_ADD          0x36    //（读取操作）写地址失败
//#define PCF_ERR_WR_ADDL         0x37    //（读取操作）写低位地址失败
#define PCF_ERR_R_IC_ADD        0x38    //（读取操作）写IC地址失败
#define PCF_ERR_MW_OVERFLOW     0x39    //连续写操作中，数据溢出（>127字节）

/****************************PCF_Set_Time*********************************/
#define PCF_ERR_ST_SET_TIME     0x3A    //PCF设置时钟失败
#define PCF_ERR_ST_SET_STA      0x3B    //PCF设置状态寄存器失败
#define PCF_ERR_ST_READ_STA     0x3C    //PCF读取状态寄存器失败
#define PCF_ERR_ST_SET_STA2     0x3D    //第二次PCF设置状态寄存器失败

/****************************PCF_Read_Time********************************/
#define PCF_ERR_RT_READ_TIME    0x40    //PCF设置时钟失败
#define PCF_ERR_RT_SET_STA      0x41    //PCF设置状态寄存器失败
#define PCF_ERR_RT_READ_STA     0x42    //PCF读取状态寄存器失败
#define PCF_ERR_RT_SET_STA2     0x43    //第二次PCF设置状态寄存器失败

/****************************PCF_Set_Alarm********************************/
#define PCF_ERR_SA_SET_TIME     0x44    //PCF设置报警时间失败

/****************************PCF_Read_Alarm********************************/
#define PCF_ERR_RA_READ_ALARM   0x45    //PCF读取报警时间失败

/****************************PCF_Register********************************/
#define PCF_CON_STA             0x00    //设置控制和状态
#define PCF_T_SEC_100           0x01    //设置计时器的秒/100
#define PCF_T_SEC               0x02    //设置计时器的秒
#define PCF_T_MIN               0x03    //设置计时器的分
#define PCF_T_HOUR              0x04    //设置计时器的时
#define PCF_T_DAY               0x05    //设置计时器的天
#define PCF_T_MONTH             0x06    //设置计时器的月
#define PCF_CON_ALARM           0x08    //设置报警器
#define PCF_A_SEC_100           0x09    //设置报警器的秒/100
#define PCF_A_SEC               0x0A    //设置报警器的秒
#define PCF_A_MIN               0x0B    //设置报警器的分
#define PCF_A_HOUR              0x0C    //设置报警器的时
#define PCF_A_DAY               0x0D    //设置报警器的天
#define PCF_A_MONTH             0x0E    //设置报警器的月
#define PCF_INIT_VALUE          0b11000100 //read date and month count directly
#define PCF_START_VALUE         0b00000100
#define PCF_ALARM_VALUE         0b10010000
#define PCF_D0_STOP_COUNT       (1<<7)
#define PCF_D0_HOLD_LAST_COUNT  (1<<6)
#define PCF_D0_ALARM_EN         (1<<2)
#define PCF_D0_AlARM_FLAG       (1<<1)

/*setting IO*/
#define ReadPCFINT      PORTBbits.RB13 
#define SetPCFINT0Tris  _TRISB13


/*local time zone,like chinese is earst 8 time zone*/
#define TIME_ZONE       28800  

extern volatile time_t tNowTimestamp;

/*PCF8583 Initialization*/
extern void vPCF8583Init(unsigned char*);
/*set time by struct tm*/
extern void vPCF8583SetTime(struct tm);
/*set time by timestamp*/
extern void vPCF8583SetTimeByTimestamp(time_t* ultimestamp);
/*read timestamp type of struct tm*/
extern struct tm sPCF8583ReadTime(unsigned int*);
/*read timestamp type of time_t*/
extern time_t tPCF8583ReadTime(unsigned int*);
/*set alarm time*/
extern void vPCF8583SetAlarmTime(struct tm alarmtime);
/*set register*/
extern void vPCF8583WriteRegister(unsigned char ucRegisterAddress, unsigned char ucRegisterContext);
/*read register*/
extern unsigned char ucPCF8583ReadRegister(unsigned char ucRegisterAddress);
/*set alarm*/
extern void vPCF8583SetAlarmTime(struct tm tAlarmTime);
/*set alarm*/
extern void vPCF8583SetAlarmTimeByTimestamp(time_t *tSetAlarmTimestamp);
#endif

