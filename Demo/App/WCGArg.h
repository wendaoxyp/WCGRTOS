#ifndef WCGARG_H
#define WCGARG_H

#include <stdbool.h>

//#define WCGArgBytes 33//32 1

enum xScreenID {
    eMainPage1 = 0, eMainPage2 = 1, eMainPage3 = 2, ePasswordPage = 3, eSetPage1 = 4, eSetPage2 = 5,
    eSetPage3 = 6, eSetPage4 = 7, eSetPage5 = 8, eSetPage6 = 9, eSetPage7 = 10, eSetPage8 = 11,
    eSetPage9 = 12,

    /* Other page SetPage2 = 3,*/
};

union sConfigbit {
    unsigned char SampleMode : 2;
    unsigned char SendMode : 2;
    unsigned char None : 4;
};

struct sGlobalWCGArg {
    unsigned char IP[4]; //4
    unsigned int Port; //2
    union sConfigbit Configbit1; //1
    unsigned char SampleSetTime[3]; //3
    unsigned int SamplePeriodTime; //2
    unsigned char SendSetTime[3]; //3
    unsigned int SendPeriodTime; //2
    float PressureAlarmHighValue; //4
    float PressureAlarmLowValue; //4
    unsigned char DataTime[7]; //7
};

//#define MainScreenPage     3
#define MaxScreenPage      13
#define NoUseCursor        0x07

extern void vSetScreenID(void*);
extern void vWriteWCGArg(struct sGlobalWCGArg psWriteArg);
extern void vReadWCGArg(struct sGlobalWCGArg *psReadArg);
extern bool bPasswordIsRight(unsigned char *ucpPassword);
extern void vWCGGetCurrentTime(unsigned char* ucCurrentTime);
#endif

