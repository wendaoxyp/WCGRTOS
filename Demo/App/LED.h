/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LED_H
#define	LED_H

#include <xc.h>
#include <stdbool.h>

/*use freertos*/
#define UseFreeRTOS                 1
/*set delay const*/
#define CPU_CLOCK_HZ  4000000
#if (CPU_CLOCK_HZ == 2000000)
#define DELAY10MS   4251     
#define DELAY100MS  29761              
#elif (CPU_CLOCK_HZ == 4000000)
#define DELAY10MS   4251  
#define DELAY100MS  40900           
#endif

/*set IO level*/
#define GPIO_OUTPUT                            0 
#define GPIO_SET_HIGH                          1
#define GPIO_SET_LOW                           0
/*定义IO口*/
#define LEDGreenTRIS                           _TRISE5
#define LEDGreenLAT                            _LATE5
#define LEDRedTRIS                             _TRISE7
#define LEDRedLAT                              _LATE7

#define LEDRedON                               (LEDRedLAT=1)
#define LEDRedOFF                              (LEDRedLAT=0)
#define LEDGreenON                             (LEDGreenLAT=1)
#define LEDGreenOFF                            (LEDGreenLAT=0)

#define LEDGreen                               1
#define LEDRed                                 2
#define LEDTurnON                              1
#define LEDTurnOFF                             0

/*init led*/
extern void vLEDInit(void);
/*LED handle*/
extern void vLEDHandle(unsigned char ucLEDIO, bool bLEDSta);
/*LED操作*/
extern void vLEDShark(unsigned char ucLEDIO, unsigned int usLedOnTimeMs, unsigned int usLedOffTimeMs, unsigned char ucSharkCnt);

#endif	/* XC_HEADER_TEMPLATE_H */

