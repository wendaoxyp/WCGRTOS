#include "CheckData.h"

/*************************************
 * Function: uiCRC16Check
 * Description: CRC16校验程序
 * Input: pucCRCBuf:数据地址
 *        ucBufLenght:数据长度
 * Output: CRC_Value:CRC校验值
 * notice: 
 *************************************/
uint16_t uiCRC16Check(uint8_t *pucCRCBuf, const uint8_t ucBufLenght) {
    uint16_t usCount1, usCount2;
    uint16_t usCRCSumx;

    usCRCSumx = 0xFFFF;
    for (usCount1 = 0; usCount1 < ucBufLenght; usCount1++) {
        /*异或*/
        usCRCSumx ^= *(pucCRCBuf + usCount1);
        for (usCount2 = 0; usCount2 < 8; usCount2++) {
            if (usCRCSumx & 0x01) {
                usCRCSumx >>= 1;
                usCRCSumx ^= 0xA001;
            } else {
                usCRCSumx >>= 1;
            }
        }
    }
    return (usCRCSumx);
}

/*************************************
Function: usSumCheck 
Description: 计算和校验的数值，
Input: pucCRCBuf：数据，ucBufLenght：字节数 
Output: 和校验结果值
 *************************************/
uint16_t uiSumCheck(uint8_t *pucCRCBuf, const uint8_t ucBufLenght) {
    uint16_t usSum = 0;
    uint16_t usCount = ucBufLenght;
    while (usCount > 0) {
        usSum += *pucCRCBuf++;
        usCount--;
    }
    return usSum;
}










