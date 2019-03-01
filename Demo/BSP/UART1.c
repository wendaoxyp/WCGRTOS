#include "UART1.h"


#if (UseFreeRTOSInUART1==1)

#include "FreeRTOS.h"
#include "queue.h"
#include "projdefs.h"
#include "LED.h"

extern xQueueHandle xQueueUart1Pressure;
#endif

#if (USE_BUFFER_UART1 == 1)
/*define buffer*/
uint8_t ucUart1Buffer[UART1_BUFFER_LENGTH];
/*define writepointer*/
static uint8_t ucUart1BufferWptr = 0;
/*define readpointer*/
static uint8_t ucUart1BufferRptr = 0;
#endif

/*set uart1 interrupt expect byte,determind receive protocal size,like 01 03 04 3E F4 00 00 B6 29*/
//static uint8_t ucUART1InterruptExpectByte = 9;

/*************************************
Function: vUART1Init
Description: 485ͨѶ��ʼ��
Input: �� 
Output: ��
 *************************************/
void vUART1Init(void) {
    /*���ƿ�����λ��� 485_CON*/
    UART1_TX_TRIS = 0;
    /*����Ϊ����*/
    UART1_RX_TRIS = 1;
#ifdef UART1_TX_ANS
    /*��������*/
    UART1_TX_ANS = 0;
#endif
#ifdef UART1_RX_ANS
    /*��������*/
    UART1_RX_ANS = 0;
#endif
#if (USE_RS485_ON_UART1 == 1)
    /*����Ϊ���*/
    RS485_CON1_TRIS = 0;
    /*��������*/
    RS485_CON1_ANS = 1;
#endif
    /*unlock PPS*/
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    /* RB9->UART1:U1TX*/
    RPOR4bits.RP9R = 0x03;
    /* RB8->UART1:U1RX*/
    RPINR18bits.U1RXR = 0x08;
    /*Lock PPS*/
    __builtin_write_OSCCONL(OSCCON | 0x40);
    /*ʹ�ܴ���*/
    U1MODEbits.UARTEN = 1;
    /*high baud rate*/
    U1MODEbits.BRGH = 1;
    /*set baud rate 1000000/9600/4-1,last value equal 0x0019*/
    U1BRG = WCG_CLOCK_HZ / UART1_BAUD_RATE / 4 - 1;
    /*����żУ��*/
    U1MODEbits.PDSEL = 00;
    /*1λֹͣλ*/
    U1MODEbits.STSEL = 0;
    /*����ģʽ�¼�������*/
    U1MODEbits.USIDL = 0;
    /*����״̬�¼�������*/
    U1MODEbits.WAKE = 1;
    /*ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������*/
    U1STAbits.UTXEN = 0;
    /*��4�������ַ����жϱ�־λ�� 1*/
    U1STAbits.URXISEL = 3;
    /* send buffer set zero*/
    U1TXREG = 0;
    /*receive buffer set zero*/
    U1RXREG = 0;
    /*set receive interrupt priority is seven*/
    IPC2bits.U1RXIP = 7;
    /*��������ж�*/
    IFS0bits.U1RXIF = 0;
    /*���������ж�*/
    IEC0bits.U1RXIE = 1;
    /*set send interrupt priority is six*/
    IPC16bits.U1ERIP = 6;
    /*��������ж�*/
    IFS4bits.U1ERIF = 0;
    /*���������ж�*/
    IEC4bits.U1ERIE = 1;
    /*ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������*/
    U1STAbits.UTXEN = 1;
}

/*************************************
Function: vUART1Open
Description: open UART1
Input: �� 
Output: ��
 *************************************/
void vUART1Open(void) {
    /*ʹ�ܴ���*/
    U1MODEbits.UARTEN = 1;
    /*ʹ�ܷ��� ������ʹ�ܴ��� �ڷ�������*/
    U1STAbits.UTXEN = 1;
    /*���������ж�*/
    _U1RXIE = 1;
}

/*************************************
Function: vUART1Close
Description: close UART1
Input: �� 
Output: ��
 *************************************/
void vUART1Close(void) {
    /*close�����ж�*/
    _U1RXIE = 0;
    /*disable send  */
    U1STAbits.UTXEN = 0;
    /*disable uart3*/
    U1MODEbits.UARTEN = 0;
}


#if (USE_RS485_ON_UART1 == 1)

/*************************************
Function: vSetRS485CON1
Description: set Rs485CON status,1:send mode;0:receive mode
Input: ���͵����� 
Output: 1:���ͳɹ�
 *************************************/
static void vSetRS485CON1(bool bSta) {
    /*maybe need delay*/
    /*set 1:send;set 0:receive */
    RS485_CON1 = bSta;
    /*maybe need delay*/
}
#endif

/*************************************
Function: vUART1Send
Description: send length of bytes data
Input: ucData,ucBytes
Output: ��
 *************************************/
void vUART1Send(void* ucData, uint8_t ucBytes) {
    uint8_t ucCount = 0;
    char * pcChar = (char*) ucData;
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART1 == 1)
    vSetRS485CON1(RS485_SEND_MODE);
#endif
    /*send data*/
    while (ucCount < ucBytes) {
        U1TXREG = *(pcChar + ucCount);
        while (!U1STAbits.TRMT);
        ucCount++;
    }
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART1 == 1)
    vSetRS485CON1(RS485_RECEIVE_MODE);
#endif
}

/*************************************
Function: vUART1SendString
Description: 485�����ַ���
Input: string address
Output: ��
 *************************************/
void vUART1SendString(void* pvParameter) {
    uint8_t ucBytes = 0;

    char * pcChar = (char*) pvParameter;
    /*get strings length*/
    ucBytes = strlen(pcChar);
    /*send string*/
    vUART1Send(pcChar, ucBytes);
}

/*************************************
Function: bUART1Receive 
Description: ��ȡ�����յ������ݣ���Ϊ4���ֽ�һ���жϣ����3���ֽ���Ҫִ�иú�����ȡ
Input: get char address
Output: bool true:get;false:not get
 *************************************/
bool bUART1Receive(int8_t *pcChar) {
    /*received 3 byte,don't have interrupt*/
    if (U1STAbits.URXDA) {
        *pcChar = U1RXREG;
        return true;
    }
    return false;
}

/*************************************
Function: vUART1BufferWrite 
Description: д���ݵ����λ�����
Input: void 
Output: ��
 *************************************/
static void vUART1BufferWrite(void) {
    uint8_t tmp;
    /*������������� д���ٶȱȶ����ٶȿ�*/
    if (ucUart1BufferWptr == (ucUart1BufferRptr - 1)) {
        tmp = U1RXREG; //����������ݣ�����
        return;
    }
    ucUart1Buffer[ucUart1BufferWptr] = U1RXREG;
    ucUart1BufferWptr++;
    ucUart1BufferWptr = ucUart1BufferWptr % UART1_BUFFER_LENGTH;
}

/*************************************
Function:  bUART1BufferRead
Description: �����λ�����
Input: ���ݵ�ַ 
Output: 1����ȡ�ɹ���0����ȡʧ��
 *************************************/
bool bUART1BufferRead(uint8_t *pucData) {
    if (ucUart1BufferRptr == ucUart1BufferWptr) {
        /*д����������FIFO�������û���������������û��*/
        if (U1STAbits.OERR)
            U1STAbits.OERR = 0;
        return 0;
    }
    *pucData = ucUart1Buffer[ucUart1BufferRptr];
    ucUart1BufferRptr++;
    ucUart1BufferRptr = ucUart1BufferRptr % UART1_BUFFER_LENGTH;
    return 1;
}

/*************************************
Function: usUART1GetBufferSize 
Description: uart1 vaild buffer size
Input: void
Output: length
 *************************************/
static unsigned int usUART1GetBufferSize(void) {
    unsigned int usBufferWriteLength;

    usBufferWriteLength = ucUart1BufferWptr;
    if (ucUart1BufferWptr < ucUart1BufferRptr)
        usBufferWriteLength += UART1_BUFFER_LENGTH;

    return usBufferWriteLength - ucUart1BufferRptr;
}

/*************************************
Function: vUART1RxGet4Byte 
Description: uart1 get data (no interrupt)
Input: void
Output: void
 *************************************/
void vUART1RxGet4Byte(void) {
    unsigned char ucCount;
    for (ucCount = 0; ucCount < 4; ucCount++) {
        /*û�н��յ�*/
        if (U1STAbits.URXDA)
            vUART1BufferWrite();
    }
}

/*************************************
Function: _U1RXInterrupt 
Description: uart1 receive interrupt
Input: void
Output: void
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
#if (UseFreeRTOSInUART1 == 1)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif
    vUART1RxGet4Byte();
#if (UseFreeRTOSInUART1 == 1)
    if (usUART1GetBufferSize() >= 8) {
        xQueueSendFromISR(xQueueUart1Pressure, ucUart1Buffer, &xHigherPriorityTaskWoken);
        //        if (xHigherPriorityTaskWoken)
        //            portYIELD();
    }
    if (xHigherPriorityTaskWoken != pdFALSE) {
        portYIELD();
    }

#endif
    LEDGreenON;
    _U1RXIF = 0;
}

/*************************************
Function: UART1�����ն�
Description: ��
Input: �� 
Output: ��
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U1ErrInterrupt(void) {
    LEDRedON;
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

