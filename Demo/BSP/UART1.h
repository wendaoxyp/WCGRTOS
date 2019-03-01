/* 
 * File:   RS485.h
 * Author: TURONG62
 *
 * Created on 2016年6月12日, 下午4:09
 */

#ifndef UART1_H
#define	UART1_H


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*use RS485 on UART1 ,set 1*/
#define USE_RS485_ON_UART1           (1)  
/*use buffer*/
#define USE_BUFFER_UART1             (1)
/*define Use freertos*/
#define UseFreeRTOSInUART1           (1)

/*define System Clock,use for set uart1 baudrate*/
#ifndef WCG_CLOCK_HZ
#define WCG_CLOCK_HZ                 (4000000L)
#endif
/*define uart1 baudrate*/
#ifndef UART1_BAUD_RATE
#define UART1_BAUD_RATE              (9600)
#endif

#if (USE_RS485_ON_UART1 == 1)
/*define RS485 Control Pin*/
#define RS485_CON1_TRIS               TRISBbits.TRISB10
#define RS485_CON1                    LATBbits.LATB10
#define RS485_CON1_ANS                ANSBbits.ANSB10
/*endif USE_RS485_ON_UART1*/
#endif
/*define RS485 Input*/
#define UART1_RX_TRIS                 TRISBbits.TRISB8
#define UART1_RX_ANS                  ANSBbits.ANSB8
/*define RS485 Output*/
#define UART1_TX_TRIS                 TRISBbits.TRISB9
#define UART1_TX                      LATBbits.LATB9
#define UART1_TX_ANS                     ANSBbits.ANSB9




#if (USE_BUFFER_UART1 == 1)
/*define buffer length*/
#define UART1_BUFFER_LENGTH          16
/*define buffer */
extern unsigned char ucUart1Buffer[UART1_BUFFER_LENGTH];
/*endif USE_BUFFER_UART1 */
#endif

/*RS485 mode */
#define RS485_SEND_MODE              true
#define RS485_RECEIVE_MODE           false

/*send char*/
#define vUART1SendChar(cChar)   vUART1Send(&cChar,1)

/*initialed UART1*/
extern void vUART1Init(void);
/*open uart1*/
extern void vUART1Open(void);
/*clost uart1*/
extern void vUART1Close(void);
/*send  data , length id ubBytes */
extern void vUART1Send(void* pucdata, uint8_t ucBytes);
/*send string*/
extern void vUART1SendString(void* pvParameter);
/*receive one bytes*/
extern bool bUART1Receive(int8_t *pcChar);
/*get buffer */
extern bool bUART1BufferRead(uint8_t *pucData);
/*Read UART receive Buffer by software*/
extern void vUART1RxGet4Byte(void);
#endif	/* RS485_H */

