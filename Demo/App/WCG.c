#include "WCG.h"
//#include <time.h>

#define TIMEOFFSET 1483200000
const uint8_t WCG[] = "WCG";
#define TimeRegAdd 0x00
#define GPRSRegAdd 0x06
#define IDRegAdd 0x08
#define IPRegAdd 0x09
#define PortRegAdd 0x0d
//#define TimeRegAdd 0x00
const uint8_t RegAdd[] = {0x00, 0x06, 0x08, 0x0a, 0x0b, 0x0f, 0x11};
//const uint8_t RegNum[] = {0x06, 0x01, 0x01, 0x01, 0x04, 0x02};

//enum {Jan=31,Feb=30,Mar=31,Apr=30,May=31,Jun=30,Jul=31,Aug=31,Sep=30,Oct=31,Nov=30,Dec=31};
//const uint8_t Month[12] = {31, 30, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const uint8_t GetPressureInt[] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xD4}; //��ȡѹ����ָ��
volatile WCGTIME0BITS WCGTIME0bits;
volatile WCGTIME1BITS WCGTIME1bits;
volatile WCGTIME2BITS WCGTIME2bits;
volatile WCGCON0BITS WCGCON0bits;
volatile WCGCON1BITS WCGCON1bits;
volatile WCGCON2BITS WCGCON2bits;
volatile WCGCON3BITS WCGCON3bits;
volatile WCGCON4BITS WCGCON4bits;
volatile WCGIPBITS WCGIPbits;
volatile WCGCNTBITS WCGCNTbits;
volatile uint16_t WCGPORT;
//volatile WCGPERIODBITS WCGPeriodbits;
volatile uint8_t WCG_Sta = 1;
float f_p;
//struct RTCC_Time_Node RT_node;

//static volatile struct RTCC_Time_Node rtcc_sample;
//static volatile struct RTCC_Time_Node rtcc_send;
static uint16_t gCatWriteAdd; //д������ַ
static uint16_t gCatCanReadAdd; //��ʼ��ȡ�ĵ�ַ
static uint16_t gCatCanReadNum; //��ȡ�����ݵĳ���

//static uint8_t MKSendString(uint8_t* tmp);
static uint8_t HandleArg(uint8_t funcode, uint8_t regadd, uint8_t *arg);
static void RefreshReg(void);

void WCG_Init(void) {
    WCGIPbits.IP3 = 183; //����IP��ַ
    WCGIPbits.IP2 = 246;
    WCGIPbits.IP1 = 74;
    WCGIPbits.IP0 = 68;
    WCGPORT = 5070; //���ö˿ں�
    WCGCON0bits.Send_60s = 1440; //����2���� mark1
    WCGCON1bits.Sample_5s = 60; //�ɼ�5��
    WCGCON2bits.TestGPRSBy485 = 0; //�ر�E41
    WCGCON2bits.Debug1 = WCGCON2bits.Debug2 = 0; //�ر�E41
    WCGCON2bits.WCG_ID = 0x03; //ID��
    //    RTCC_TIME_Init(); //��ʼ��RTCC_TIME���ݽṹ
    WCGCON2bits.Period_FLAG = 1; //��ʼ����ʼ����ʱ��
    //    WCGPeriodbits.CNT = 0;
    //    WCGCON2bits.Alarm_RST_FLAG = 0; //�ϵ�����¼���
}

//static void GetPressure(void) {
//    
//}

//bool WCG_CalcAlarmPeriod(void) {//�����´α���ʱ��
//    struct tm now_time1, now_time2;
//    uint32_t time1;
//    //��ȡ��ǰ��ʱ�䣬Ȼ�������ʱ��Ļ����ϼ�������
//    while (!RTC_Read_Time(&now_time1)); //�ݴ����
//    //    while (!RTC_Read_Time(&now_time1)); //�ݴ����
//    time1 = mktime(&now_time1);
//    time1 += 10;
//    now_time2 = *gmtime(&time1);
//
//    RTC_Set_Alarm(now_time1);
//}

void GetTimeByNet(uint8_t *tmp1, uint8_t getbytes) {
    time_t gmt = 0;
    struct tm timeptr;
    struct tm* timeptr1;
    uint8_t getop = 0; //ʱ��ͨѶ
    int16_t offset = 0, tmp2 = 0; //, mktime1[10]; //

    U2Rx4Byte();
    //.58267 18-05-29 06:41:57 50 0 0   0.0 UTC(NIST) * .
    //58269 18-05-31 12:53:2
    while (BufferRead_UART2(tmp1 + getbytes++));
    getop = Str_Find_Head(tmp1, "UTC", getbytes - 1, 3);
    offset = getop - 32;
    if (offset > 0) {
        timeptr.tm_isdst = 0;
        timeptr.tm_wday = 0;
        timeptr.tm_yday = 0;
        tmp2 = (int16_t) ((tmp1[offset] - 0x30)*10 + (tmp1[1 + offset] - 0x30) + 100); //��
        timeptr.tm_year = tmp2;
        timeptr.tm_mon = (int16_t) ((tmp1[3 + offset] - 0x30)*10 + (tmp1[4 + offset] - 0x30) - 1); //��
        timeptr.tm_mday = (int16_t) ((tmp1[6 + offset] - 0x30)*10 + (tmp1[7 + offset] - 0x30)); //��
        timeptr.tm_hour = (int16_t) ((tmp1[9 + offset] - 0x30)*10 + (tmp1[10 + offset] - 0x30)); //ʱ
        timeptr.tm_min = (int16_t) ((tmp1[12 + offset] - 0x30)*10 + (tmp1[13 + offset] - 0x30)); //��
        timeptr.tm_sec = (int16_t) ((tmp1[15 + offset] - 0x30)*10 + (tmp1[16 + offset] - 0x30)); //��
        gmt = mktime(&timeptr); //�������gmt��
        gmt += 28800; //����ʱ��
        timeptr1 = gmtime(&gmt);
        WCGTIME0bits.year = DCH(timeptr1->tm_year - 100); //��
        WCGTIME0bits.month = DCH(timeptr1->tm_mon + 1); //��
        WCGTIME1bits.day = DCH(timeptr1->tm_mday); //��
        WCGTIME1bits.hour = DCH(timeptr1->tm_hour); //ʱ
        WCGTIME2bits.min = DCH(timeptr1->tm_min); //��
        WCGTIME2bits.sec = DCH(timeptr1->tm_sec); //��
#ifdef DEBUG_GET_TIME
        PrintTime();
#endif 
//        RTC_Refresh_Time();
    }
}

static void MKSendString(void) {//�������ݲ�С��20���ֽ�
    struct tm stm;
    //    uint8_t bytes = 0; //���֡ͷ
    uint8_t tmp[20];
    //    uint16_t crc;
    tmp[0] = 'A';
    tmp[1] = '2';
    tmp[2] = 20; //���ʱ��
//    while (!RTC_Read_Time(&stm));
    tmp[3] = (stm.tm_year);
    tmp[4] = (stm.tm_mon);
    tmp[5] = (stm.tm_mday);
    tmp[6] = (stm.tm_hour);
    tmp[7] = (stm.tm_min);
    tmp[8] = (stm.tm_sec);
    //    bytes = 9;
    FloatToChar(&f_p, tmp + 9); //ת��Ϊѹ��ֵ
    CRC16_Check(tmp, 13);
    //    tmp[13] = crc >> 8;
    //    tmp[14] = crc - ((crc >> 8) << 8);
    //    bytes = 15;
    //    strcat(tmp, tm); //���ѹ��
    //��������
    UART2_SendString2(tmp, 15); //���ʹ�������
    //    return bytes;
}

void GPRS_Task(uint8_t mode) {
    uint8_t IsErr;
    uint8_t tmp1[100]; //, getbytes = 0, getop = 0; //ʱ��ͨѶ


    //    uint8_t tmp2[10]; //ʱ��ͨѶ

    memset(tmp1, 0, 50);
    //    memset(tmp2, 0, 9);
    //    HL6528_GetIP_Port(); //ÿ��ͨѶ��������IP��ַ�Ͷ˿ں�
    UART2_Open();
    //    Delay1s(3); //���⴮�ڼ�ⲻ�� ���ʹ��#ifdef
    WCG_Sta = GPRS_Dingling; //GPRS����
    IsErr = HL6528_DialingIsERR(mode);
    //    RS485SendString1("GPRS ONline Now!!!");
    if (!IsErr) {
//        LED_On();
        WCG_Sta = GPRS_Online; //GPRS��������
        //        Delay1s(); //��ʱ1s
        if (mode == GETTIME) {
            IFS3bits.RTCIF = 1;
        } else {
            U2Rx4Byte();
            ClrUART2Buf();
            //            Delay1s(); //��ʱ1s
            //            for()
            //            MKSendString();
            MKSendString();
            Delay100ms(1); //��ʱ1s
            MKSendString();
            Delay100ms(1); //��ʱ1s
        }
        if (WCGCON2bits.Debug2)//���Ե�2 GPRS
            RS485SendString1("GPRS ONline Now!!!");
    } else {
        WCG_Sta = GPRS_Err; //GPRS����ʧ��
        if (WCGCON2bits.Debug2) {//���Ե�2 GPRS
            RS485SendString1("\r\nGPRS DialingFail!!!Code:");
        }
    }
//    LED_Off();
    HL6528_Close(); //����ATָ�������}
    Delay1s();
    Delay1s();
    Delay1s();
    //    if (IsErr) {
    //        LED_On();
    //        Delay1s(); //��ʱ1s
    //        LED_Off();
    //    }

    //    if (WCGCON2bits.TestGPRSBy485) {//�����ͨ��485����GPRS�Ļ����������ݽ��   mark
    //        CopyDat(tmp, "WCG", 3);
    //        tmp[3] = 0x05;
    //        tmp[4] = IsErr;
    //        CRC16_Check(tmp, 5);
    //        WCGCON2bits.TestGPRSBy485 = 0;
    //    }
}

bool Sample_Task(void) {
    struct tm nowtime;
    uint8_t Getstr[50] = {0x01, 0x03, 0x04}; //���ڱ�����յ�����
    uint8_t Savstr[60] = {0x00}; //uart��ȡ����������01 03 04 3E F4 00 00 B6 29
    uint8_t Senstr[30] = {0};
    uint8_t cnt = 0, writebyte = 0; //����
    uint8_t getbytes = 0, getop = 0; // getPressureFlag = 0;

    while (1) {
        cnt++;
        if (cnt > 3)
            return false; //ѭ��5�κ󣬻�δ��ȡ����Ч��ѹ��ֵ��ֱ�ӷ���false ��Ӵ�����ʾ
        RS485SendString(GetPressureInt, 8);
        Delay100ms(2); //��ʱ2s ����С��1s ��������ָ���ȡ���ݵ������ݶ�ʧ
        U1Rx4Byte();
        getbytes = UARTGetData(BufferRead_UART1, Savstr, 50);
        if (getbytes < 40)
            getop = Str_Find_Head(Savstr, Getstr, 50, 3);
        else
            getbytes = 0;
        if (getop && CheckIsRight(Savstr + getop - 1, 7)) {
            CharToFloat(&f_p, Savstr + getop + 2);
            //#ifdef DEBUG_PRESSURE
            //    RS485SendString1("\r\nGet Pressure!!!\r\n10Mp:");
            //    CharToFloat(&f_p, Getstr + 3);
            //    f_p *= 10;
            //    printnums((uint32_t) (f_p));
            //    RS485SendString1("\r\n");
            //    PrintTime(); //��ӡʱ��
            //#endif
            RTC_Read_Time(&nowtime);
            Senstr[0] = 0x20;
            Senstr[1] = nowtime.tm_year & 0x00ff;
            Senstr[2] = nowtime.tm_mon;
            Senstr[3] = nowtime.tm_mday;
            Senstr[4] = nowtime.tm_hour;
            Senstr[5] = nowtime.tm_min;
            Senstr[6] = nowtime.tm_sec;
            CopyDat(Senstr + 7, Getstr + 3, 4); //��ֵ����
            Senstr[11] = Sum_Check(Senstr, 11);
            for (writebyte = 0; writebyte < 12; writebyte++) {//δ���� ͨ��C���Բ���
                CAT24_Write_Byte(gCatWriteAdd, *(Savstr + writebyte)); //�洢����
                gCatWriteAdd += 1;
                gCatCanReadAdd = gCatWriteAdd - 1;
                if (gCatCanReadNum < 65532) {
                    gCatCanReadNum += 1;
                    gCatCanReadAdd = 0;
                } else
                    gCatCanReadAdd = gCatWriteAdd;
                if (gCatWriteAdd >= 65532) {
                    gCatWriteAdd = 0;
                    gCatCanReadNum = 65532;
                }
            }
            return true;
        }
    }
    return false;
}



//    if (WCGCON2bits.Alarm_RST_FLAG) {//�����Ҫ�����Ļ�,��ô���¼������ڲ�������֮�������´α�����ʱ��
//        WCGCON2bits.Alarm_RST_FLAG = 0; //�����־Ϊ
//        if (WCGCON0bits.Send_60s < 3)//������ֵ�ж�
//            WCGCON0bits.Send_60s = 3;
//        else if (WCGCON0bits.Send_60s > 1440)
//            WCGCON0bits.Send_60s = 1440;
//        if (WCGCON1bits.Sample_5s < 1)//�ɼ���ֵ�ж�
//            WCGCON1bits.Sample_5s = 1;
//        else if (WCGCON1bits.Sample_5s > 17280)
//            WCGCON1bits.Sample_5s = 17280;
//
//        if (WCGCON1bits.Sample_5s > (WCGCON0bits.Send_60s * 12))//����ɼ�ʱ����ڷ���ʱ�䣬��ô���ɼ�ʱ������Ϊ����ʱ��
//            WCGCON1bits.Sample_5s = WCGCON0bits.Send_60s * 12;
//        WCGPeriodbits.B1 = (WCGCON0bits.Send_60s * 12) / WCGCON1bits.Sample_5s; //����
//        WCGPeriodbits.Y2 = (WCGCON0bits.Send_60s * 12) % WCGCON1bits.Sample_5s; //����     
//        WCGPeriodbits.CNT = 0; //�������
//    }



//    if (WCGPeriodbits.CNT == WCGPeriodbits.B1) {//�¸�ʱ����Ƿ��͵�ʱ��
//        //���ñ���ʱ��Ϊ������ʱ��
//        if (!WCGPeriodbits.Y2) {//�������Ϊ0�Ļ�����ôֱ�������´βɼ�ʱ�䣨�ϴ�ʱ���Ѿ����ˣ�����֮�������´μ����ϴ�ʱ��
//            now_second += (WCGCON1bits.Sample_5s * 5); //�����´α�����ʱ��
//            //��ʼ����GPRS�ϴ�����
//            WCGCON2bits.Send_FLAG = 1; //�ɼ�ʱ��ͷ���ʱ�������
//            WCGPeriodbits.CNT = 0;
//        } else {
//            now_second += WCGPeriodbits.Y2 * 5; //�����ϴ�ʱ��
//            WCGPeriodbits.CNT += 1;
//        }
//    } else if (WCGPeriodbits.CNT > WCGPeriodbits.B1) {
//        now_second += (WCGCON1bits.Sample_5s * 5); //�����´α�����ʱ��
//        //��ʼ����GPRS�ϴ�����
//        WCGPeriodbits.CNT = 0;
//    } else {
//        //���ñ���ʱ��Ϊ�ɼ���ʱ��
//        WCGCON2bits.Sample_FLAG = 1;
//        now_second += (WCGCON1bits.Sample_5s * 5); //���ϱ�����ʱ��
//        WCGPeriodbits.CNT += 1;
//    }

uint32_t CalaAlarmTime(void) {
    static uint8_t cnt = 0;
    static uint32_t all_alarm_time = 0;
    uint32_t alarm_time = 0; //, tmp;
    //#define DEBUG_CALC_TIME 0
    if (WCGCON2bits.Period_FLAG) {
        WCGCON3bits.delay = WCGCON1bits.Sample_5s * 5; //�ɼ�ʱ��
        WCGCON3bits.count = WCGCON0bits.Send_60s * 12 / WCGCON1bits.Sample_5s; //����ɼ��Ĵ��� ��WCGCON1bits.Sample_5s=0ʱ������ѧ����
        WCGCON4bits.delay = WCGCON0bits.Send_60s * 60; //(WCGCON0bits.Send_60s * 12 % WCGCON1bits.Sample_5s)*5; //�����ϴ���ʱ��
        WCGCON4bits.count = 0; //�ϴ��ۼƴ�������
        WCGCON2bits.Sample_FLAG = 0;
        WCGCON2bits.Send_FLAG = 0;
#ifdef DEBUG_CALC_TIME
        DeBug_PrintStrNum("\r\nPeriodFlag:", 1);
        DeBug_PrintStrNum("\r\nWCGCON3bits.delay:", WCGCON3bits.delay);
        DeBug_PrintStrNum("\r\n WCGCON3bits.count:", WCGCON3bits.count);
        DeBug_PrintStrNum("\r\n  WCGCON4bits.delay:", WCGCON4bits.delay);
        DeBug_PrintStrNum("\r\n   WCGCON4bits.count:", WCGCON4bits.count);
        //        RS485SendString("/r/nWCGCON3bits.delay:");
        //        my_itoa(WCGCON3bits.delay);
        //        RS485SendString("/r/nPeriodFlag=1/r/n!!!");
        //        RS485SendString("/r/nPeriodFlag=1/r/n!!!");
        //        WCGCON3bits.delay = 10; //�ɼ�ʱ��
        //        WCGCON3bits.count = 6; //����ɼ��Ĵ���
        //        WCGCON4bits.delay = 0; //�����ϴ���ʱ�� ��ʱ��Ϊ12*3+3=39s
        //        WCGCON4bits.count = 0; //�ϴ��ۼƴ�������      
#endif
        //        WCGCON2bits.Cala_Time_Is_Mod = WCGCON4bits.delay % WCGCON3bits.delay;
        cnt = 0;
        alarm_time = WCGCON3bits.delay; //���ص�һ�βɼ�ʱ��
        all_alarm_time = alarm_time; //���ۼ�ֵ��ʼ��
        WCGCON2bits.Period_FLAG = 0;
    } else {
        if (cnt < WCGCON3bits.count - 1) {//�����ʱ��û�е�����ô��������ʱ����Ϊ�ɼ���ʱ��
            WCGCON2bits.Sample_FLAG = 1;
#ifdef DEBUG_CALC_TIME
            RS485SendString1("\r\nsampleFLAG339:\r\n");
#endif
            StartTMR2();
            IFS0bits.T2IF = 1;
            cnt += 1;
            //#ifdef DEBUG_RTCC_TIME
            //            samplecount = cnt;
            //#endif
            alarm_time = WCGCON3bits.delay; //1160
            all_alarm_time += alarm_time;
        } else {//����ɼ������͹涨��ʱ�������ͬ����ô��Ҫ�ж��Ƿ�ɼ�ʱ���Ƿ����ϴ�ʱ���������
            if (WCGCON4bits.delay != all_alarm_time) {//�������ʱ��պ��ǲɼ�ʱ����������Ļ��������ƼĴ���2��־Ϊ��1�������´ζ�ʱʱ��
                if (WCGCON4bits.count) {
                    WCGCON4bits.count = 0;
                    WCGCON2bits.Send_FLAG = 1;
                    cnt = 0;
                    //                    alarm_time = WCGCON3bits.delay - all_alarm_time;
                    all_alarm_time += WCGCON3bits.delay;
                    alarm_time = all_alarm_time % WCGCON4bits.delay;
                    all_alarm_time = alarm_time;
                    WCGCON3bits.count = (WCGCON4bits.delay - all_alarm_time) / WCGCON3bits.delay + 1; //���¼������ߵĴ���
                } else {//һ�����ڵ����һ�βɼ�����
                    //#ifdef DEBUG_RTCC_TIME
                    //                    samplecount = cnt + 1;
                    //#endif 
                    WCGCON2bits.Sample_FLAG = 1;
#ifdef DEBUG_CALC_TIME
                    RS485SendString1("\r\nsampleFLAG363:\r\n");
#endif
                    StartTMR2();
                    IFS0bits.T2IF = 1;
                    WCGCON4bits.count += 1; //���ߴ�����1
                    alarm_time = WCGCON4bits.delay - all_alarm_time; //��ʾ��n������ϴ���ʱ��                   
                }
            } else {//��֮������ʱ��==����ʱ��
                //#ifdef DEBUG_RTCC_TIME
                //                samplecount = cnt + 1;
                //#endif
                WCGCON2bits.Sample_FLAG = WCGCON2bits.Send_FLAG = 1;
#ifdef DEBUG_CALC_TIME
                RS485SendString1("\r\nsampleFLAG379:\r\n");
#endif
                StartTMR2();
                IFS0bits.T2IF = 1;
                cnt = 0; //����ڲ�����
                alarm_time = WCGCON3bits.delay;
                all_alarm_time = WCGCON3bits.delay;
                WCGCON3bits.count = WCGCON4bits.delay / WCGCON3bits.delay; //���¼������ߵĴ���
            }
        }
    }
    //    if (!last_alarm_time) {//������һ�����õı���ʱ��Ϊ0�Ļ�����ôֱ��
    //        alarm_time = WCGCON3bits.delay;
    //        last_alarm_time = 0;
    //    }
#ifdef DEBUG_CALC_TIME
    if (WCGCON2bits.Sample_FLAG) {
        RS485SendString1("\r\nsampleFLAG:\r\n");
        DeBug_PrintStrNum("\r\nWCGCON3bits.delay:", WCGCON3bits.delay);
        DeBug_PrintStrNum("\r\n WCGCON3bits.count:", WCGCON3bits.count);
    }
    if (WCGCON2bits.Send_FLAG) {
        RS485SendString1("\r\nsend:FLAG\r\n:");
        DeBug_PrintStrNum("\r\n  WCGCON4bits.delay:", WCGCON4bits.delay);
        DeBug_PrintStrNum("\r\n   WCGCON4bits.count:", WCGCON4bits.count);
    }
    DeBug_PrintStrNum("\r\ncnt:", cnt);
    DeBug_PrintStrNum("\r\nalarm_time:", alarm_time);
#endif
    return alarm_time;
}

void SetNextAlarm(uint32_t sample_sec) {
    struct tm gettime, changetime, * settime;
    time_t gmt;

    while (!RTC_Read_Time(&gettime)); //�ݴ����
    changetime.tm_isdst = 0;
    changetime.tm_yday = 0;
    changetime.tm_wday = 0;
    changetime.tm_year = (int16_t) (HCD(gettime.tm_year) + 100); //��
    changetime.tm_mon = (int16_t) (HCD(gettime.tm_mon) - 1); //��
    changetime.tm_mday = (int16_t) (HCD(gettime.tm_mday)); //��
    changetime.tm_hour = (int16_t) (HCD(gettime.tm_hour)); //ʱ
    changetime.tm_min = (int16_t) (HCD(gettime.tm_min)); //��
    changetime.tm_sec = (int16_t) (HCD(gettime.tm_sec)); //��
    gmt = mktime(&changetime); //�������gmt��
    gmt += sample_sec; //����ʱ��
    settime = gmtime(&gmt);
    changetime.tm_year = (int16_t) (DCH(settime->tm_year - 100)); //��
    changetime.tm_mon = (int16_t) (DCH(settime->tm_mon + 1)); //��
    changetime.tm_mday = (int16_t) (DCH(settime->tm_mday)); //��
    changetime.tm_hour = (int16_t) (DCH(settime->tm_hour)); //ʱ
    changetime.tm_min = (int16_t) (DCH(settime->tm_min)); //��
    changetime.tm_sec = (int16_t) (DCH(settime->tm_sec)); //��
    RTC_Set_Alarm(changetime); //ÿ��һ������
}

//void WCGGetArg(void) {
//    do {
//
//    } while ();
//}

static void ReadArgByRegAdd(uint8_t * arg) {
    arg[0] = WCGTIME0bits.year;
    arg[1] = WCGTIME0bits.month;
    arg[2] = WCGTIME1bits.day;
    arg[3] = WCGTIME1bits.hour;
    arg[4] = WCGTIME2bits.min;
    arg[5] = WCGTIME2bits.sec;
    arg[6] = WCGCON0bits.Send_60s >> 8;
    arg[7] = (uint8_t) (WCGCON0bits.Send_60s & 0x00FF); //(WCGCON0bits.Sample_5s>>3);
    arg[8] = WCGCON1bits.Sample_5s >> 8;
    arg[9] = (uint8_t) (WCGCON1bits.Sample_5s & 0x00FF);
    arg[10] = WCGCON2bits.WCG_ID;
    arg[11] = WCGIPbits.IP3;
    arg[12] = WCGIPbits.IP2;
    arg[13] = WCGIPbits.IP1;
    arg[14] = WCGIPbits.IP0;
    arg[15] = WCGPORT >> 8;
    arg[16] = WCGPORT & 0x00ff;
}

static void Fun03ReadArg(void) {
    // *send: 57 47 43 03 00 06 ?? ??
    // *rec: 57 47 43 03 11 17 10 30 13 01 08 05 A0 00 0C 03 B7 F6 4A 44 13 CE 05 A7

    uint8_t send_rec[30];
    RefreshReg(); //ˢ��Arg����RefreshReg
    send_rec[0] = 0x57;
    send_rec[1] = 0x43;
    send_rec[2] = 0x47;
    send_rec[3] = 0x03;
    send_rec[4] = 0x11;
    ReadArgByRegAdd(send_rec + 5);
    CRC16_Check(send_rec, 22); //����CRC
    RS485SendString((const uint8_t *) send_rec, 24); //�������� ע�����ݷ��Ͳ�Ҫ���ж�����
}

static void WriteArgByRegAdd(uint8_t * arg) {
    //���ݼĴ�����ַ�����������ݳ��Ⱥ�����,�жϽ�����������
    //* send: 57 47 43 04 00 05 17 12 10 12 10 20 00 03 00 20 05 B7 F6 4A 44 12 CE 1A 6A
    //* rec: 57 47 43 04 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH 
    WCGTIME0bits.year = (*arg);
    WCGTIME0bits.month = (*(arg + 1));
    WCGTIME1bits.day = (*(arg + 2));
    WCGTIME1bits.hour = (*(arg + 3));
    WCGTIME2bits.min = (*(arg + 4));
    WCGTIME2bits.sec = (*(arg + 5));
    WCGCON0bits.Send_60s = ((uint16_t)*(arg + 6) << 8)+*(arg + 7); //ֱ��BCD��                    
    DataIsVaild(WCGCON0bits.Send_60s, 3, 1440);
    WCGCON1bits.Sample_5s = ((uint16_t)*(arg + 8) << 8)+*(arg + 9); //ֱ��BCD��
    DataIsVaild(WCGCON1bits.Sample_5s, 2, 17280);
    WCGCON2bits.WCG_ID = *(arg + 10);
    WCGIPbits.IP3 = *(arg + 11);
    WCGIPbits.IP2 = *(arg + 12);
    WCGIPbits.IP1 = *(arg + 13);
    WCGIPbits.IP0 = *(arg + 14);
    WCGPORT = (*(arg + 15) << 8)+*(arg + 16); //�˿ں� 
}

static void Fun04WriteArg(const uint8_t * get_vaild_str) {
    uint8_t send_rec[30];
    //����ֵ����                
    // *send: 57 43 47 04 00 06 17 12 10 12 10 20 00 03 00 05 03 B7 F6 4A 44 12 CE 4E 7E    
    // *rec:57 47 43 04 11 17 12 10 12 10 20 |00 03 |00 05 03 B7 F6 4A 44 12 CE 6B A1
    send_rec[0] = 0x57;
    send_rec[1] = 0x43;
    send_rec[2] = 0x47;
    send_rec[3] = 0x04;
    CopyDat(send_rec + 5, get_vaild_str + 6, 17); //������������
    if ((((uint16_t) get_vaild_str[12] << 8) + get_vaild_str[13]) < 3) {//��ֵ���� send time
        send_rec[11] = 0;
        send_rec[12] = 3;
    } else if ((((uint16_t) get_vaild_str[12] << 8) + get_vaild_str[13]) > 1440) {
        send_rec[11] = 0x05;
        send_rec[12] = 0xA0;
    }
    if (((uint16_t) get_vaild_str[14] << 8) + get_vaild_str[15] < 2) {//��ֵ���� sample time
        send_rec[13] = 0;
        send_rec[14] = 2;
    } else if (((uint16_t) get_vaild_str[14] << 8) + get_vaild_str[15] > 17280) {
        send_rec[13] = 0x43;
        send_rec[14] = 0x80;
    }
    //    if (send_rec[4] > RegAdd[6])//���������������
    //        send_rec[4] = RegAdd[6];

    WriteArgByRegAdd(send_rec + 5);
    RTC_Refresh_Time();
    WCGCON2bits.Period_FLAG = 1; //���¼���RTCC ��������´ζ�ʱ��ʱ��
    IFS3bits.RTCIF = 1;

    CRC16_Check(send_rec, 22); //����CRC
    RS485SendString(send_rec, 24); //�������� ע�����ݷ��Ͳ�Ҫ���ж�����
}

static void Fun05TestGPRS(const uint8_t IsShow) {
    // * send: 57 43 47 05 30 12 77 
    // * rec:  57 43 47 05 10 FF B7 4D 
    //����GPRS�Ĳ���
    uint8_t send_rec[10];
    send_rec[0] = 0x57;
    send_rec[1] = 0x43;
    send_rec[2] = 0x47;
    send_rec[3] = 0x05;
    send_rec[4] = GPRS_Init;
    send_rec[5] = GPRS_Opertion_OK;
    CRC16_Check(send_rec, 6); //����CRC
    RS485SendString((const uint8_t *) send_rec, 8); //�������� ע�����ݷ��Ͳ�Ҫ���ж�����
    if (IsShow == 0x31)//��ʾGPRS���߹���
        WCGCON1bits.TestGPRSShow = 1; //��ʾGPRS��������
    else
        WCGCON1bits.TestGPRSShow = 0; //����ʾ
    WCGCON2bits.Send_FLAG = 1; //
    WCGCON2bits.TestGPRSBy485 = 1;
    //    break;
}

static void Fun30GetHistory(const uint8_t * get_vaild_str) {
    uint8_t send_rec[250]; //�����Ҫ���͵�����
    uint8_t cntcat = 0;
    uint16_t sizecnt = 0, sizes = 0, frames = 0, frames_last = 0, offset = 0;

    CopyDat(send_rec, get_vaild_str, 4); //����֡ͷ+������  
    //�����ֽ��� 
    // * send: 57 43 47 30 CRCL CRCH 
    // * rec:  57 43 47 30 02 01 [12*20] 76 3C //240+8=248
    // * rec:  57 43 47 30 02 02 [12*20] 76 3C //240+8=248
    //����GPRS�Ĳ���
    sizes = gCatCanReadNum / 12;
    frames = sizes / 20;
    frames_last = frames % 20;
    for (sizecnt = 0; sizecnt < frames; sizecnt++) {
        send_rec[0] = 0x57;
        send_rec[1] = 0x43;
        send_rec[2] = 0x47;
        send_rec[3] = 0x30;
        send_rec[4] = frames + 1; //��֡��
        send_rec[5] = sizecnt;
        for (cntcat = 0; cntcat < 240; cntcat++) {//12*20
            CAT24_Read_Byte(gCatCanReadAdd, send_rec + 6 + cntcat);
        }
        CRC16_Check(send_rec, 246); //����CRC
        RS485SendString(send_rec, 248); //
    }
    if (frames_last) {
        for (sizecnt = 0; sizecnt < frames; sizecnt++) {
            send_rec[0] = 0x57;
            send_rec[1] = 0x43;
            send_rec[2] = 0x47;
            send_rec[3] = 0x30;
            send_rec[4] = frames + 1; //��֡��
            send_rec[5] = send_rec[4];
            offset = frames_last * 12;
            for (cntcat = 0; cntcat < offset; cntcat++) {//12*20
                CAT24_Read_Byte(gCatCanReadAdd, send_rec + 6 + cntcat);
            }
            CRC16_Check(send_rec, 246); //����CRC
            RS485SendString(send_rec, 248); //
        }
    }
    //    break;
}

bool WCGPCCop(void) {
    uint8_t tmp[50]; //���ڽ��ܵ�������
    uint8_t get_vaild_str[50]; //��ȡ�������

    uint8_t getbytes = 0, getop = 0; //��ȡ�ֽ��� ��ȡλ��

    memset(tmp, 0, 50);
    //    Delay1s();//��ʱ���Ѿ���ʱ
    U1Rx4Byte();
    getbytes = UARTGetData(BufferRead_UART1, tmp, 50); //��ȡmark  �޸�����
    getop = Str_Find_Head(tmp, WCG, getbytes, sizeof (WCG) - 1);
    CopyDat(get_vaild_str, tmp + getop - 1, getbytes);

    if (getop && CheckIsRight(get_vaild_str, getbytes - 2)) {
        //���ݼĴ�����ַ�����������ݳ��Ⱥ�����,�жϽ�����������

        switch (get_vaild_str[3]) {
            case 0x30://��ʷ���� //δ����
            {
                Fun30GetHistory(get_vaild_str);
                break;
            }
            case 0x05://GPRS���߲���
            {
                Fun05TestGPRS(get_vaild_str[4]);
                break;
            }
            case 0x04://���ò���
            {
                Fun04WriteArg(get_vaild_str);
                break;
            }
            case 0x03://��ȡ����
            {
                Fun03ReadArg();
                break;
            }
        }
        return true;
    }
    return false;
}

static void RefreshReg(void) {
    struct tm tm_tmp;
    while (!RTC_Read_Time(&tm_tmp));
    WCGTIME0bits.year = tm_tmp.tm_year;
    WCGTIME0bits.month = tm_tmp.tm_mon;
    WCGTIME1bits.day = tm_tmp.tm_mday;
    WCGTIME1bits.hour = tm_tmp.tm_hour;
    WCGTIME2bits.min = tm_tmp.tm_min;
    WCGTIME2bits.sec = tm_tmp.tm_sec;
}

//static void LoadReg(void) {
//    //    struct tm tm_tmp;
//    //    while (!RTC_Read_Time(&tm_tmp));
//    WCGTIME0bits.year; //= DCH(tm_tmp.tm_year);
//    WCGTIME0bits.month; // = DCH(tm_tmp.tm_mon);
//    WCGTIME1bits.day; //= DCH(tm_tmp.tm_mday);
//    WCGTIME1bits.hour; // = DCH(tm_tmp.tm_hour);
//    WCGTIME2bits.min; //= DCH(tm_tmp.tm_min);
//    WCGTIME2bits.sec; //= DCH(tm_tmp.tm_sec);
//}



/*uint8_t [year,mon,day,hour,min,sec,Send_60s,Sample_5s.WCG_ID,IP0,IP1,IP2,IP3,PORT]
 *send��WCG+fun_code+reg+reg_num+CRC
 *rec��WCG+fuc_code+data_num+data[17]+CRC
 * fun_code 03:��ȡ����
 * fun_code 04:���ò���
 * /////////��ȡ����
 *send��WCG+03+reg+reg_num+CRC
 *rec��WCG+03+dat_num+dat[dat_num]+CRC
 * send: 57 47 43 03 00 05 CRCL CRCH
 * rec: 57 47 43 03 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
 * 
 * fun_code 03:��ȡ����
 * fun_code 04:���ò���
 * /////////��ȡ����
 *send��WCG+04+reg+reg_num+dat+CRC
 *rec��WCG+04+dat_num+dat+CRC
 * send: 57 47 43 04 00 05 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE 04 35
 * rec: 57 47 43 04 10 17 12 10 12 10 20 03 20 05 B7 F6 4A 44 12 CE CRCL CRCH
 * 
 * error handle:code 0x80
 * 
 */




