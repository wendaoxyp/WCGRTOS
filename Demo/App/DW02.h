#ifndef _DW02_H_
#define _DW02_H_

#include <xc.h>
#include <stdint.h>
#include "UART2.h"

/*define GPRS communication IO*/
/*define GPRS Enable Port*/
#define GPRSENTris                  TRISDbits.TRISD4
#define GPRSWriteEN                 LATDbits.LATD4
/*define GPRS Link Port*/
#define GPRSLKTris                  TRISDbits.TRISD1
#define GPRSReadLK                  PORTDbits.RD1  

/*handle Enable port*/
#define GPRSEnable()                (GPRSWriteEN = 1) 
#define GPRSDisable()               (GPRSWriteEN = 0)    

/*GPRS send data*/
#define vGPRSSend(pucBuffer,uxBufferSize) vUART2Send(pucBuffer,uxBufferSize)
#define vGPRSSendString(uxString) vUART2SendString(uxString)

/*define GRRS find setting IP and Port*/
/*dailing*/
extern const char GPRSCmdDialing[];
extern const char GPRSCmdGetVersion[];
extern const char GPRSVersion[];


#endif
