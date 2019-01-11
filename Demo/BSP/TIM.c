#include <TIM.h>
//用于显示LCD

volatile uint8_t gT3flag;
volatile uint8_t gT3Cnt;
//用于休眠状态下指示灯工作

void TMR1_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS External; TSYNC disabled; TCKPS 1:1; TECS SOSC; TON enabled; 
    T1CON = 0x0002;
    //TMR1 0; 
    TMR1 = 0x0000;
    //PR1 20; 
    PR1 = 0x8000; //1s// 0xF230; //2s 
    T1CONbits.TON = 1;
    IPC0bits.T1IP = 5;
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
}
//用于采集任务

void TMR2_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS FOSC/2; TCKPS 1:256; T32 disabled; TON enabled; 
    T2CON = 0x8030;
    //TMR2 0; 
    TMR2 = 0x0000;
    //Period Value = 10.000 ms; PR2 20000; 
    PR2 = 0xffff; //0x4E20;
    IPC1bits.T2IP = 3;
    T2CONbits.TON = 0;
    IFS0bits.T2IF = 0;
}
//用于低功耗AT指令

void TMR3_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS FOSC/2; TCKPS 1:256; T32 disabled; TON enabled; 
    T3CON = 0x0030;
    //TMR2 0; 
    TMR3 = 0x0000;
    //Period  1M
    PR3 = 391; //100ms
    IPC2bits.T3IP = 1;
    T3CONbits.TON = 0;
    IFS0bits.T3IF = 0;
}
//用于PC通讯

void TMR4_Initialize(void) {
    //TSIDL disabled; TGATE disabled; TCS External; TSYNC disabled; TCKPS 1:1; TECS SOSC; TON enabled; 
    T4CON = 0x0030;
    //TMR1 0; 
    TMR4 = 0x0000;
    //PR1 20; 
    PR4 = 3915; //1s// 0xF230; //2s 1/1000000*256
    T4CONbits.TON = 0;
    _T4IP = 2;
    _T4IF = 0;
    _T4IE = 1;
}

void StartTMR2(void) {
    IEC0bits.T2IE = 1;
    T2CONbits.TON = 1;
}

void StopTMR2(void) {
    IEC0bits.T2IE = 0;
    T2CONbits.TON = 0;
}

void StartTMR3(const uint8_t cnt) {
    TMR3 = 0x0000;
    gT3Cnt = cnt;
    //Period Value = 10.000 ms; PR2 20000; 4M
    //    if (ms100 >= 10240)
    //        PR3 = 65535;
    //    else
    //    PR3 = ms100 / 6.4; //0x4E20; 1/4000000*256   15625
    IEC0bits.T3IE = 1;
    T3CONbits.TON = 1;
}

void StopTMR3(void) {
    IEC0bits.T3IE = 0;
    T3CONbits.TON = 0;
    TMR3 = 0x0000;
    //Period Value = 10.000 ms; PR2 20000; 4M
    //    PR2 = 0xffff; //0x4E20;
}

void StartTMR4(void) {
    TMR4 = 0x0000;
    _T4IE = 1;
    T4CONbits.TON = 1;
}

void StopTMR4(void) {
    _T4IE = 0;
    T4CONbits.TON = 0;
    TMR3 = 0x0000;
}


