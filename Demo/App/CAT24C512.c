#include <stdint.h>

#include "CAT24C512.h"
#include "I2C_S.h"

sI2CDeviceAttribute sCAT24C512;

/*************************************
Function: vCAT24Init
Description: CAT��ʼ������WP�ڳ�ʼ�������ҪI2CЭ��Ļ�����Ҫ��ʼ��I2C
Input: void
Output: void
 *************************************/
void vCAT24Init(void) {
#ifndef Have_Initialized_I2C
    vI2CInit();
#define Have_Initialized_I2C
#endif 
    /*CAT24C512����Ϊ���*/
    CAT24_WP_DIR = 0;
    /*����д����*/
    CAT24_WP = 1;
    /*doing some setting here*/
}

/*************************************
Function: xCAT24WritePage
Description: ��CAT24��ҳд
Input: ������ݵĵ�ַadd��д�������dataָ�룬���ݳ���bytes,operation(write or read)
Output: ����CAT24��״̬CAT24_STA
 *************************************/
CAT24_STA xCAT24WriteReadPage(const unsigned int usRegisterAddress,
        unsigned char* pucFirstByteAddress,
        const unsigned char ucWriteReadBytes,
        bool bWriteRead) {
    CAT24_STA xCATSta = 0;
    /*�ر�д����*/
    CAT24_WP = 0;

    /*set cat24c512 attribute*/
    sCAT24C512.ucSlaveAddress = CAT24_ADD;
    sCAT24C512.usRegisterAddress = usRegisterAddress;
    sCAT24C512.bIs16BitDevice = true;
    sCAT24C512.pucNeedData = pucFirstByteAddress;
    sCAT24C512.ucNeedDataBytes = ucWriteReadBytes;
    /*select read or write*/
    if (bWriteRead) {
        /*read data*/
        xCATSta = bI2CReadSlave(&sCAT24C512);
    } else {
        /*write  data*/
        xCATSta = bI2CWriteSlave(&sCAT24C512);
    }
    /*����д����*/
    CAT24_WP = 1;
    return xCATSta;
}



