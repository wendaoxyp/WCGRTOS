#include "GPRSProtocol.h"
#include "PCF8583.h"
#include "Common.h"
#include "WCGArg.h"
#include "CheckData.h"
#include "WCGDeBug.h"


/*define const*/
#define FrameHead 0x3E
const unsigned char DeviceIdentification[8] = {0x00, 0x01, 0x23, 0x45, 0x67, 0x89, 0x01, 0x23};
const unsigned char DeviceLocationNumber[8] = {0xFF, 0xFF, 0xFF, 0x01, 0x23, 0x45, 0x67, 0x89};
const unsigned char DeviceUserID[6] = {0x01, 0x23, 0x45, 0x67, 0x89, 0x10};

/*************************************
 * Function: vGPRSPacketDataToGroup
 * Description: get Group Data
 * Input: sGroupProtocal* sGroPro, unsigned char *usTime, float fPressure
 * Output: void
 * notice: 
 *************************************/
void vGPRSPacketDataToGroup(sGroupProtocal* sGroPro, unsigned char *usTime, float fPressure) {
    CopyDat(sGroPro->RecordTime, usTime, 6);
    sGroPro->Vb = 0;
    sGroPro->Vm = 0;
    sGroPro->Qb = 0;
    sGroPro->Qm = 0;
    sGroPro->Temperature = 0;
    sGroPro->Pressure = fPressure;
    sGroPro->StatuWord = 0;
    ClearDat(sGroPro->AlarmWord, 0, 3);
    sGroPro->Surplus = 0;
}

/*************************************
 * Function: vGPRSGroupToChar
 * Description: get Group Data to char
 * Input: sGroupProtocal* sGroPro,unsigned char *ucGroup
 * Output: void
 * notice: 
 *************************************/
void vGPRSGroupToChar(sGroupProtocal* sGroPro, unsigned char *ucGroup) {
    unsigned char ucTempGroup[60];
    unsigned char ucOffset = 0;
    /*get group data*/
    CopyDat(ucTempGroup, sGroPro->RecordTime, 6);
    ucOffset += 6;
    DoubleToChar(&(sGroPro->Vb), ucTempGroup + ucOffset);
    ucOffset += 8;
    DoubleToChar(&(sGroPro->Vm), ucTempGroup + ucOffset);
    ucOffset += 8;
    FloatToChar(&(sGroPro->Qb), ucTempGroup + ucOffset);
    ucOffset += 4;
    FloatToChar(&(sGroPro->Qm), ucTempGroup + ucOffset);
    ucOffset += 4;
    FloatToChar(&(sGroPro->Temperature), ucTempGroup + ucOffset);
    ucOffset += 4;
    FloatToChar(&(sGroPro->Pressure), ucTempGroup + ucOffset);
    ucOffset += 4;
    ucTempGroup[ucOffset++] = sGroPro->StatuWord;
    CopyDat(ucTempGroup + ucOffset, sGroPro->AlarmWord, 3);
    ucOffset += 3;
    CopyDat(ucTempGroup + ucOffset, (unsigned char *) &sGroPro->Surplus, 8);
    ucOffset += 8;
    /*one Group is 50 bytes*/
    CopyDat(ucGroup, ucTempGroup, 50);
}

/*************************************
 * Function: vGPRSPacketData1InFrame
 * Description: packet data1 in Frame ,data1 like ucAllFrameNumbers,ucCurrentFrameID
 * Input: ucAllFrameNumbers,ucCurrentFrameID
 * Output: void
 * notice: 
 *************************************/
void vGPRSPacketData1InFrame(sFrameProtocal*sFraPro) {
    unsigned char ucCurrentTime[7];

    sFraPro->FrameID = 0x3E;
    /*function code*/
    sFraPro->FunctionCode = 0x08;
    /*device id*/
    ClearDat(sFraPro->DeviceID, 0, 8);
    /*device id*/
    ClearDat(sFraPro->LocationNumber, 0, 8);
    /*user id*/
    ClearDat(sFraPro->UserID, 0, 8);
    /*get current time*/
    vWCGGetCurrentTime(ucCurrentTime);
    CopyDat(sFraPro->SendTime, ucCurrentTime + 1, 6);

}

/*************************************
 * Function: vGPRSPacketGroupInFrame
 * Description: packet Group in Frame 
 * Input: psGroPro,ucGroupNum
 * Output: void
 * notice: 
 *************************************/
void vGPRSPacketGroupInFrame(sFrameProtocal*sFraPro, sGroupProtocal*psGroPro, unsigned char ucGroupNum) {
    //    char cCnt;
    /*calc all byte of frame,31 + ucGroupNum * 50 + 4 + 2 + 2;*/
    sFraPro->AllLength = 39 + ucGroupNum * 50;
    sFraPro->Group4 = NULL;
    sFraPro->Group3 = NULL;
    sFraPro->Group2 = NULL;
    sFraPro->Group1 = NULL;
    /*get Group*/
    switch (ucGroupNum) {
        case 4:
        {
            sFraPro->Group4 = psGroPro + 3;
        }
        case 3:
        {
            sFraPro->Group3 = psGroPro + 2;
        }
        case 2:
        {
            sFraPro->Group2 = psGroPro + 1;
        }
        case 1:
        {
            sFraPro->Group1 = psGroPro;
            break;
        }
        case 0:
        {
            break;
        }
    }
}

/*************************************
 * Function: vGPRSPacketData2InFrame
 * Description: packet data2 in Frame ,data2 like currentprice
 * Input: psGroPro
 * Output: void
 * notice: 
 *************************************/
void vGPRSPacketData2InFrame(sFrameProtocal * sFraPro, unsigned char ucAllFrameNumbers, unsigned char ucCurrentFrameID) {
    /*get current price*/
    ClearDat(sFraPro->CurrentPrice, 0, 4);
    /*set current frame id*/
    sFraPro->CurrentFrameID = ucCurrentFrameID;
    /*set frame length*/
    sFraPro->AllFrameNumbers = ucAllFrameNumbers;
}

/*************************************
 * Function: vGPRSFrameToChar
 * Description: packet data3 in Frame ,data3 like recordtime,currentprice
 * Input: psGroPro
 * Output: void
 * notice: 
 *************************************/
void vGPRSFrameToChar(sFrameProtocal * sFraPro, unsigned char* ucFrame, unsigned char ucGroupNum) {
    unsigned char ucTempFrame[245];
    unsigned char ucOffset = 0;
    unsigned char ucCnt = 0;
    unsigned int uiCRC16;
    /*get member*/
    ucTempFrame[ucOffset++] = sFraPro->FrameID;
    ucTempFrame[ucOffset++] = sFraPro->AllLength;
    ucTempFrame[ucOffset++] = sFraPro->FunctionCode;
    CopyDat(ucTempFrame + ucOffset, sFraPro->DeviceID, 8);
    ucOffset += 8;
    CopyDat(ucTempFrame + ucOffset, sFraPro->LocationNumber, 8);
    ucOffset += 8;
    CopyDat(ucTempFrame + ucOffset, sFraPro->UserID, 6);
    ucOffset += 6;
    CopyDat(ucTempFrame + ucOffset, sFraPro->SendTime, 6);
    ucOffset += 6;
    if (ucGroupNum) {
        for (ucCnt = 0; ucCnt < ucGroupNum; ucCnt++) {
            vGPRSGroupToChar(sFraPro->Group1 + ucCnt, ucTempFrame + ucOffset);
            ucOffset += 50;
        }
        CopyDat(ucTempFrame + ucOffset, sFraPro->CurrentPrice, 4);
        ucOffset += 4;
        ucTempFrame[ucOffset++] = sFraPro->CurrentFrameID;
        ucTempFrame[ucOffset++] = sFraPro->AllFrameNumbers;
    }
    uiCRC16 = uiCRC16Check(ucTempFrame, ucOffset);
    sFraPro->CRCL = uiCRC16;
    sFraPro->CRCH = uiCRC16 >> 8;
    ucTempFrame[ucOffset++] = sFraPro->CRCL;
    ucTempFrame[ucOffset++] = sFraPro->CRCH;
    CopyDat(ucFrame, ucTempFrame, ucOffset);
}





