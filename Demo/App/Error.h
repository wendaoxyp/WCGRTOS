#ifndef _ERROR_H_
#define _ERROR_H_


#include <stdint.h>
#include <stdbool.h>

#include "CAT24C512.h"
#include "UART3.h"

typedef unsigned char ErrCode;

/*use freertos set 1*/
#define UseFreeRTOSInError                            (1)

/*Get Pressure error*/
#define ErrorNoError                                  0x00
/*Send pressure protocal not get Ack,maybe disconnect,Uart1 no get data*/
#define ErrorGetPressureValueNoAck                    0x01
/*loss byte,need 9bytes,but get 8bytes*/
#define ErrorGetPressureValueLossBytes                0x02
/*Calc CRC is not right*/
#define ErrorGetPressureValueCRCNoRight               0x03
/*Calc CRC is not right*/
#define ErrorGetPressureValueInvaildHead              0x04



#define ErrorCodeInitEEPRom                           0xFF80
#define ErrorCodeEEPRomLength                         20   
#define ErrorCodePointerAddress                       0xFFF5

/*define error code output source */
#define OutputInLCD                                   0
#define OutputToUser                                  1
#define OutputBoth                                    2

/*define Protocal length */
#define ErrorCodeProtocalLength                       12

/*error send by uart3*/
#define vErrorSend(pucString)  \
    vUART3Send(pucString, ErrorCodeProtocalLength)
/*print error code*/
extern void vErrorPrintCode(ErrCode xErrorCode, unsigned char usOutputSource);
/*send user error detail*/
extern void vErrorSendToUser(ErrCode xErrorCode);
#endif
