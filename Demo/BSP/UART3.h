#ifndef UART3_H
#define UART3_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*use RS485 on UART3 ,set 1*/
#define USE_RS485_ON_UART3           (1)   
/*use buffer*/
#define USE_BUFFER_UART3             (1)
/*define Use freertos*/
#define UseFreeRTOSInUART3           (1)

/*define System Clock,use for set uart1 baudrate*/
#ifndef WCG_CLOCK_HZ
#define WCG_CLOCK_HZ                 (4000000L)
#endif
/*define uart1 baudrate*/
#ifndef UART3_BAUD_RATE
#define UART3_BAUD_RATE              (19200)
#endif

#if (USE_RS485_ON_UART3 == 1)
/*define RS485 Control Pin*/
#define RS485_CON3_TRIS               TRISEbits.TRISE6
#define RS485_CON3                    LATEbits.LATE6
#define RS485_CON3_ANS                ANSEbits.ANSE6
/*endif USE_RS485_ON_UART3*/
#endif
/*define RS485 Input*/
#define UART3_RX_TRIS                 TRISGbits.TRISG8
#define UART3_RX_ANS                  ANSGbits.ANSG8
/*define RS485 Output*/
#define UART3_TX_TRIS                 TRISGbits.TRISG7
#define UART3_TX                      LATGbits.LATG7
#define UART3_TX_ANS                  ANSGbits.ANSG7



#if (USE_BUFFER_UART3 == 1)
/*define buffer length*/
#define UART3_BUFFER_LENGTH          128
/*define buffer */
extern unsigned char ucUart3Buffer[UART3_BUFFER_LENGTH];
/*endif USE_BUFFER_UART3 */
#endif

/*RS485 mode */
#ifndef RS485_SEND_MODE
#define RS485_SEND_MODE              true
#endif  
#ifndef RS485_RECEIVE_MODE
#define RS485_RECEIVE_MODE           false
#endif

/*send char*/
#define vUART3SendChar(cChar)   vUART3Send(&cChar,1)

/*initialed UART3*/
extern void vUART3Init(void);
/*open uart1*/
extern void vUART3Open(void);
/*clost uart1*/
extern void vUART3Close(void);
/*send  data , length id ubBytes */
extern void vUART3Send(void* pucdata, uint8_t ucBytes);
/*send string*/
extern void vUART3SendString(void* pvParameter);
/*receive one bytes*/
extern bool bUART3Receive(int8_t *pcChar);
/*get buffer */
extern bool bUART3BufferRead(uint8_t *pucData);
/*Read UART receive Buffer by software*/
extern void vUART3RxGet4Byte(void);
/*set interrupt need receive bytes*/
extern void vUART3SetGetLength(unsigned char usExpectBytes);
#endif

