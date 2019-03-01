#include <includes.h>
#include "Configbits.h"

#ifdef DEBUG_MAIN_VAR
volatile uint32_t rtime;
uint8_t main_cnt = 0;
//uint32_t main_nums;
//volatile uint8_t samplecount;
//volatile uint8_t samplecount1;
#endif

/*
                         Main application
 */
void main(void) {
    BSP_Init(); //�ײ�������ʼ��
    HL6528_Init(); /*Initialize the HL6528*/
    CAT24_Init();
    LCD_Init();
    NUMS_SHOW(1, 0);
    IFS3bits.RTCIF = 1; //������ص��жϱ�־״̬λ����
    RS485SendString("Start", 5); //�ȷ���һ���ֽڣ�������մ���
    WCGCON2bits.Sample_FLAG = 1; //��ȡһ��ѹ��ֵ
    StartTMR2();
    IFS0bits.T2IF = 1;
    Delay1s();
    WCGCON2bits.Sample_FLAG = 1; //��ȡ�ڶ���ѹ��ֵ
    StartTMR2();
    IFS0bits.T2IF = 1;
//    WCGCON1bits.TestGPRSShow = 1;

    //    while (1) {
    //        uint16_t* i;
    //        char tmp[10];
    //        i = tmp;
    //        *i = 0;
    //        i = tmp + 1;
    //        *i = 0;
    //        //        tmp[20] = i;
    //        //        tmp[1000] = 0;
    //    }
    //    WCGCON2bits.Send_FLAG = 1;
    while (1) {
        //        Delay1s(5);
        //        WCGPCCop();
        //�Ż��͹��ģ��ر�ģ��
        while (!WCGCON2bits.PC_Cop_FLAG && !WCGCON2bits.Send_FLAG) {//�������ͨѶ�׶λ��Ƿ������ݵĻ�����ô������ѭ��
            //����IO�� ���ر�ģ��
            //            CAT_WP_LAT = 1; //д����
            //            T1CONbits.TON = 0;
            U1MODEbits.WAKE = 1;
            Sleep();
            //            DeepSleep();
            U1MODEbits.WAKE = 1;
        }
        if (WCGCON2bits.Send_FLAG) {
            WCGCNTbits.Send_CNT++;
            GPRS_Task(0);
            WCGCON2bits.Send_FLAG = 0;
        }
        if (WCGCON2bits.SET_TIME_FLAG) {
            GPRS_Task(GETTIME);
            WCGCON2bits.SET_TIME_FLAG = 0;
        }
    }
}


