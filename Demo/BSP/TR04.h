#ifndef _TR04_H_
#define _TR04_H_
/*获取压力值：
发送数据：
01 03 00 64 00 02 85 D4 
接受数据：
01 03 04 3E F4 00 00 B6 29
 */
/*define receive get pressure protocal length*/
#define  PressReciveLength                      (9)                           
/*define send get pressure protocal*/
const unsigned char TR04[8] = {0x01, 0x03, 0x00, 0x64, 0x00, 0x02, 0x85, 0xd4};

#endif


