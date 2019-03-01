/* 
 * File:   I2C_S.h
 * Author: Administrator
 *
 * Created on December 29, 2017, 3:35 PM
 */

#ifndef I2C_S_H
#define	I2C_S_H

/***************************************************************************
 * Includes
 ***************************************************************************/
#include <xc.h>
#include <stdbool.h>
/***************************************************************************
 * Definitions
 ***************************************************************************/
/*********************user must define******************/
#define SystemClock         4000000L
#define SystemNop           Nop
/*SCK pin37 G2
 *SDA pin36 G3
 */
#define I2C_SCL             LATGbits.LATG2
#define I2C_SDA             LATGbits.LATG3

#define I2C_SCL_DIR         TRISGbits.TRISG2   
#define I2C_SDA_DIR         TRISGbits.TRISG3
#define I2C_R_SDA           PORTGbits.RG3

#define I2C_WRITE                       0xFE
#define I2C_READ                        0x01

#define I2C_MASTER_MISS_ACK             0
#define I2C_MASTER_GET_ACK              1

#define I2C_MASTER_SEND_ACK             0
#define I2C_MASTER_SEND_NACK            1

/*is use RTOS like liteos freeos ucos*/
#define UseRTOS

/*declare new type*/
typedef struct I2CDeviceAttribute {
    unsigned char ucSlaveAddress;
    unsigned int usRegisterAddress;
    bool bIs16BitDevice;
    unsigned char* pucNeedData;
    unsigned char ucNeedDataBytes;
} sI2CDeviceAttribute;

/***************************************************************************
 * Prototypes
 ***************************************************************************/
/*I2C Potpcal IO setting
 * user should define I2C_SCL\I2C_SDA\I2C_SCL_DIR\I2C_SDA_DIR\I2C_R_SDA*/
extern void vI2CInit(void);
///*I2C Protocal Start function*/
//extern void vI2CStart(void);
////extern void I2C_Restart(void);
///*I2C Protocal Stop function*/
//extern void vI2CStop(void);
///*I2C Master Send SalveAdress ,select Read or Write I2C device
// *paramter :I2C_Address+I2C_WRITE(I2C_READ),or I2C device register*/
//extern void vI2CWriteByte(unsigned char ucAddress);
///*Master write data in Salve*/
//extern bool bI2CWriteBytes(unsigned char *pucData, unsigned char ucDatasBytes);
///*Master read data from Salve*/
//extern unsigned char ucI2CReadByte(void);
///*Master get ack from Salve*/
//extern bool bI2CGetACK(void);
///*Master set nack to Salve*/
//extern void vI2CSetNACK(void);
/*Write Slave Device*/
extern bool bI2CWriteSlave(sI2CDeviceAttribute*);
/*Read Slave Device*/
extern bool bI2CReadSlave(sI2CDeviceAttribute *sI2CDevice);
#endif	/* I2C_S_H */
