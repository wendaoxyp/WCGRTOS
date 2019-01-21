#include "UART2.h"

#if (UseFreeRTOSInUART2==1)

#include "FreeRTOS.h"
#include "queue.h"
#include "projdefs.h"
#include "LED.h"

extern xQueueHandle xQueueUart2GPRS;
#endif

#if (USE_BUFFER_UART2 == 1)
/*define buffer*/
uint8_t ucUart2Buffer[UART2_BUFFER_LENGTH];
/*define writepointer*/
static uint8_t ucUart2BufferWptr = 0;
/*define readpointer*/
static uint8_t ucUart2BufferRptr = 0;
#endif
/*set uart2 interrupt expect byte*/
static uint8_t ucUART2InterruptExpectByte;

void vUART2Init(void) {
    /*����Ϊ����*/
    UART2_RX_TRIS = 1;
    /*����Ϊ���*/
    UART2_TX_TRIS = 0;
    /*����Ϊ���ֶ˿�*/
#ifdef UART2_RX_ANS
    UART2_RX_ANS = 0;
#endif
    /*����Ϊ���ֶ˿�*/
#ifdef  UART2_TX_ANS 
    UART2_TX_ANS = 0;
#endif 
#if (USE_RS485_ON_UART2 == 1)
    /*����Ϊ����*/
    RS485_CON2_TRIS = 0;
    /*����Ϊ���ֶ˿�*/
    RS485_CON2_ANS = 0;
#endif
    /*unlock PPS*/
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    /* RD3->UART2:U2TX*/
    RPOR11bits.RP22R = 0x05;
    /* RD2->UART2:U2RX*/
    RPINR19bits.U2RXR = 0x17;
    /*Lock PPS*/
    __builtin_write_OSCCONL(OSCCON | 0x40);
    /*������ʹ�ñ�׼ģʽ1:16*/
    U2MODEbits.BRGH = 1;
    /*set baud rate*/
    U2BRG = WCG_CLOCK_HZ / UART2_BAUD_RATE / 4 - 1;
    /*����żУ��*/
    U2MODEbits.PDSEL = 0;
    /*1λֹͣλ*/
    U2MODEbits.STSEL = 0;
    /*ʹ�ܴ���*/
    U2MODEbits.UARTEN = 1;
    /*ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������*/
    U2STAbits.UTXEN = 1;
    /*�� 4 �������ַ����жϱ�־λ�� 1*/
    U2STAbits.URXISEL = 3;
    /*set receive interrupt priority is seven */
    IPC7bits.U2RXIP = 7;
    /*set err receive interrupt priority is six*/
    IPC16bits.U2ERIP = 6;
    /*���������ж�*/
    IEC1bits.U2RXIE = 1;
    /*�������flag*/
    IFS1bits.U2RXIF = 0;
    /*�����ж�*/
    IEC4bits.U2ERIE = 1;
    /*clear flag*/
    IFS4bits.U2ERIF = 0;
}

/*************************************
Function: vUART2Open
Description: open UART2
Input: �� 
Output: ��
 *************************************/
void vUART2Open(void) {
    /*ʹ�ܴ���*/
    U2MODEbits.UARTEN = 1;
    /*ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������*/
    U2STAbits.UTXEN = 1;
    /*���������ж�*/
    _U2RXIE = 1;
}

/*************************************
Function: vUART2Close
Description: close UART2
Input: �� 
Output: ��
 *************************************/
void vUART2Close(void) {
    /*close�����ж�*/
    _U2RXIE = 0;
    /*disable send  */
    U2STAbits.UTXEN = 0;
    /*disable uart3*/
    U2MODEbits.UARTEN = 0;
}
#if (USE_RS485_ON_UART2 == 1)

/*************************************
Function: vSetRS485CON2
Description: set Rs485CON3 status,1:send mode;0:receive mode
Input: ���͵����� 
Output: 1:���ͳɹ�
 *************************************/
static void vSetRS485CON2(bool bSta) {
    /*maybe need delay*/
    /*set 1:send;set 0:receive */
    RS485_CON2 = bSta;
    /*maybe need delay*/
}
#endif

/*************************************
Function: vUART2Send
Description: send length of bytes data
Input: ucData,ucBytes
Output: ��
 *************************************/
void vUART2Send(void* ucData, uint8_t ucBytes) {
    uint8_t ucCount = 0;
    char * pcChar = (char*) ucData;
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART2 == 1)
    vSetRS485CON2(RS485_SEND_MODE);
#endif
    /*send data*/
    while (ucCount < ucBytes) {
        U2TXREG = *(pcChar + ucCount);
        while (!U2STAbits.TRMT);
        ucCount++;
    }
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART2 == 1)
    vSetRS485CON2(RS485_RECEIVE_MODE);
#endif
}

/*************************************
Function: vUART2SendString
Description: 485�����ַ���
Input: string address
Output: ��
 *************************************/
void vUART2SendString(void* dat) {
    uint8_t ucBytes = 0;

    char * pcChar = (char*) dat;
    /*get strings length*/
    ucBytes = strlen(pcChar);
    /*send string*/
    vUART2Send(pcChar, ucBytes);
}

/*************************************
Function: bUART2Receive 
Description: ��ȡ�����յ������ݣ���Ϊ4���ֽ�һ���жϣ����3���ֽ���Ҫִ�иú�����ȡ
Input: get char address
Output: bool true:get;false:not get
 *************************************/
bool bUART2Receive(int8_t *pcChar) {
    /*received 3 byte,don't have interrupt*/
    if (U2STAbits.URXDA) {
        *pcChar = U2RXREG;
        return true;
    }
    return false;
}

/*************************************
Function: vUART2BufferWrite 
Description: д���ݵ����λ�����
Input: void 
Output: ��
 *************************************/
static void vUART2BufferWrite(void) {
    uint8_t tmp;
    /*������������� д���ٶȱȶ����ٶȿ�*/
    if (ucUart2BufferWptr == (ucUart2BufferRptr - 1)) {
        tmp = U2RXREG; //����������ݣ�����
        return;
    }
    ucUart2Buffer[ucUart2BufferWptr] = U2RXREG;
    ucUart2BufferWptr++;
    ucUart2BufferWptr = ucUart2BufferWptr % UART2_BUFFER_LENGTH;
}

/*************************************
Function:  bUART2BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool bUART2BufferRead(uint8_t *pucData) {
    if (ucUart2BufferRptr == ucUart2BufferWptr) {
        /*д����������FIFO�������û���������������û��*/
        if (U2STAbits.OERR)
            U2STAbits.OERR = 0;
        return 0;
    }
    *pucData = ucUart2Buffer[ucUart2BufferRptr];
    ucUart2BufferRptr++;
    ucUart2BufferRptr = ucUart2BufferRptr % UART2_BUFFER_LENGTH;
    return 1;
}

/*************************************
Function: usUART2GetBufferSize 
Description: uart2 vaild buffer size
Input: void
Output: length
 *************************************/
unsigned int usUART2GetBufferSize(void) {
    unsigned int usBufferWriteLength;

    usBufferWriteLength = ucUart2BufferWptr;
    if (ucUart2BufferWptr < ucUart2BufferRptr)
        usBufferWriteLength += UART2_BUFFER_LENGTH;

    return usBufferWriteLength - ucUart2BufferRptr;
}

/*************************************
Function: vUART2RxGet4Byte 
Description: uart2 get data (no interrupt)
Input: void
Output: void
 *************************************/
void vUART2RxGet4Byte(void) {
    unsigned char ucCount;
    for (ucCount = 0; ucCount < 4; ucCount++) {
        /*û�н��յ�*/
        if (U2STAbits.URXDA)
            vUART2BufferWrite();
    }
}

/*************************************
Function: vUART2SetGetLength
Description: uart2 receive interrupt
Input: usExpectBytes
Output: void
 *************************************/
void vUART2SetGetLength(unsigned char usExpectBytes) {
    ucUART2InterruptExpectByte = usExpectBytes >> 2 << 2;
}

/*************************************
Function: _U2RXInterrupt 
Description: uart2 receive interrupt
Input: void
Output: void
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
#if (UseFreeRTOSInUART2 == 1)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif
    vUART2RxGet4Byte();
#if (UseFreeRTOSInUART2 == 1)
    if (usUART2GetBufferSize() >= ucUART2InterruptExpectByte) {
        xQueueSendFromISR(xQueueUart2GPRS, ucUart2Buffer, &xHigherPriorityTaskWoken);
        //        if (xHigherPriorityTaskWoken)
        //            portYIELD();
    }
    if (xHigherPriorityTaskWoken != pdFALSE) {
        portYIELD();
    }

#endif
    LEDGreenON;
    _U2RXIF = 0;
}

/*************************************
Function: UART2�����ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U2ErrInterrupt(void) {
    LEDRedON;
    if (U2STAbits.OERR)
        U2STAbits.OERR = 0;
    if (U2STAbits.FERR) {//mark
        //        U2RXREG = U2RXREG;
        U2STAbits.FERR = 0;
    }
    if (U2STAbits.PERR)
        U2STAbits.PERR = 0;
    _U2ERIF = 0;

}







