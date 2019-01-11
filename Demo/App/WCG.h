#ifndef WCG_H
#define WCG_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "HL6528.h"
#include "Debug.h"
#include "Common.h"
#include "CRC16.h"
#include "CAT24C512.h"


#define  BAT_TEST_DIR TRISBbits.TRISB11
#define  BAT_TEST_LAT LATBbits.LATB11
#define  BAT_TEST_PORT PORTBbits.RB11
#define GETTIME 10

typedef struct tagWCGTIME0BITS {
    uint16_t year : 8;
    uint16_t month : 8;
} WCGTIME0BITS;
extern volatile WCGTIME0BITS WCGTIME0bits;

typedef struct tagWCGTIME1BITS {
    uint16_t day : 8;
    uint16_t hour : 8;
} WCGTIME1BITS;
extern volatile WCGTIME1BITS WCGTIME1bits;

typedef struct tagWCGTIME2BITS {
    uint16_t min : 8;
    uint16_t sec : 8;
} WCGTIME2BITS;
extern volatile WCGTIME2BITS WCGTIME2bits;

//typedef struct tagWCGTIME3BITS {
//    uint16_t sendtime : 8;
//    uint16_t sampletime : 8;
//} WCGTIME3BITS;
//extern volatile WCGTIME3BITS WCGTIME3bits;

typedef struct tagWCGCON0BITS {
    uint16_t Send_60s : 11; //����ʱ��,��λ������ 2^15=32768 
    uint16_t None : 5; //δ����
} WCGCON0BITS;
extern volatile WCGCON0BITS WCGCON0bits;

typedef struct tagWCGCON1BITS {
    uint16_t Sample_5s : 15; //�ɼ�ʱ��,��λ���� �̶�5s
    uint16_t TestGPRSShow : 1; //��ʾGPRS���߹���    
} WCGCON1BITS;
extern volatile WCGCON1BITS WCGCON1bits;

typedef struct tagWCGCON2BITS {
    uint16_t WCG_ID : 8; //WCG��ID�� 0-255
    uint16_t TestGPRSBy485 : 1; //�̳������Ƿ�������������    
    uint16_t Debug1 : 1; //�̳������Ƿ������޸Ĳ���    
    uint16_t Debug2 : 1; //����ʱ����Բɼ�ʱ���Ƿ�������
    uint16_t Period_FLAG : 1; //rtcc��־λ
    uint16_t Sample_FLAG : 1; //������־λ
    uint16_t Send_FLAG : 1; //���ͱ�־λ
    uint16_t SET_TIME_FLAG : 1; //RTCC��ʱʱ�����
    uint16_t PC_Cop_FLAG : 1; //�û�ͨѶ��־λ
} WCGCON2BITS;
extern volatile WCGCON2BITS WCGCON2bits;

typedef struct tagWCGCON3BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
} WCGCON3BITS;
extern volatile WCGCON3BITS WCGCON3bits;

typedef struct tagWCGCON4BITS {
    uint32_t delay : 17; //0-131071s;
    uint32_t count : 15; //0-32767 �� �ɼ�ʱ�����Ϊ17280 ����ʱ�����Ϊ480 һ��֮��
} WCGCON4BITS;
extern volatile WCGCON4BITS WCGCON4bits;

typedef struct tagWCGIPBITS {
    uint32_t IP3 : 8; //IP��ַ��3λ
    uint32_t IP2 : 8; //IP��ַ��2λ
    uint32_t IP1 : 8; //IP��ַ��1λ
    uint32_t IP0 : 8; //IP��ַ��0λ
} WCGIPBITS;
extern volatile WCGIPBITS WCGIPbits;

typedef struct tagWCGCNTBITS {
    uint32_t Sample_CNT : 16;
    uint32_t Send_CNT : 16;
} WCGCNTBITS;
extern volatile WCGCNTBITS WCGCNTbits;
//typedef struct tagWCGPORTBITS {
//    uint16_t HighAddr : 8; //��λ��ַ
//    uint16_t LowAddr : 8; //��λ��ַ
//} WCGPORTBITS;
extern volatile uint16_t WCGPORT;

//typedef struct tagWCGPERIODBITS {
//    uint16_t B1; //���ڱ���
//    uint16_t Y2; //�������� 
//    uint16_t CNT; //����ѭ������ 
//    //    uint16_t RST_FLAG : 1; //���¼������ڱ�־
//} WCGPERIODBITS;
//extern volatile WCGPERIODBITS WCGPeriodbits;

typedef enum {
    Send_Flag, GPRS_Dingling, GPRS_Online, GPRS_Underline, GPRS_Senddata, GPRS_Receivedata, GPRS_Err,
    Sample_Flag, Sample_Data, Sample_Err, Sample_Send_Flag,
    E41_Senddata, E41_Receivedata, E41_Error,
    eerom_Writedata, eerom_Readdata, eerom_Writeerr, eerom_Readerr,
    LCD_Senderr
} WCG_STA;



//enum {
//    DATA, SENDTIME, SAMPLETIME, ID, IP, PORT
//};
//extern volatile struct RTCC_Time_Node rtcc_sample;
//extern volatile struct RTCC_Time_Node rtcc_send;
extern volatile uint8_t WCG_Sta;
extern float f_p;

extern void WCG_Init(void);
//extern bool WCG_CalcAlarmPeriod(void);
extern void GPRS_Task(uint8_t);
extern bool Sample_Task(void);
extern void SetNextAlarm(uint32_t sample_sec);
extern bool WCGPCCop(void);
#endif


