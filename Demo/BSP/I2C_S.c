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
Description: ��ʼ��I2C��IO
Input: void
Output: void
 *************************************/
void vI2CInit(void) {
    /*SCL����Ϊ���*/
    I2C_SCL_DIR = 0;
    /*SDA����Ϊ���*/
    I2C_SDA_DIR = 0;
    /*SCL�ø�*/
    I2C_SCL = 1;
    /*SDA�ø�*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_Start 
Description: I2C��������
Input: void 
Output: void
 *************************************/
void vI2CStart(void) {
    /*��������*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
    /*��������*/
    I2C_SCL = 1;
    /*delay*/
    vI2CDelay();
    /*�����õ�*/
    I2C_SDA = 0;
    /*delay,ȷ��IC���ܱ�ʶ�����ټ�us*/
    vI2CDelay();
    /*�ͷ�����*/
    I2C_SCL = 0;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_Stop 
Description: I2Cֹͣ����
Input: void
Output: void
 *************************************/
void vI2CStop(void) {
    /*�����õ�*/
    I2C_SDA = 0;
    /*delay*/
    vI2CDelay();
    /*��������*/
    I2C_SCL = 1;
    /*delayȷ��IC���ܱ�ʶ�����ټ�us*/
    vI2CDelay();
    /*�����ø�*/
    I2C_SDA = 1;
    /*delay*/
    vI2CDelay();
}

/*************************************
Function: I2C_WriteICAdd 
Description: I2CдIC��ַ
Input: ����IC��ַadd�����ݲ���opreation
Output: �����ֵ
 *************************************/
void vI2CWriteByte(unsigned char ucData) {
    /*������ʱ����*/
    unsigned char ucTmp;
    char cCnt;
    /*�����ݸ�ֵ*/
    ucTmp = ucData;
    /*ѭ����ȡ��������(bit)*/
    for (cCnt = 7; cCnt >= 0; cCnt--) {
        /*SDA������Ӧ�ô���SCL��SCL�м�ɼ�*/
        I2C_SDA = ((ucTmp >> cCnt) & 0x01) ? 1 : 0;
        /*delay*/
        vI2CDelay();
        /*give I2C bus*/
        I2C_SCL = 1;
        /*delay*/
        vI2CDelay();
        /*take I2C bus*/
        I2C_SCL = 0;
        /*������λ����1����SDA=0,����I2CЭ��ͨѶʧ��*/
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
//    unsigned char* pucTmp = pucData; //������ʱ����
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
    /*������ʱ����*/
    unsigned char ucTmp = 0;
    char cCnt;

    /*��������Ϊ����*/
    I2C_SDA_DIR = 1;
    /*ѭ����ȡ���ݣ�I2CЭ����������Ϊ��ʱ���м��ȡ����*/
    for (cCnt = 7; cCnt >= 0; cCnt--) {
        /*��������*/
        I2C_SCL = 1;
        /*delay*/
        vI2CDelay();
        /*�м�ɼ�*/
        ucTmp |= I2C_R_SDA << cCnt;
        /*delay*/
        vI2CDelay();
        /*�ͷ�����*/
        I2C_SCL = 0;
        /*delay*/
        vI2CDelay();
    }
    /*��������Ϊ���*/
    I2C_SDA_DIR = 0;
    /*���ؽ��*/
    return ucTmp;
}

/*************************************
Function: I2C_ACK 
Description: Master Get ACK state 
Input: void 
Output: isAck
 *************************************/
bool bI2CGetACK(void) {
    /*����I2C״̬����*/
    bool ucI2CSDASTA;

    /*�л�Ϊ���루���軻����*/
    I2C_SDA_DIR = 1;
    vI2CDelay();
    /*��������*/
    I2C_SCL = 1;
    vI2CDelay();
    /*�ж��Ƿ��ȡ��ACK*/
    ucI2CSDASTA = (I2C_R_SDA) ? I2C_MASTER_MISS_ACK : I2C_MASTER_GET_ACK;
    vI2CDelay();
    /*�ͷ�����*/
    I2C_SCL = 0;
    vI2CDelay();
    /*����Ϊ���*/
    I2C_SDA_DIR = 0;
    //    I2C_SDA = 1; //��������Ϊ��
    /*����ACK״̬*/
    return ucI2CSDASTA;
}

/*************************************
Function: I2C_NACK 
Description: master send NoAck
Input: void
Output: void
 *************************************/
void vI2CSetNACK(bool bACK) {
    /*�����ø�*/
    I2C_SDA = bACK;
    vI2CDelay();
    /*��������*/
    I2C_SCL = 1;
    vI2CDelay();
    /*�����õ�*/
    I2C_SCL = 0;
    vI2CDelay();
    /*�ͷ�����*/
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
        /*send salve register address,���뿪ʼ��ȡ*/
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

