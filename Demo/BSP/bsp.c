/*
 *********************************************************************************************************
 *                                             Microchip dsPIC33FJ
 *                                            Board Support Package
 *
 *                                                   Micrium
 *                                    (c) Copyright 2005, Micrium, Weston, FL
 *                                              All Rights Reserved
 *
 *
 * File : BSP.C
 * By   : Eric Shufro
 *********************************************************************************************************
 */

#include <includes.h>
//#include "HL6528.h"
//#include "E41.h"
//#include "xc.h"

void OSCILLATOR_Initialize(void) {
    // DOZEN disabled; DOZE 1:8; RCDIV FRC/1; ROI disabled; 
    CLKDIV = 0x3200;

    // Set the secondary oscillator    
    OSCCONbits.SOSCEN = 1; //������������
    //    __builtin_write_OSCCONL(0x02);
    __builtin_write_OSCCONL(0x00); //2M    4M
    //    OSCCONbits.OSWEN = 1;
    //    OSC_Unlock_Sequence(); //�л�ʱ��
}

/*
 *********************************************************************************************************
 *                                         BSP INITIALIZATION
 *
 * Description : This function should be called by your application code before you make use of any of the
 *               functions found in this module.
 *
 * Arguments   : none
 *********************************************************************************************************
 */

void BSP_Init(void) {
    OSCILLATOR_Initialize(); //��ʼ��ʱ��
    LED_Init(); //��ʼ��LED
    WCG_Init(); //��ʼ��WCG����
    //    RTC_Init(); //��ʼ��ʵʱʱ��
    PPSInit(); //ѡ���豸
    UART2_Init(); //��ʼ������2������GPRSͨѶhl6528
    //    UART3_Init(); //��ʼ������3�����ڶ̳�����ͨѶ433
    RS485_Init(); //��ʼ������1������485ͨѶ��λ��ͨѶ
    I2C_Init();
    UART2_Close();
    TMR1_Initialize();
    TMR3_Initialize();
    TMR4_Initialize();
}

