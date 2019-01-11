#ifndef TIM_H
#define TIM_H

#include <xc.h>
#include <stdint.h>



extern void TMR1_Initialize(void);
extern void TMR2_Initialize(void);
extern void TMR3_Initialize(void);
extern void TMR4_Initialize(void);
extern void StartTMR2(void);
extern void StopTMR2(void);
extern void StartTMR3(const uint8_t cnt);
extern void StopTMR3(void);
extern void StartTMR4(void);
extern void StopTMR4(void);
#endif



