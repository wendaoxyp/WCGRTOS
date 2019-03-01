#include <string.h>

#include "Error.h"
#include "PCF8583.h"
#include "CheckData.h"
#include "LCD.h"

#if (UseFreeRTOSInError == 1) 
#include "FreeRTOS.h"
#endif
/*Storage in EepRom address*/
unsigned char ucErrorPointer;
/*protocal array*/
uint8_t ucProtocalArray[ErrorCodeProtocalLength];

/*************************************
Function: vErrorSaveInEEPRom 
Description: save data in eeprom
Input: void  
Output: void
 *************************************/
static void vErrorSaveInEEPRom(unsigned char *ucProtocal) {
    /*read last ucErrorPointer*/
    xCAT24ReadByte(ErrorCodePointerAddress, ucErrorPointer);
    /*wirte t4,t3,t2,t1,err_code in eeprom*/
    xCAT24WriteBytes(ucErrorPointer + ErrorCodeInitEEPRom, ucProtocal + 4, 5);
    /*upgrade ucErrorPointer*/
    ucErrorPointer++;
    ucErrorPointer = ucErrorPointer % ErrorCodeEEPRomLength;
    xCAT24WriteByte(ErrorCodePointerAddress, ucErrorPointer);
}

/*************************************
Function: vErrorGenarateProtocal 
Description: Genatate notify user error protocal 
Input: xErrorCode
Output: protocal length
 *************************************/
static uint8_t vErrorGenarateProtocal(ErrCode xErrorCode) {
    uint8_t ucGenarateSize;
    time_t tTimestamp;
    uint16_t usCRC16;
    unsigned int uiYear = 2015;

    /*copy protocal header,'W','C','G'*/
    strncpy((char*) ucProtocalArray, "WCG", 3);
    ucGenarateSize = 3;
    /*set protocal function code ,'W','C','G',0x04*/
    ucProtocalArray[ucGenarateSize] = 0x0E;
    ucGenarateSize += 1;
    /*get timestamp*/
    tTimestamp = tPCF8583ReadTime(&uiYear);
    /*set timestamp, 'W','C','G',0x04,t4,t3,t2,t1*/
    strncpy((char*) (ucProtocalArray + ucGenarateSize), ((char*) & tTimestamp), 4);
    ucGenarateSize += 4;
    /*set error code,'W','C','G',0x04,t4,t3,t2,t1,err_code*/
    ucProtocalArray[ucGenarateSize] = xErrorCode;
    ucGenarateSize += 1;
    /*get CRC,'W','C','G',0x04,t4,t3,t2,t1,err_code,CRCH,CRCL*/
    usCRC16 = uiCRC16Check(ucProtocalArray, 9);
    ucProtocalArray[ucGenarateSize++] = (uint8_t) (usCRC16 >> 8);
    ucProtocalArray[ucGenarateSize++] = (uint8_t) (usCRC16);
    /*write data*/
    vErrorSaveInEEPRom(ucProtocalArray);
    return ucGenarateSize;
}

/*************************************
Function: vErrorSendToUser 
Description: send protocal to user ,like 'W','C','G',0x04,t4,t3,t2,t1,err_code,CRCH,CRCL
Input: xErrorCode  
Output: void
 *************************************/
void vErrorSendToUser(ErrCode xErrorCode) {
#if (UseFreeRTOSInError == 1) 
    portENTER_CRITICAL();
#endif
    vErrorGenarateProtocal(xErrorCode);
    vErrorSend(ucProtocalArray);
#if (UseFreeRTOSInError == 1) 
    portEXIT_CRITICAL();
#endif
}

/*************************************
Function: vErrorPrintCode 
Description: print error code ,maybe show in lcd ,or to user,or both
Input: xErrorCode,usOutputSource
Output: void 
 *************************************/
void vErrorPrintCode(ErrCode xErrorCode, unsigned char usOutputSource) {
    switch (usOutputSource) {
        case OutputInLCD:
        {
            //            vLCDShowNums(xErrorCode, SEGHIDE);
            break;
        }
        case OutputToUser:
        {
            vErrorSendToUser(xErrorCode);
            break;
        }
        case OutputBoth:
        {
            //            vLCDShowNums(xErrorCode, SEGHIDE);
            vErrorSendToUser(xErrorCode);
            break;
        }
    }
}

