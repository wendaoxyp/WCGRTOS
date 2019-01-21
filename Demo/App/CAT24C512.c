#include <stdint.h>

#include "CAT24C512.h"
#include "I2C_S.h"

sI2CDeviceAttribute sCAT24C512;

/*************************************
Function: vCAT24Init
Description: CAT初始化，对WP口初始化，如果要I2C协议的话，需要初始化I2C
Input: void
Output: void
 *************************************/
void vCAT24Init(void) {
#ifndef Have_Initialized_I2C
    vI2CInit();
#define Have_Initialized_I2C
#endif 
    /*CAT24C512设置为输出*/
    CAT24_WP_DIR = 0;
    /*开启写保护*/
    CAT24_WP = 1;
    /*doing some setting here*/
}

/*************************************
Function: xCAT24WritePage
Description: 向CAT24，页写
Input: 填充数据的地址add，写入的数据data指针，数据长度bytes,operation(write or read)
Output: 操作CAT24的状态CAT24_STA
 *************************************/
CAT24_STA xCAT24WriteReadPage(const unsigned int usRegisterAddress,
        unsigned char* pucFirstByteAddress,
        const unsigned char ucWriteReadBytes,
        bool bWriteRead) {
    CAT24_STA xCATSta = 0;
    /*关闭写保护*/
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
    /*开启写保护*/
    CAT24_WP = 1;
    return xCATSta;
}



