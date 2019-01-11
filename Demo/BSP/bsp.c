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
    OSCCONbits.SOSCEN = 1; //开启辅助振荡器
    //    __builtin_write_OSCCONL(0x02);
    __builtin_write_OSCCONL(0x00); //2M    4M
    //    OSCCONbits.OSWEN = 1;
    //    OSC_Unlock_Sequence(); //切换时钟
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
    OSCILLATOR_Initialize(); //初始化时钟
    LED_Init(); //初始化LED
    WCG_Init(); //初始化WCG参数
    //    RTC_Init(); //初始化实时时钟
    PPSInit(); //选择设备
    UART2_Init(); //初始化串口2，用于GPRS通讯hl6528
    //    UART3_Init(); //初始化串口3，用于短程无线通讯433
    RS485_Init(); //初始化串口1，用于485通讯上位机通讯
    I2C_Init();
    UART2_Close();
    TMR1_Initialize();
    TMR3_Initialize();
    TMR4_Initialize();
}

