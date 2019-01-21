#include "UART3.h"


#if (UseFreeRTOSInUART3==1)

#include "FreeRTOS.h"
#include "queue.h"
#include "projdefs.h"
#include "LED.h"

extern xQueueHandle xQueueUart3User;
#endif

#if (USE_BUFFER_UART3 == 1)
/*define buffer*/
uint8_t ucUart3Buffer[UART3_BUFFER_LENGTH];
/*define writepointer*/
static uint8_t ucUart3BufferWptr = 0;
/*define readpointer*/
static uint8_t ucUart3BufferRptr = 0;
#endif

/*set uart3 interrupt expect byte*/
static uint8_t ucUART3InterruptExpectByte;

void vUART3Init(void) {
    /*设置为输入*/
    UART3_RX_TRIS = 1;
    /*设置为输出*/
    UART3_TX_TRIS = 0;
#ifdef UART3_RX_ANS
    /*设置为数字端口*/
    UART3_RX_ANS = 0;
#endif
#ifdef UART3_TX_ANS
    /*设置为数字端口*/
    UART3_TX_ANS = 0;
#endif
#if (USE_RS485_ON_UART3 == 1)
    /*设置为输入*/
    RS485_CON3_TRIS = 0;
    /*设置为数字端口*/
    RS485_CON3_ANS = 0;
#endif
    /*unlock PPS*/
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    /* RG7->UART3:U3TX*/
    RPOR13bits.RP26R = 0x1C;
    /* RG8->UART3:U3RX*/
    RPINR17bits.U3RXR = 0x13;
    /*Lock PPS*/
    __builtin_write_OSCCONL(OSCCON | 0x40);
    /*波特率使用标准模式1:16*/
    U3MODEbits.BRGH = 1;
    /*19200:103*/
    U3BRG = WCG_CLOCK_HZ / UART3_BAUD_RATE / 4 - 1;
    /*无奇偶校验*/
    U3MODEbits.PDSEL = 0;
    /*1位停止位*/
    U3MODEbits.STSEL = 0;
    /*使能串口*/
    U3MODEbits.UARTEN = 1;
    /*有 4 个数据字符，中断标志位置 1*/
    U3STAbits.URXISEL = 3;
    /*清除接收flag  */
    IFS5bits.U3RXIF = 0;
    /*set priority is seven*/
    IPC20bits.U3RXIP = 7;
    /*开启接收中断*/
    IEC5bits.U3RXIE = 1;
    /*清除error接收flag*/
    IFS5bits.U3ERIF = 0;
    /*set priority is six*/
    IPC20bits.U3ERIP = 6;
    /*开启接收中断*/
    IEC5bits.U3ERIE = 1;
    /*使能发送 必须先使能串口 在发送数据*/
    U3STAbits.UTXEN = 1;
}

/*************************************
Function: vUART3Open
Description: open UART3
Input: 无 
Output: 无
 *************************************/
void vUART3Open(void) {
    /*使能串口*/
    U3MODEbits.UARTEN = 1;
    /*使能发送 必须先使能串口 在发送数据*/
    U3STAbits.UTXEN = 1;
    /*开启接收中断*/
    IEC5bits.U3RXIE = 1;
}

/*************************************
Function: vUART3Close
Description: close UART3
Input: 无 
Output: 无
 *************************************/
void vUART3Close(void) {
    /*close接收中断*/
    IEC5bits.U3RXIE = 0;
    /*disable send  */
    U3STAbits.UTXEN = 0;
    /*disable uart3*/
    U3MODEbits.UARTEN = 0;
}
#if (USE_RS485_ON_UART3 == 1)

/*************************************
Function: vSetRS485CON3
Description: set Rs485CON3 status,1:send mode;0:receive mode
Input: 发送的数据 
Output: 1:发送成功
 *************************************/
static void vSetRS485CON3(bool bSta) {
    /*maybe need delay*/
    /*set 1:send;set 0:receive */
    RS485_CON3 = bSta;
    /*maybe need delay*/
}
#endif

/*************************************
Function: vUART3Send
Description: send length of bytes data
Input: ucData,ucBytes
Output: 无
 *************************************/
void vUART3Send(void* ucData, uint8_t ucBytes) {
    uint8_t ucCount = 0;
    char * pcChar = (char*) ucData;
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART3 == 1)
    vSetRS485CON3(RS485_SEND_MODE);
#endif
    /*send data*/
    while (ucCount < ucBytes) {
        U3TXREG = *(pcChar + ucCount);
        while (!U3STAbits.TRMT);
        ucCount++;
    }
    /*use 485 need set mode*/
#if (USE_RS485_ON_UART3 == 1)
    vSetRS485CON3(RS485_RECEIVE_MODE);
#endif
}

/*************************************
Function: vUART3SendString
Description: 485发送字符串
Input: string address
Output: 无
 *************************************/
void vUART3SendString(void* dat) {
    uint8_t ucBytes = 0;

    char * pcChar = (char*) dat;
    /*get strings length*/
    ucBytes = strlen(pcChar);
    /*send string*/
    vUART3Send(pcChar, ucBytes);
}

/*************************************
Function: bUART3Receive 
Description: 获取最后接收到的数据，因为4个字节一次中断，最后3个字节需要执行该函数获取
Input: get char address
Output: bool true:get;false:not get
 *************************************/
bool bUART3Receive(int8_t *pcChar) {
    /*received 3 byte,don't have interrupt*/
    if (U3STAbits.URXDA) {
        *pcChar = U3RXREG;
        return true;
    }
    return false;
}

/*************************************
Function: vUART3BufferWrite 
Description: 写数据到环形缓冲区
Input: void 
Output: 无
 *************************************/
static void vUART3BufferWrite(void) {
    uint8_t tmp;
    /*如果缓冲区已满 写的速度比读的速度块*/
    if (ucUart3BufferWptr == (ucUart3BufferRptr - 1)) {
        tmp = U3RXREG; //将溢出的数据，丢弃
        return;
    }
    ucUart3Buffer[ucUart3BufferWptr] = U3RXREG;
    ucUart3BufferWptr++;
    ucUart3BufferWptr = ucUart3BufferWptr % UART3_BUFFER_LENGTH;
}

/*************************************
Function:  bUART3BufferRead
Description: 读环形缓冲区
Input: 数据地址 
Output: 1：读取成功，0：读取失败
 *************************************/
bool bUART3BufferRead(uint8_t *pucData) {
    if (ucUart3BufferRptr == ucUart3BufferWptr) {
        /*写数据满导致FIFO溢出，而没有清除，接受数据没有*/
        if (U3STAbits.OERR)
            U3STAbits.OERR = 0;
        return 0;
    }
    *pucData = ucUart3Buffer[ucUart3BufferRptr];
    ucUart3BufferRptr++;
    ucUart3BufferRptr = ucUart3BufferRptr % UART3_BUFFER_LENGTH;
    return 1;
}

/*************************************
Function: usUART3GetBufferSize 
Description: uart3 vaild buffer size
Input: void
Output: length
 *************************************/
unsigned int usUART3GetBufferSize(void) {
    unsigned int usBufferWriteLength;

    usBufferWriteLength = ucUart3BufferWptr;
    if (ucUart3BufferWptr < ucUart3BufferRptr)
        usBufferWriteLength += UART3_BUFFER_LENGTH;

    return usBufferWriteLength - ucUart3BufferRptr;
}

/*************************************
Function: vUART3RxGet4Byte 
Description: uart3 get data (no interrupt)
Input: void
Output: void
 *************************************/
void vUART3RxGet4Byte(void) {
    unsigned char ucCount;
    for (ucCount = 0; ucCount < 4; ucCount++) {
        /*没有接收到*/
        if (U3STAbits.URXDA)
            vUART3BufferWrite();
    }
}

/*************************************
Function: vUART3SetGetLength
Description: uart3 receive interrupt
Input: usExpectBytes
Output: void
 *************************************/
void vUART3SetGetLength(unsigned char usExpectBytes) {
    ucUART3InterruptExpectByte = usExpectBytes >> 2 << 2;
}

/*************************************
Function: _U3RXInterrupt 
Description: uart3 receive interrupt
Input: void
Output: void
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void) {
#if (UseFreeRTOSInUART3 == 1)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#endif
    vUART3RxGet4Byte();
#if (UseFreeRTOSInUART3 == 1)
    if (usUART3GetBufferSize() >= ucUART3InterruptExpectByte) {
        xQueueSendFromISR(xQueueUart3User, ucUart3Buffer, &xHigherPriorityTaskWoken);
        //        if (xHigherPriorityTaskWoken)
        //            portYIELD();
    }
    if (xHigherPriorityTaskWoken != pdFALSE) {
        portYIELD();
    }

#endif
    LEDGreenON;
    _U3RXIF = 0;
}

/*************************************
Function: UART3错误终端
Description: 无
Input: 无 
Output: 无
 *************************************/
void __attribute__((interrupt, no_auto_psv)) _U3ErrInterrupt(void) {
    LEDRedON;
    if (U3STAbits.OERR)
        U3STAbits.OERR = 0;
    if (U3STAbits.FERR) {//mark
        //        U3RXREG = U3RXREG;
        U3STAbits.FERR = 0;
    }
    if (U3STAbits.PERR)
        U3STAbits.PERR = 0;
    _U3ERIF = 0;

}

