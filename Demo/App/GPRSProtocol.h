#ifndef _GPRSPROTOCOL_H
#define _GPRSPROTOCOL_H

#include "DW02.h"

/*define type grouprotocal,PIC24 is Big-Endian ,but need Little-Endian*/
typedef struct GroupProtocal {
    unsigned char RecordTime[6];
    double/* unsigned char*/ Vb;
    double /*unsigned char*/ Vm;
    float /*unsigned char*/ Qb;
    float/* unsigned char */Qm;
    float /*unsigned char */Temperature;
    float /*unsigned char*/ Pressure;
    unsigned char StatuWord;
    unsigned char AlarmWord[3];
    long long Surplus; // £”‡¡ø    
} sGroupProtocal;

/*define type FrameProtocal*/
typedef struct FrameProtocal {
    unsigned char FrameID;
    unsigned char AllLength;
    unsigned char FunctionCode;
    unsigned char DeviceID[8];
    unsigned char LocationNumber[8];
    unsigned char UserID[6];
    unsigned char SendTime[6];
    struct GroupProtocal *Group1;
    struct GroupProtocal *Group2;
    struct GroupProtocal *Group3;
    struct GroupProtocal *Group4;
    unsigned char CurrentPrice[4];
    unsigned char AllFrameNumbers;
    unsigned char CurrentFrameID;
    unsigned char CRCH;
    unsigned char CRCL;
} sFrameProtocal;

extern void vGPRSPacketDataToGroup(sGroupProtocal* sGroPro, unsigned char *usTime, float fPressure);
extern void vGPRSGroupToChar(sGroupProtocal* sGroPro, unsigned char *ucGroup);
extern void vGPRSPacketData1InFrame(sFrameProtocal*sFraPro);
extern void vGPRSPacketData2InFrame(sFrameProtocal * sFraPro, unsigned char ucAllFrameNumbers, unsigned char ucCurrentFrameID);
extern void vGPRSPacketGroupInFrame(sFrameProtocal*sFraPro, sGroupProtocal*psGroPro, unsigned char ucGroupNum);
extern void vGPRSFrameToChar(sFrameProtocal * sFraPro, unsigned char* ucFrame, unsigned char ucGroupNum);
#endif
