#include "INT.h"
#include "WCGDeBug.h"
#include <xc.h>

#if   (DebugPCF8583 == 1)
#include "FreeRTOS.h"
#include "semphr.h"
#include "Debug.h"
/*endif (DebugPCF8583 == 1)*/
#endif

void INT0_Init(void) {
    TRISFbits.TRISF6 = 1; //����Ϊ����
    INTCON2bits.INT0EP = 1; //  1 = �½����ж�  0 = �������ж�
    IPC0bits.INT0IP = 7; //���ȼ�Ϊ2
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 1; //ʹ���ж�
}

void INT0_Open(void) {
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 1;
}

void INT0_Close(void) {
    IFS0bits.INT0IF = 0; //�����־λ
    IEC0bits.INT0IE = 0;
}
extern void vDeBugPrintInformation(void* strings);
/*debug PCF8583*/
#if (DebugPCF8583 == 1)
extern SemaphoreHandle_t xSemBinaryAlarm;
/*endif (DebugPCF8583 == 1)*/
#endif

void __attribute__((__interrupt__, auto_psv))_INT0Interrupt(void) {
#if  (DebugPCF8583 == 1)
    vDeBugPrintInformation("****************************\r\n");
    vDeBugPrintInformation("enter int0\r\n");
    vDeBugPrintInformation("****************************\r\n");
    xSemaphoreGiveFromISR(xSemBinaryAlarm, NULL);
    /*endif (DebugPCF8583 == 1)*/
#endif
    IFS0bits.INT0IF = 0;
}
