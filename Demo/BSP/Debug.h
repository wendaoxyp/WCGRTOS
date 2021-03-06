/* 
 * File:   Debug.h
 * Author: Administrator
 *
 * Created on January 4, 2018, 4:58 PM
 */

#ifndef DEBUG_H
#define	DEBUG_H


/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "Common.h"
#include "UART3.h"//19200

//#define Debug_SampleTest         //定义采样测试 缓冲区
//#define DeBug_PrintsInfo         //定义打印调试消息

//typedef void (*SendStr)(void * dat, const uint8_t cnt);
//typedef void (*SendChar)(uint8_t ch);


#define vDebugSendString       vUART3SendString
#define vDebugSend             vUART3Send
//#define DebugCode(x) DeBug_PritnErrCode1(x);


/***************************************************************************
 * Prototype
 ***************************************************************************/
extern void vDeBugPrintInformation(void *strings);
extern void vDeBugPrintStringAndNums(void *strings, uint16_t nums);
extern void vDeBugPrintHexNums(void *pvStrings, uint8_t* pucNums, unsigned char ucBytes);
#endif	/* DEBUG_H */

