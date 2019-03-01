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
    BSP_Init(); //底层驱动初始化
    HL6528_Init(); /*Initialize the HL6528*/
    CAT24_Init();
    LCD_Init();
    NUMS_SHOW(1, 0);
    IFS3bits.RTCIF = 1; //外设相关的中断标志状态位清零
    RS485SendString("Start", 5); //先发送一个字节，避免接收错误
    WCGCON2bits.Sample_FLAG = 1; //获取一次压力值
    StartTMR2();
    IFS0bits.T2IF = 1;
    Delay1s();
    WCGCON2bits.Sample_FLAG = 1; //获取第二次压力值
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
        //优化低功耗，关闭模块
        while (!WCGCON2bits.PC_Cop_FLAG && !WCGCON2bits.Send_FLAG) {//如果处于通讯阶段或是发送数据的话，那么就跳过循环
            //设置IO口 并关闭模块
            //            CAT_WP_LAT = 1; //写保护
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


