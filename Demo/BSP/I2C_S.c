#include "I2C_S.h"
#ifdef UseRTOS
#include "FreeRTOS.h"
#include "task.h"
#endif

/*************************************
Function: vI2CDelay
Description: 
Input: void
Output: void
 *************************************/
static void vI2CDelay(void) {
    unsigned int usCnt;
    /*Select delay time by system clock*/
#if (SystemClock==4000000L)    //100Khz Fsck=100khz  
    for (usCnt = 0; usCnt < 20; usCnt++)
        SystemNop();
#else 
#error "please add delay in other clock"    
#endif
}

/*************************************
Function: I2C_Init 
Description: 初始化I2C的IO
Input: void
Output: void
 *************************************/
void vI2CInit(void) {
    /*SCL设置为输出*/
    I2C_SCL_DIR = 0;
    /*SDA设置为输出*/
    I2C_SDA_DIR = 0;
    /*SCL置高*/
    I2C_SCL = 1;
    /*SDA置高*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_Start 
Description: I2C启动函数
Input: void 
Output: void
 *************************************/
void vI2CStart(void) {
    /*数据拉高*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
    /*握手总线*/
    I2C_SCL = 1;
    /*delay*/
    vI2CDelay();
    /*数据置低*/
    I2C_SDA = 0;
    /*delay,确保IC端能被识别，至少几us*/
    vI2CDelay();
    /*释放总线*/
    I2C_SCL = 0;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_Stop 
Description: I2C停止函数
Input: void
Output: void
 *************************************/
void vI2CStop(void) {
    /*数据置低*/
    I2C_SDA = 0;
    /*delay*/
    vI2CDelay();
    /*握手总线*/
    I2C_SCL = 1;
    /*delay确保IC端能被识别，至少几us*/
    vI2CDelay();
    /*数据置高*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_WriteICAdd 
Description: I2C写IC地址
Input: 输入IC地址add，数据操作opreation
Output: 输出数值
 *************************************/
void vI2CWriteByte(unsigned char ucData) {
    /*申请临时变量*/
    unsigned char ucTmp;
    char cCnt;
    /*将数据赋值*/
    ucTmp = ucData;
    /*循环获取发送数据(bit)*/
    for (cCnt = 7; cCnt >= 0; cCnt--) {
        /*SDA的周期应该大于SCL，SCL中间采集*/
        I2C_SDA = ((ucTmp >> cCnt) & 0x01) ? 1 : 0;
        /*delay*/
        vI2CDelay();
        /*give I2C bus*/
        I2C_SCL = 1;
        /*delay*/
        vI2CDelay();
        /*take I2C bus*/
        I2C_SCL = 0;
        /*如果最后位发送1，将SDA=0,避免I2C协议通讯失败*/
        if (!cCnt && I2C_SDA)
            I2C_SDA = 0;
    }
}

///*************************************
//Function: I2C_WriteDatas 
//Description: Write data to I2C device
//Input: data 
//Output: is finish complete 
// *************************************/
//bool bI2CWriteBytes(unsigned char *pucData, unsigned char ucDatasBytes) {
//    unsigned char* pucTmp = pucData; //申明临时变量
//    char cCnt;
//
//    /*repeat write data */
//    for (cCnt = 0; cCnt < ucDatasBytes; cCnt++) {
//        vI2CWriteByte(*(pucTmp + cCnt));
//        if (!bI2CGetACK()) {
//            return false;
//        }
//    }
//    return true;
//}

/*************************************
Function: I2C_ReadData 
Description:read data from I2C device 
Input: void 
Output: data
 *************************************/
unsigned char ucI2CReadByte(void) {
    /*声明临时变量*/
    unsigned char ucTmp = 0;
    char cCnt;

    /*数据设置为输入*/
    I2C_SDA_DIR = 1;
    /*循环获取数据，I2C协议中是总线为高时，中间获取数据*/
    for (cCnt = 7; cCnt >= 0; cCnt--) {
        /*握手总线*/
        I2C_SCL = 1;
        /*delay*/
        vI2CDelay();
        /*中间采集*/
        ucTmp |= I2C_R_SDA << cCnt;
        /*delay*/
        vI2CDelay();
        /*释放总线*/
        I2C_SCL = 0;
        /*delay*/
        vI2CDelay();
    }
    /*数据设置为输出*/
    I2C_SDA_DIR = 0;
    /*返回结果*/
    return ucTmp;
}

/*************************************
Function: I2C_ACK 
Description: Master Get ACK state 
Input: void 
Output: isAck
 *************************************/
bool bI2CGetACK(void) {
    /*声明I2C状态变量*/
    bool ucI2CSDASTA;

    /*切换为输入（必需换方向）*/
    I2C_SDA_DIR = 1;
    vI2CDelay();
    /*握手总线*/
    I2C_SCL = 1;
    vI2CDelay();
    /*判断是否获取到ACK*/
    ucI2CSDASTA = (I2C_R_SDA) ? I2C_MASTER_MISS_ACK : I2C_MASTER_GET_ACK;
    vI2CDelay();
    /*释放总线*/
    I2C_SCL = 0;
    vI2CDelay();
    /*设置为输出*/
    I2C_SDA_DIR = 0;
    //    I2C_SDA = 1; //数据设置为高
    /*返回ACK状态*/
    return ucI2CSDASTA;
}

/*************************************
Function: I2C_NACK 
Description: master send NoAck
Input: void
Output: void
 *************************************/
void vI2CSetNACK(bool bACK) {
    /*数据置高*/
    I2C_SDA = bACK;
    vI2CDelay();
    /*握手总线*/
    I2C_SCL = 1;
    vI2CDelay();
    /*数据置低*/
    I2C_SCL = 0;
    vI2CDelay();
    /*释放总线*/
    I2C_SDA = 0;
    vI2CDelay();
}

/*************************************
Function: bI2CWriteSlave 
Description: continue write data 
Input: sI2CDevice
Output: void
 *************************************/
bool bI2CWriteSlave(sI2CDeviceAttribute *sI2CDevice) {
    /*if use rtos,disable tick interrupt*/
#ifdef UseRTOS
    taskDISABLE_INTERRUPTS();
#endif
    bool bIsWriteComplete = true;
    unsigned char ucCnt;
    /*Start I2C communication*/
    vI2CStart();
    /*Select PCF and  ready to write */
    vI2CWriteByte(sI2CDevice->ucSlaveAddress & I2C_WRITE);
    if (bI2CGetACK()) {
        if (sI2CDevice->bIs16BitDevice) {
            /*write 16bit register address 0x00*/
            vI2CWriteByte((unsigned char) ((sI2CDevice->usRegisterAddress && 0x00ff) >> 8));
            if (bI2CGetACK()) {
                vI2CWriteByte((unsigned char) (sI2CDevice->usRegisterAddress & 0x00ff));
            }
        } else {
            /*write 8bit register address 0x00*/
            vI2CWriteByte((unsigned char) (sI2CDevice->usRegisterAddress & 0x00FF));
        }
        if (bI2CGetACK()) {
            /*write data in register ,all write 15 bytes,repeat write data */
            for (ucCnt = 0; ucCnt < sI2CDevice->ucNeedDataBytes; ucCnt++) {
                vI2CWriteByte(*(sI2CDevice->pucNeedData + ucCnt));
                if (!bI2CGetACK()) {
                    bIsWriteComplete = false; //                error(0);//notice error:0
                    break;
                }
            }
        }
    }
    /*I2C Protocal stop commuication*/
    vI2CStop();
#ifdef UseRTOS
    taskENABLE_INTERRUPTS();
#endif
    return bIsWriteComplete;
}

/*************************************
Function: bI2CReadSlave 
Description: master read data
Input: sI2CDevice
Output: void
 *************************************/
bool bI2CReadSlave(sI2CDeviceAttribute *sI2CDevice) {
    unsigned char ucCnt;
    bool bIsReadComplete = false;

#ifdef UseRTOS
    taskDISABLE_INTERRUPTS();
#endif
    /*I2C protocal is started communication*/
    vI2CStart();
    /*send salve address and write operation*/
    vI2CWriteByte(sI2CDevice->ucSlaveAddress & I2C_WRITE);
    /*get ack*/
    if (bI2CGetACK()) {
        /*send salve register address,从秒开始读取*/
        if (sI2CDevice->bIs16BitDevice) {
            /*write 16bit register address 0x00*/
            vI2CWriteByte((unsigned char) ((sI2CDevice->usRegisterAddress && 0x00ff) >> 8));
            if (bI2CGetACK()) {
                vI2CWriteByte((unsigned char) (sI2CDevice->usRegisterAddress & 0x00ff));
            }
        } else {
            /*write 8bit register address 0x00*/
            vI2CWriteByte((unsigned char) (sI2CDevice->usRegisterAddress & 0x00FF));
        }
        //        vI2CWriteByte(sI2CDevice->usRegisterAddress); //PCF_CON_STA + 2);
        /*get ack*/
        if (bI2CGetACK()) {
            /*I2C Restart*/
            vI2CStart();
            /*send read handle*/
            vI2CWriteByte(sI2CDevice->ucSlaveAddress | I2C_READ);
            /*get ack*/
            if (bI2CGetACK()) {
                /*repeat read data*/
                for (ucCnt = 0; ucCnt < sI2CDevice->ucNeedDataBytes; ucCnt++) {
                    /*Read byte*/
                    *(sI2CDevice->pucNeedData + ucCnt) = ucI2CReadByte();
                    /*if count is last byte, set nack;else set ack*/
                    if (ucCnt == sI2CDevice->ucNeedDataBytes - 1) {
                        vI2CSetNACK(I2C_MASTER_SEND_NACK);
                        bIsReadComplete = true;
                    } else {
                        vI2CSetNACK(I2C_MASTER_SEND_ACK);
                    }
                }
            }

        }
    }
    /*I2x protocal is stopped communication */
    vI2CStop();
#ifdef UseRTOS
    taskENABLE_INTERRUPTS();
#endif
    return bIsReadComplete;
}

