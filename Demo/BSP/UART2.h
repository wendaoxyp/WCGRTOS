#ifndef UART2_H
#define UART2_H


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*use RS485 on UART2 ,set 1*/
#define USE_RS485_ON_UART2           (0)  
/*use buffer*/
#define USE_BUFFER_UART2             (1)
/*define Use freertos*/
#define UseFreeRTOSInUART2           (1)

/*define System Clock,use for set uart1 baudrate*/
#ifndef WCG_CLOCK_HZ
#define WCG_CLOCK_HZ                 (4000000L)
#endif
/*define uart1 baudrate*/
#ifndef UART2_BAUD_RATE
#define UART2_BAUD_RATE              (9600)
#endif

#if (USE_RS485_ON_UART2 == 1)
/*define RS485 Control Pin*/
#define RS485_CON2_TRIS               TRISHbits.TRISH10
#define RS485_CON2                    LATHbits.LATH10
#define RS485_CON2_ANS                ANSHbits.ANSH10
/*endif USE_RS485_ON_UART2*/
#endif
/*define RS485 Input*/
#define UART2_RX_TRIS                 TRISDbits.TRISD2 
/*#define UART2_RX_ANS                  ANSDbits.ANSD2*/
/*define RS485 Output*/
#define UART2_TX_TRIS                 TRISDbits.TRISD3
#define UART2_TX                      LATDbits.LATD3
/*#define UART2_TX_ANS                  ANSDbits.ANSD3*/


#if (USE_BUFFER_UART2 == 1)
/*define buffer length*/
#define UART2_BUFFER_LENGTH          16
/*define buffer */
extern unsigned char ucUart2Buffer[UART2_BUFFER_LENGTH];
/*endif USE_BUFFER_UART2 */
#endif

/*RS485 mode */
#define RS485_SEND_MODE              true
#define RS485_RECEIVE_MODE           false

/*send char*/
#define vUART2SendChar(cChar)   vUART2Send(&cChar,1)

/*initialed UART2*/
extern void vUART2Init(void);
/*open uart1*/
extern void vUART2Open(void);
/*clost uart1*/
extern void vUART2Close(void);
/*send  data , length id ubBytes */
extern void vUART2Send(void* pucdata, uint8_t ucBytes);
/*send string*/
extern void vUART2SendString(void* pvParameter);
/*receive one bytes*/
extern bool bUART2Receive(int8_t *pcChar);
/*get buffer */
extern bool bUART2BufferRead(uint8_t *pucData);
/*Read UART receive Buffer by software*/
extern void vUART2RxGet4Byte(void);
/*set interrupt need receive bytes*/
extern void vUART2SetGetLength(unsigned char usExpectBytes);
#endif

