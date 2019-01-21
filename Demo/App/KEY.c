/*
 * File:   KEY.c
 * Author: zw
 *
 * Created on 2019��1��10��, ����2:36
 */

#include "KEY.h"

#if (UseFreeRTOSInKey == 1)
#include "FreeRTOS.h"
#include "semphr.h"
extern xSemaphoreHandle xSemBinKey;
#endif

/*************************************
Function: vDelay10ms
Description: ��ʱ10ms
Input: ʱ��
Output: ��
 *************************************/
static void vKeyDelay10ms(unsigned int usDelay10ms) {
    unsigned int usConut;
    while (usDelay10ms-- > 0)
        for (usConut = 0; usConut < DELAY10MS; usConut++)
            Nop();
}

/*************************************
Function: vDelay100ms
Description: ��ʱ100ms
Input: ʱ��
Output: ��
 *************************************/
/*static void vKeyDelay100ms(unsigned int usDelay100ms) {
    unsigned int usConut;
    while (usDelay100ms-- > 0)
        for (usConut = 0; usConut < DELAY100MS; usConut++)
            Nop();
}*/

#if  (UseKeyInterrupt == 1)

/*************************************
Function: vIOCInit
Description: key interrupt initialization
Input: void 
Output: void
 *************************************/
void vKeyInterruptInit(void) {
    _CN14PUE = 1;
    _CN15PUE = 1;
    _CN16PUE = 1;
    _CN14IE = 1;
    _CN15IE = 1;
    _CN16IE = 1;
    /*freertos priority is 2*/
    _CNIP = 1;
    /*�����־λ*/
    _CNIF = 0;
    _CNIE = 1;
}
#endif 

#if (UseKeyInterrupt == 1)

/*************************************
Function: IOC
Description: ��������
Input: void 
Output: void
 *************************************/

void __attribute__((interrupt, no_auto_psv)) _CNInterrupt(void) {
#if (UseFreeRTOSInKey == 1)
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
#else
    unsigned char ucKeyState;
#endif
    if (!ReadKey1State | !ReadKey2State | !ReadKey3State)
#if (UseFreeRTOSInKey == 1)    
        xSemaphoreGiveFromISR(xSemBinKey, &xHigherPriorityTaskWoken);
    //        portYIELD_WITHIN_API(xHigherPriorityTaskWoken);
#else
        vKeyScan(&ucKeyState);
#endif         
    _CNIF = 0; //�����־λ;
}
#endif 

/*************************************
Function: vKeyInit
Description: IO������������
Input: �� 
Output:�� 
 *************************************/
void vKeyInit(void) {
    /*key1������������*/
    SetKey1ANS = 0;
    /*key1��������*/
    SetKey1Tris = 1;
    /*key2������������*/
    SetKey2ANS = 0;
    /*key2��������*/
    SetKey2Tris = 1;
    //    /*key3������������*/
    //    SetKey3ANS = 0;
    /*key3��������*/
    SetKey3Tris = 1;
#if (UseKeyInterrupt == 1)
    /*��������IOC*/
    vKeyInterruptInit();
#endif 
}

/*************************************
Function: usReadKeyIO
Description: read key IO
Input: �� 
Output:key IO Port
 *************************************/
static unsigned int usReadKeyIO(void) {
    return (ReadKey1State || (ReadKey2State << 1) || (ReadKey3State << 2));
}

/*************************************
Function: vKeyScan
Description: ��������
Input: �� 
Output:��������
 *************************************/
void vKeyScan(void* vKeyState) {
    unsigned char ucKeyState = InvalidKEY;
    unsigned char ucCount = 0;
    unsigned int usKeyIOCurrent, usKeyIONext;

    usKeyIOCurrent = usReadKeyIO();
    if (usKeyIOCurrent) {
        /*ǰ������*/
        vKeyDelay10ms(1);
        /*check key is really push*/
        usKeyIOCurrent = usReadKeyIO();
        if (usKeyIOCurrent) {
            for (ucCount = 0; ucCount < 200; ucCount++) {
                vKeyDelay10ms(1);
                usKeyIONext = usReadKeyIO();
                if (usKeyIONext != usKeyIOCurrent) {
                    break;
                }
                /*for*/
            }
            /*end if (usKeyIOCurrent)*/
        }

        if (ucCount >= 200) {
            ucKeyState = (LongKEY << 6) | usKeyIOCurrent;
        } else if (ucCount > 20) {
            ucKeyState = (ShortKEY << 6) | usKeyIOCurrent;
        } else {
            ucKeyState = (InvalidKEY << 6) | usKeyIOCurrent;
        }
    }
    /*return which key and key state*/
    *((unsigned char*) vKeyState) = ucKeyState;
}

/*************************************
Function: vKey1LongHandle
Description: deal witch key by keystate 
Input: ucKeyState 
Output: void
 *************************************/

static void vKey1LongHandle(void*parameter) {
    unsigned char ucLCDNum;

    ucLCDNum = *((unsigned char *) parameter);
    /*increase*/
    ucLCDNum++;
    /*mod*/
    ucLCDNum %= 10;
    /*return parameter*/
    *((unsigned char *) parameter) = ucLCDNum;
}

/*************************************
Function: vKey1ShortHandle
Description: deal witch key by keystate 
Input: ucKeyState 
Output: void
 *************************************/

static void vKey1ShortHandle(void*parameter) {
    unsigned char ucLCDNum;

    ucLCDNum = *((unsigned char *) parameter);
    /*increase*/
    ucLCDNum++;
    /*mod*/
    ucLCDNum %= 10;
    /*return parameter*/
    *((unsigned char *) parameter) = ucLCDNum;
}

/*************************************
Function: vKeyUserFunction
Description: deal witch key by keystate 
Input: ucKeyState 
Output: void
 *************************************/
void vKeyUserFunction(unsigned char ucKeyState) {
    unsigned char ucNum;
    /*switch key function*/
    switch (ucKeyState) {
        case 0xC1://LongKEY1
        {
            vKey1LongHandle(&ucNum);
            break;
        }
        case 0x41://ShortKEY1
        {
            vKey1ShortHandle(&ucNum);
            break;
        }
        case 0xC2://LongKEY2
        {
            break;
        }
        case 0x42://ShortKEY2
        {
            break;
        }
        case 0xC4://LongKEY2
        {
            break;
        }
        case 0x44://ShortKEY2
        {
            break;
        }
    }
}






