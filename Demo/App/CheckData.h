/* 
 * File:   CRC16.h
 * Author: TURONG62
 *
 * Created on 2016年6月22日, 上午9:06
 */

#ifndef CHECKDATA_H
#define	CHECKDATA_H

#include <stdint.h>
#include <stdbool.h>


/*CRC16 check*/
uint16_t usCRC16Check(uint8_t *pucCRCBuf, const uint8_t ucCRCLength);
/*sum check*/
uint16_t usSumCheck(uint8_t *pucCRCBuf, const uint8_t ucBufLength);
/*CRC16 is right*/
#define  bCRC16IsRight(pucBuf,ucBufLength,usCheckDat) \
               (((usCheckDat<<8)+(usCheckDat>>8)) == usCRC16Check(pucBuf, ucBufLength))
/*CRC16 is right by protocal*/
#define  bCRC16IsRight1(pucBuf,ucBufLength) \
               (((unsigned int)(*(ucBufLength+pucBuf+1))<<8)+(*(ucBufLength+pucBuf)) == usCRC16Check(pucBuf, ucBufLength))
/*sum check is right*/
#define bSumCheckIsRight(pucBuf,ucBufLength,usCheckDat)\
        ((usCheckDat&0x00FF)==usSumCheck(pucBuf,ucBufLength))

#endif	/* CRC16_H */

