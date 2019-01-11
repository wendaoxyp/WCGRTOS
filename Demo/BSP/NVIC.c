/* 
 * File:   NVIC.c
 * Author: TURONG62
 *
 * Created on 2016��6��6��, ����8:48
 */
#include "SerialBuffer.h"
#include "includes.h"
#include "stdbool.h"
#include "stdio.h"
#include "RTCC.h"
#include "LCD.h"
#include "WCG.h"
#include "bsp.h"

extern volatile uint8_t gT3flag;
extern volatile uint8_t gT3Cnt;
static uint8_t T0_Cnt = 0;
static uint32_t gRTC_Cnt = 0;

/*************************************
Function: �ⲿ�ն�0
Description: ��ѹ���
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv))_ISR _INT0Interrupt(void) {
    IFS0bits.INT0IF = 0;
}
/*************************************
Function: ��ʱ���ж� 
Description: ������GPRS���߹����У���ʱʱ��
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {
//    gT3Count++;
//    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
//}

/*************************************
Function: ��ʱ���ж� 
Description: ����485ͨѶ��ʱ����ʱ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T3Interrupt(void) {
    static uint8_t t3cnt = 0;
    if (++t3cnt > gT3Cnt) {
        t3cnt = 0;
        gT3flag = 1;
    }
    IFS0bits.T3IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ���ж� 
Description: ����485ͨѶ��ʱ����ʱ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T2Interrupt(void) {
    //    StopTMR2(); //ֹͣ��ʱ
    //    if (WCGCON2bits.Sample_FLAG) {
    //        //#ifdef DEBUG_SAMPLE
    //        //        for (main_cnt = 0; main_cnt < 2; main_cnt++) {
    //        //            Delay100ms(3);
    //        //            LED_Toggle();
    //        //        }
    //        //        RS485SendString1("\r\nStart Sample!!! count:");
    //        //        //            Delay100ms(3);
    //        //        printnums(WCGCNTbits.Sample_CNT++);
    //        //        NUMS_SHOW(WCGCNTbits.Sample_CNT, 0);
    //        //#endif
    //        if (Sample_Task()) {
    //            LED_Toggle1(2, 4);
    //            //#ifdef DEBUG_PRESSURE
    //            //            RS485SendString1("\r\nCan't get pressure!!!\r\n");
    //            //#endif
    //            WCGCON2bits.Sample_FLAG = 0; //��ͬ�붨ʱ��2��־λ
    //        }
    //    }
    IFS0bits.T2IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ���ж� 
Description: LCD��ʾ
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T1Interrupt(void) {//cvery second
    //    struct tm tmptr;
    uint16_t pressure10 = 0;

    if (gRTC_Cnt++ >= 86400) {//һ��У��ʱ��һ��
        gRTC_Cnt = 0;
        WCGCON2bits.SET_TIME_FLAG = 1; //Уʱ��־��1
    }
    switch (T0_Cnt++ % 4) {
        case 0:
        {
            pressure10 = f_p * 100;
            if (pressure10) {//���ѹ��ֵΪ0
                //                NUMS_SHOW((uint32_t) pressure10, 0);
                W_LCDCON.LCD_Flagbits.F_DP = 2;
            } else {
                W_LCDCON.LCD_Flagbits.F_DP = 0;
                //                NUMS_SHOW(0, 0);
            }
            W_LCDCON.LCD_Flagbits.F_KPa = 1;
            W_LCDCON.LCD_Flagbits.F_Num = 1;
            LCD_Task(pressure10); //ִ��LCDˢ������
            break;
        }
        case 2:
        {
            W_LCDCON.LCD_Flagbits.F_KPa = 0;
            W_LCDCON.LCD_Flagbits.F_DP = 0;
            W_LCDCON.LCD_Flagbits.F_Time = 1;
            LCD_Task(pressure10); //ִ��LCDˢ������
            break;
        }
    }


    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ʱ��t4�ж� 
Description: ���ڲɼ����ݵ�����
Input: �� 
Output: ��
 *************************************/
void __attribute__((__interrupt__, __auto_psv__, __shadow__)) _T4Interrupt(void) {
    //    StopTMR4();
    //    U1Rx4Byte(); //�������С��4�ֽڵ����ݣ�
    //    WCGPCCop();
    //    U1Rx4Byte(); //�������С��4�ֽڵ����ݣ�
    //    ClrUART1Buf(); //�����û�ͨѶ��������
    //    WCGCON2bits.PC_Cop_FLAG = 0;
    IFS1bits.T4IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}

/*************************************
Function: ��ƽ�仯�ж� 
Description: ��ȡ���������
Input: �� 
Output: ��
 *************************************/
//void __attribute__((__interrupt__, __auto_psv__)) _CNInterrupt(void) { //���Ѹ������
//    if (S1) {//ͨ���ڶ���������ȡ����
//        gPulseCount++; //������+1
//        if (FLagArgbits.T1CountFlag && FLagArgbits.T1CountLastFlag) {//�������T1��ʱ�������ǵڶ��ν��룬��ɼ�����
//            gPulseTime = gT1Count * 1000 + (((u32) TMR1) * 1000 >> 15) + 100; //��λms
//            if (gPulseTime < 2000)//�ɼ�ʱ��С��2s
//                gPulseTime = 0;
//            else {
//                FLagArgbits.PulseTimeFlag = 1; // ����Ѿ���ȡ������ʱ�䣬��ô��Ҫ�رն�ʱ��
//                FLagArgbits.T1CountFlag = 0;
//                T1CONbits.TON = 0;
//            }
//        }
//        TMR1 = 0;
//        gT1Count = 0;
//        FLagArgbits.T1CountLastFlag = FLagArgbits.T1CountFlag; //ͨ�������أ��ر�FLagArgbits.T1CountLastFlag
//    }
//    IFS1bits.CNIF = 0;
//}

/*************************************
Function: UART1�����ж�
Description: 485ͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
//    uint8_t cnt = 0;
    //    if (!T4CONbits.TON) {
    //        StartTMR4(); ///��ʾPC���ں��豸ͨѶ
    //        WCGCON2bits.PC_Cop_FLAG = 1;
    //    }
    //    for (cnt = 0; cnt < 4; cnt++)
    //        if (U1STAbits.URXDA) //û�н��յ�
    //            BufferWrite_UART1();
    IFS0bits.U1RXIF = 0;
}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    uint8_t cnt = 0;

    for (cnt = 0; cnt < 4; cnt++)
        if (U2STAbits.URXDA == 1) //û�н��յ�        
            BufferWrite_UART2();
    IFS1bits.U2RXIF = 0;
}

/*************************************
Function: UART2�����ж�
Description: GPRSͨѶ
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void) {
    uint8_t cnt = 0;

    for (cnt = 0; cnt < 4; cnt++)
        if (U3STAbits.URXDA == 1) //û�н��յ�        
            BufferWrite_UART3();
    IFS5bits.U3RXIF = 0;
}

/*************************************
Function: UART1�����ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {

    if (U1STAbits.OERR)
        U1STAbits.OERR = 0;
    if (U1STAbits.FERR) {//mark
        //        U1RXREG = U1RXREG;
        U1STAbits.FERR = 0;
    }
    if (U1STAbits.PERR)
        U1STAbits.PERR = 0;
    IFS4bits.U1ERIF = 0;

}

/*************************************
Function: UART2�����ж�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {

    if (U2STAbits.OERR == 1)
        U2STAbits.OERR = 0;
    IFS4bits.U2ERIF = 0;

}

/*************************************
Function: UART2�����ж�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U3ErrInterrupt(void) {

    if (U3STAbits.OERR == 1)
        U3STAbits.OERR = 0;
    IFS5bits.U3ERIF = 0;

}

/*************************************
Function: Ĭ���ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt(void) {
//    RS485SendString1("\r\nDefaultInt:");
    printnums(INTCON1);
    if (INTCON1bits.STKERR)INTCON1bits.STKERR = 0;
    if (INTCON1bits.ADDRERR)INTCON1bits.ADDRERR = 0;
    if (INTCON1bits.MATHERR)INTCON1bits.MATHERR = 0;
    //    asm("GOTO __reset");  //�Զ���λ
    //    Reset();
    //    Sleep();
}

//void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
//
//    static uint16_t i2c_operatcode;
//    static uint8_t* pi2c_buf_ptr;
//    static uint16_t i2c_address;
//    static uint8_t i2c_bytes_left;
//    static I2C_Flag i2c_flag;
//    static bool i2c_IsResart; //�豸�Ƿ�����
//
//
//    if (I2C1STATbits.IWCOL) {//���д��ͻ���λΪ1����ô�������λ������״̬����Ϊ����
//        I2C1STATbits.IWCOL = 0;
//        //        i2c_address_restart = 0;
//        //�Ƿ���Ҫ�������
//        return;
//    }
//    /* Handle the correct i2c state */
//    switch (i2c1_state) {
//        case S_MASTER_IDLE: /* In reset state, waiting for data to send */
//        {
//            if (i2c_bytes_left == 0) {//����������ݲ�Ϊ0�Ļ�
//                //                I2C1CONbits.SEN = 1; // ������������
//                //            } else {
//                I2C1CONbits.SEN = 1; // ������������
//                i2c_operatcode = i2c_buf.operatcode; //��ֵ������
//                i2c_address = i2c_buf.address; //��ֵ��ַ
//                i2c_bytes_left = i2c_buf.length; //��ֵ����
//                pi2c_buf_ptr = i2c_buf.pbuffer; //��ֵ���ݵ�ַ
//                i2c_flag = i2c_buf.flag; //���豸ѡ��͹���ģʽ����ֵ
//                i2c_IsResart = 0;
//                i2c1_state = S_MASTER_SEND_ADDR; //״̬����Ϊ���͵�ַ
//            }
//            break;
//        }
//        case S_MASTER_RESTART:
//        {
//            I2C1CONbits.RSEN = 1; // ������������
//            i2c_bytes_left = i2c_buf.length; //��ֵ����
//            i2c1_state = S_MASTER_SEND_ADDR; //״̬����Ϊ���͵�ַ
//            break;
//        }
//        case S_MASTER_SEND_ADDR:
//        {
//            if (!i2c_flag.F_IsSelectiveMode) {//��ʾ������ַ��ȡ���� && i2c_IsResart) {
//                if (i2c_flag.F_WriteOrRead) {//����Ƕ�ָ��=1����ô״̬����Ϊ��ַACK
//                    I2C1TRN = i2c_operatcode | 0x01;
//                    i2c1_state = S_MASTER_ACK_ADDR; //������
//                } else {
//                    I2C1TRN = i2c_operatcode;
//                    i2c1_state = S_MASTER_SEND_DATA; //״̬����Ϊ��������
//                }
//            } else if (!i2c_IsResart) {//�����������Ĳ����룬����ݲ��������һ���ֽڴ�������֮,��
//                I2C1TRN = i2c_operatcode;
//                i2c1_state = S_MASTER_SEND_ADDR_16BIT;
//            } else {//���Ǹ�����ַ��д���ݵĺ���
//                if (i2c_flag.F_WriteOrRead) {//����Ƕ�ָ��=1����ô״̬����Ϊ��ַACK
//                    I2C1TRN = i2c_operatcode | 0x01;
//                    i2c1_state = S_MASTER_ACK_ADDR; //������                    
//                } else {
//                    I2C1TRN = i2c_operatcode;
//                    i2c1_state = S_MASTER_SEND_DATA; //״̬����Ϊ��������
//                }
//            }
//            break;
//        }
//        case S_MASTER_SEND_ADDR_16BIT:
//        {
//            if (I2C1STATbits.ACKSTAT) {//�����⵽�ϴ�NACK
//                I2C1STATbits.ACKSTAT = 0; //��λACK
//                I2C1CONbits.PEN = 1; // ����ֹͣ���� 
//                IFS1bits.MI2C1IF = 0; //�����־
//                i2c1_state = S_MASTER_Fail; //״̬����λ����
//            } else {
//                if (i2c_flag.F_Is16bitsDevice) {
//                    i2c_flag.F_Is16bitsDevice = 0;
//                    I2C1TRN = (uint8_t) (i2c_address >> 8); //����16λ�ߵ�ַ 
//                    i2c1_state = S_MASTER_SEND_ADDR_16BIT;
//                    //                    break;
//                } else {
//                    I2C1TRN = (uint8_t) (i2c_address & 0x00FF); //����16λ�͵�ַ 
//                    if (i2c_flag.F_WriteOrRead)//����Ƕ�ȡָ��Ļ�
//                    {
//                        i2c_IsResart = 1;
//                        //                        I2C1CONbits.RSEN = 1; // ������������
//                        i2c_operatcode |= 0x01; //����ַ����Ϊ��ȡ
//                        i2c1_state = S_MASTER_RESTART;
//                    } else
//                        i2c1_state = S_MASTER_SEND_DATA;
//                }
//            }
//            break;
//        }
//        case S_MASTER_SEND_DATA:
//        {
//            if (I2C1STATbits.ACKSTAT) {//�����⵽�ϴ�NACK
//                I2C1STATbits.ACKSTAT = 0; //��λACK
//                I2C1CONbits.PEN = 1; // ����ֹͣ���� 
//                IFS1bits.MI2C1IF = 0; //�����־
//                i2c1_state = S_MASTER_Fail; //״̬����λ����
//            } else {
//                if (i2c_bytes_left-- == 0U) {//�ж������Ƿ������
//                    I2C1CONbits.PEN = 1; // I2C STOP control bit.   
//                    IFS1bits.MI2C1IF = 0; //�����־
//                    i2c1_state = S_MASTER_SEND_STOP; //״̬����Ϊ����
//                } else {
//                    I2C1TRN = *pi2c_buf_ptr++; //��������
//                }
//                break;
//            }
//        }
//        case S_MASTER_ACK_ADDR://����Ƕ������Ļ���
//        {
//            if (I2C1STATbits.ACKSTAT) { //����ϴμ�⵽NACK
//                I2C1CONbits.PEN = 1; //����ֹͣ����
//                IFS1bits.MI2C1IF = 0; //�����־
//                i2c1_state = S_MASTER_Fail;
//                I2C1STATbits.ACKSTAT = 0; //��λACK
//            } else {
//                I2C1CONbits.RCEN = 1; //��������
//                i2c1_state = S_MASTER_ACK_RCV_DATA; //״̬Ϊ����Ϊ��������
//            }
//            break;
//        }
//        case S_MASTER_RCV_DATA:
//        {
//            i2c1_state = S_MASTER_ACK_RCV_DATA; //���ͽ�������ACK
//            I2C1CONbits.RCEN = 1; //ʹ�ܽ���
//            break;
//        }
//        case S_MASTER_ACK_RCV_DATA:
//        {
//            *pi2c_buf_ptr++ = I2C1RCV; //��������
//            if (--i2c_bytes_left) {
//                I2C1CONbits.ACKDT = 0; //����ACK
//                i2c1_state = S_MASTER_RCV_DATA; //��������
//            } else {
//
//                // Yes, it's the last byte.  Don't ack it
//                // Flag that we will nak the data
//                I2C1CONbits.ACKDT = 1; // I2C ACK data control bit.
//
//                //            I2C1_FunctionComplete();
//                i2c1_state = S_MASTER_RCV_STOP;
//                //                break; //�˳�����
//            }
//
//            // Initiate the acknowledge
//            I2C1CONbits.ACKEN = 1; // I2C ����ACK .
//            break;
//        }
//        case S_MASTER_RCV_STOP:
//        {
//            I2C1CONbits.ACKDT = 0;
//            I2C1CONbits.PEN = 1; // I2C STOP control bit.   
//            //            IFS1bits.MI2C1IF = 0; //�����־ 
//            i2c1_state = S_MASTER_Finish;
//            break;
//        }
//        case S_MASTER_SEND_STOP:
//        {
//            I2C1CONbits.PEN = 1; // I2C STOP control bit.   
//            //            IFS1bits.MI2C1IF = 0; //�����־ 
//            i2c1_state = S_MASTER_Finish;
//            break;
//        }
//        case S_MASTER_Finish:
//        {
//            i2c_operatcode = 0;
//            pi2c_buf_ptr = NULL;
//            i2c_address = 0;
//            i2c_bytes_left = 0;
//            i2c_flag.F_Is16bitsDevice = i2c_flag.F_IsSelectiveMode = i2c_flag.F_WriteOrRead = 0;
//            i2c_IsResart = 0; //�豸�Ƿ�����
//            break;
//        }

//        default:
//
//            // This case should not happen, if it does then
//            // terminate the transfer
//            //    i2c1_object.i2cErrors++;
//        {
//            I2C1CONbits.PEN = 1; // I2C STOP control bit.  
//            //            IFS1bits.MI2C1IF = 0; //�����־
//            //            i2c1_state = S_MASTER_IDLE;
//            break;
//        }
//    }

//    IFS1bits.MI2C1IF = 0; //����жϱ�־λ
//}



