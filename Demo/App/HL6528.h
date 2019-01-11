#ifndef HL6528_H
#define HL6528_H
#include <xc.h>
#include <stdint.h>
#include <stddef.h>
#include "UART2.h"
#include "SerialBuffer.h"
#include "Common.h"
#include "WCG.h"


#define PWRON_TRIS TRISDbits.TRISD6
#define PWRON LATDbits.LATD6
#define PWR_TRIS TRISDbits.TRISD7
#define PWR LATDbits.LATD7
#define RTS_TRIS TRISDbits.TRISD4
#define RTS LATDbits.LATD4
#define CTS_TRIS TRISDbits.TRISD5
#define CTS LATDbits.LATD5
#define DTR_TRIS TRISDbits.TRISD1
#define DTR LATDbits.LATD1
#define DSR_TRIS TRISFbits.TRISF1
#define DSR LATFbits.LATF1

#define GPRS_Init       0x10
#define GPRS_Start      0x11
#define GPRS_Dialing    0x12
#define GPRS_Set_Arg    0x13
#define GPRS_Connect    0x14
#define GPRS_ERR_Handle 0x15
#define GPRS_Opertion_OK        0x00
#define GPRS_Opreation_Fail     0xff
#define GPRS_D1_Fail    0x01
#define GPRS_CPIN_Fail  0x02
#define GPRS_CREG_Fail  0x03
#define GPRS_CFG_Fail   0x04
#define GPRS_CFG1_Fail  0x05
#define GPRS_START_Fail     0x06
#define GPRS_Connect_Fail   0x07


extern uint8_t HL6528_DialingIsERR(uint8_t);
extern void HL6528_Init(void);
extern void HL6528_Close(void);
extern void HL6528_GetIP_Port(void);
//extern void GPRS_Task(void);


#endif




