/* 
 * File:   CAT24C512.c
 * Author: Administrator
 *
 * Created on January 2, 2018, 11:22 AM
 */

#ifndef CAT24C512_C
#define	CAT24C512_C

/***************************************************************************
 * Includes 
 ***************************************************************************/
#include <xc.h>
#include <stdbool.h>

/***************************************************************************
 * Definition 
 ***************************************************************************/
#define CAT24_WP                _LATF2
#define CAT24_WP_DIR            _TRISF2
#define CAT24_ADD               0b10101000
//#define CAT24_ERR_W_IC_ADD      0x10    //写IC地址(含操作码)失败
//#define CAT24_ERR_W_ADDH        0x11    //写高位地址失败
//#define CAT24_ERR_W_ADDL        0x12    //写低位地址失败
//#define CAT24_ERR_W_DATA        0x13    //写数据失败
//#define CAT24_NO_ERR            0x14    //操作完成
//#define CAT24_ERR_WR_IC_ADD     0x15    //（读取操作）写IC地址失败
//#define CAT24_ERR_WR_ADDH       0x16    //（读取操作）写高位地址失败
//#define CAT24_ERR_WR_ADDL       0x17    //（读取操作）写低位地址失败
//#define CAT24_ERR_R_IC_ADD      0x18    //（读取操作）写IC地址失败
//#define CAT24_ERR_MW_OVERFLOW   0x19    //连续写操作中，数据溢出（>127字节）
/*define operation*/
#define CAT24_WRITE             0
#define CAT24_READ              1
/*defien macro function*/
#define xCAT24WriteByte(usAddress, ucWriteData)  \
        xCAT24WriteReadPage(usAddress, &ucWriteData, 1, CAT24_WRITE)
#define xCAT24ReadByte(usAddress, ucReadData)  \
        xCAT24WriteReadPage(usAddress,  &ucReadData,1, CAT24_READ)
#define xCAT24WriteBytes(usAddress, pucWriteData,ucBytes) \
        xCAT24WriteReadPage(usAddress,  pucWriteData,ucBytes, CAT24_WRITE)
#define xCAT24ReadBytes(usAddress, pucWriteData,ucBytes) \
        xCAT24WriteReadPage(usAddress,  pucWriteData,ucBytes, CAT24_READ)
typedef unsigned char CAT24_STA;
/***************************************************************************
 * Prototype 
 ***************************************************************************/
/*define Intialize function*/
extern void vCAT24Init(void);
/*define operation function*/
extern CAT24_STA xCAT24WriteReadPage(const unsigned int usRegisterAddress,
        unsigned char* pucFirstByteAddress,
        const unsigned char ucWriteReadBytes,
        bool bWriteRead);
#endif	/* CAT24C512_C */

