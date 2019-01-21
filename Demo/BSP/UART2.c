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
    /*设置为输入*/
    UART2_RX_TRIS = 1;
    /*设置为输出*/
    UART2_TX_TRIS = 0;
    /*设置为数字端口*/
#ifdef UART2_RX_ANS
    UART2_RX_ANS = 0;
#endif
    /*设置为数字端口*/
#ifdef  UART2_TX_ANS 
    UART2_TX_ANS = 0;
#endif 
#if (USE_RS485_ON_UART2 == 1)
    /*设置为输入*/
    RS485_CON2_TRIS = 0;
    /*设置为数字端口*/
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
    /*波特率使用标准模式1:16*/
    U2MODEbits.BRGH = 1;
    /*set baud rate*/
    U2BRG = WCG_CLOCK_HZ / UART2_BAUD_RATE / 4 - 1;
    /*无奇偶校验*/
    U2MODEbits.PDSEL = 0;
    /*1位停止位*/
    U2MODEbits.STSEL = 0;
    /*使能串口*/
    U2MODEbits.UARTEN = 1;
    /*使能发送 必须先使能串口 在发送数据*/
    U2STAbits.UTXEN = 1;
    /*有 4 个数据字符，中断标志位置 1*/
    U2STAbits.URXISEL = 3;
    /*set receive interrupt priority is seven */
    IPC7bits.U2RXIP = 7;
    /*set err receive interrupt priority is six*/
    IPC16bits.U2ERIP = 6;
    /*开启接收中断*/
    IEC1bits.U2RXIE = 1;
    /*清除接收flag*/
    IFS1bits.U2RXIF = 0;
    /*开启中断*/
    IEC4bits.U2ERIE = 1;
    /*clear flag*/
    IFS4bits.U2ERIF = 0;
}

/*************************************
Function: vUART2Open
Description: open UART2
Input: 无 
Output: 无
 *************************************/
void vUART2Open(void) {
    /*使能串口*/
    U2MODEbits.UARTEN = 1;
    /*使能发送 必须先使能串口 在发送数据*/
    U2STAbits.UTXEN = 1;
    /*开启接收中断*/
    _U2RXIE = 1;
}

/*************************************
Function: vUART2Close
Description: close UART2
Input: 无 
Output: 无
 *************************************/
void vUART2Close(void) {
    /*close接收中断*/
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
Input: 发送的数据 
Output: 1:发送成功
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
Output: 无
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
Description: 485发送字符串
Input: string address
Output: 无
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
Description: 获取最后接收到的数据，因为4个字节一次中断，最后3个字节需要执行该函数获取
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
Description: 写数据到环形缓冲区
Input: void 
Output: 无
 *************************************/
static void vUART2BufferWrite(void) {
    uint8_t tmp;
    /*如果缓冲区已满 写的速度比读的速度块*/
    if (ucUart2BufferWptr == (ucUart2BufferRptr - 1)) {
        tmp = U2RXREG; //将溢出的数据，丢弃
        return;
    }
    ucUart2Buffer[ucUart2BufferWptr] = U2RXREG;
    ucUart2BufferWptr++;
    ucUart2BufferWptr = ucUart2BufferWptr % UART2_BUFFER_LENGTH;
}

/*************************************
Function:  bUART2BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool bUART2BufferRead(uint8_t *pucData) {
    if (ucUart2BufferRptr == ucUart2BufferWptr) {
        /*写数据满导致FIFO溢出，而没有清除，接受数据没有*/
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
        /*没有接收到*/
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
Function: UART2错误终端
Description: 无
Input: 无 
Output: 无
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







