#include "HL6528.h"
#include <string.h>
//#include <math.h>
#include <stdlib.h>
#include  <libq.h>
#include "WCG.h"
#include "Common.h"
//#include "includes.h"
//#include <stdbool.h>
//#include "cJSON.h"


//extern OS_EVENT* sem1, *sem2; //上线拨号任务标志

//struct ATCommand {
const uint8_t K3[] = {"AT&K3\r\n"}; //{"AT&K3\r\n"};
const uint8_t D1[] = {"AT&D1\r\n"}; //{"AT&K3\r\n"};
const uint8_t AT[] = {"AT\r\n"};
const uint8_t CREG_2[] = {"AT+CREG=2\r\n"};
const uint8_t OK[] = {"OK"};
const uint8_t CPIN[] = {"AT+CPIN?\r\n"};
const uint8_t READY[] = {"+CPIN: READY"};
const uint8_t CIMI[] = {"AT+CIMI\r\n"};
const uint8_t CREG[] = {"AT+CREG?\r\n"};
const uint8_t CGREG[] = {"AT+CGREG?\r\n"};
const uint8_t CREG_5[] = {" 5,"};
const uint8_t CREG_1[] = {" 1,"};
const uint8_t CSCA[] = {"AT+CSCA\r\n"};
//const uint8_t KCNXCFG[] = {"AT+KCNXCFG"};
const uint8_t KCNXCFG[] = {"AT+KCNXCFG=1,\"GPRS\",\"CMNET\"\r\n"};
const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"139.196.122.159\",5080\r\n"};
const uint8_t KTCPCFG2[] = {"AT+KTCPCFG=1,0,\"128.138.141.172\",13\r\n"};
uint8_t KTCPCFG1[] = {"AT+KTCPCFG=1,0,\"183.230.140.140\",11811\r\n"};
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.246.74.68\",5070\r\n"};//TR 
//const uint8_t KTCPCFG[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n"};//移动ONENET
//AT+KTCPCFG=1,0,"128.138.141.172",13
const uint8_t KTCPSTART[] = {"AT+KTCPSTART=1\r\n"};
const uint8_t CONNECT[] = {"CONNECT"};
const uint8_t KTCPCLOSE[] = {"AT+KTCPCLOSE=1,1\r\n"};
const uint8_t KTCPDEL[] = {"AT+KTCPDEL=1\r\n"};

extern volatile uint8_t gT3flag;
extern void GetTimeByNet(uint8_t *, uint8_t);
//static bool HL6528SendCmd(const uint8_t *ss, const uint8_t* cs, const uint8_t* cs1, const uint8_t csl, const uint8_t cnt);

void HL6528_Init(void) {
    //初始化端口
    PWRON_TRIS = 0; //PWN_ON 6528芯片电源控制
    PWR_TRIS = 0; //外部控制6528芯片电源
    DSR_TRIS = 0; //数据设备请求    
    DTR_TRIS = 0; //数据终端请求
    RTS_TRIS = 0; //请求发送数据
    CTS_TRIS = 0; //请求接受数据  
    PWR = 0;
    PWRON = 0;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
    //    UART2_Init();
}

/*输入变量：发送字符串地址ss、接受字符串、接受字符串长度、发送字符串长度、对比字符串地址、对比字符串长度、发送间隔时间、发送次数**/
static bool HL6528SendCmd(const uint8_t *sendstr, const uint8_t* comparestr, const uint8_t comparestrlen,
        const uint8_t cnt, const uint8_t ms100) {
    uint8_t send_cnt = 0, get_bytes = 0;
    bool b_sta = false;
    //    StrCmp stcp;
    uint8_t tmp[256];

    memset(tmp, 0, 100);

    do {
        send_cnt += 1;
        UART2_SendString(sendstr); //发送AT指令 
        if (WCGCON1bits.TestGPRSShow) {
            RS485SendString1("\r\nSend:");
            RS485SendString1(sendstr);
        }
        gT3flag = 0;
        IEC0bits.T3IE = 1;
        StartTMR3(ms100);
        while (!gT3flag) {
            Idle(); //进入休眠模式
            U2Rx4Byte();
            while (BufferRead_UART2(tmp + get_bytes))//获取剩余字节
                get_bytes++;
            if (get_bytes >= comparestrlen + 2) {
                if (Str_Find_Head(tmp, comparestr, get_bytes, comparestrlen)) {//判断第一个字节            
                    b_sta = true;
                    break;
                }
            }
        }
        gT3flag = 0;
        IEC0bits.T3IE = 0;
        StopTMR3();
        //        Delay100ms(ms100); //(0, 0, 3, 0); //延时1s        
        if (WCGCON1bits.TestGPRSShow) {
            if (get_bytes) {
                RS485SendString1("\r\nReceive:");
                RS485SendString(tmp, get_bytes);
                RS485SendString1("\r\n");
            } else
                RS485SendString1((uint8_t*) "No Receive!\n"); //发送AT指令 
        }
        get_bytes = 0;
        if (b_sta)
            break;
    } while (cnt > send_cnt);
    return b_sta;
}

static bool HL6528SendCREG(const uint16_t ms100) {
    uint8_t/* send_cnt = 0,*/ get_bytes = 0;
    bool b_sta = false;
    //    StrCmp stcp;
    uint8_t tmp[256];

    memset(tmp, 0, 100);

    //    do {
    //        send_cnt += 1;
    UART2_SendString(CREG); //发送AT指令 
    if (WCGCON1bits.TestGPRSShow) {
        RS485SendString1("\r\nSend:");
        RS485SendString1(CREG);
    }
    gT3flag = 0;
    IEC0bits.T3IE = 1;
    StartTMR3(ms100);
    while (!gT3flag) {
        Idle(); //进入休眠模式
        U2Rx4Byte();
        while (BufferRead_UART2(tmp + get_bytes))//获取剩余字节
            get_bytes++;
        if (get_bytes >= +2) {
            if (Str_Find_Head(tmp, CREG_5, get_bytes, sizeof (CREG_5) - 1)) {//判断第一个字节            
                b_sta = true;
                break;
            } else if (Str_Find_Head(tmp, CREG_1, get_bytes, sizeof (CREG_1) - 1)) {//判断第一个字节            
                b_sta = true;
                break;
            }
        }
    }
    gT3flag = 0;
    IEC0bits.T3IE = 0;
    StopTMR3();
    //        Delay100ms(ms100); //(0, 0, 3, 0); //延时1s        
    if (WCGCON1bits.TestGPRSShow) {
        if (get_bytes) {
            RS485SendString1("\r\nReceive:");
            RS485SendString(tmp, get_bytes);
            RS485SendString1("\r\n");
        } else
            RS485SendString1((uint8_t*) "No Receive!\n"); //发送AT指令 
    }
    //        if (b_sta)
    //            break;
    //    } while (cnt > send_cnt);
    U2Rx4Byte();
    ClrUART2Buf(); //BufferRead_UART2);
    return b_sta;
}

/*输入变量：发送字符串地址ss、接受字符串、接受字符串长度、发送字符串长度、对比字符串地址、对比字符串长度、发送间隔时间、发送次数**/
static bool HL6528SendTCPStart(const uint8_t cnt, const uint8_t ms100) {
    uint8_t send_cnt = 0, get_bytes = 0;
    bool b_sta = false;
    //    StrCmp stcp;
    uint8_t tmp[256];

    memset(tmp, 0, 100);

    do {
        send_cnt += 1;
        UART2_SendString(KTCPSTART); //发送AT指令 
        if (WCGCON1bits.TestGPRSShow) {
            RS485SendString1("\r\nSend:");
            RS485SendString1(KTCPSTART);
        }
        gT3flag = 0;
        IEC0bits.T3IE = 1;
        StartTMR3(ms100);
        while (!gT3flag) {
            Idle(); //进入休眠模式
            U2Rx4Byte();
            while (BufferRead_UART2(tmp + get_bytes))//获取剩余字节
                get_bytes++;
            if (get_bytes >= sizeof (CONNECT) + 1) {
                if (Str_Find_Head(tmp, CONNECT, get_bytes, sizeof (CONNECT) - 1)) {//判断第一个字节  
                    b_sta = true;
                    break;
                }
            }
        }
        gT3flag = 0;
        IEC0bits.T3IE = 0;
        StopTMR3();
        //        Delay100ms(ms100); //(0, 0, 3, 0); //延时1s        
        if (WCGCON1bits.TestGPRSShow) {
            if (get_bytes) {
                RS485SendString1("\r\nReceive:");
                RS485SendString(tmp, get_bytes);
                RS485SendString1("\r\n");
            } else
                RS485SendString1((uint8_t*) "No Receive!\n"); //发送AT指令 
        }
        get_bytes = 0;
        if (b_sta) {
            Delay1s();
            U2Rx4Byte();
            while (BufferRead_UART2(tmp + get_bytes))//获取剩余字节
                get_bytes++;
            GetTimeByNet(tmp, get_bytes);
            break;
        }
    } while (cnt > send_cnt);
    return b_sta;
}

static void OpenHL6528(void) {
    PWR = 1;
    PWRON = 1;
    CTS = 0;
    RTS = 0;
    DSR = 0;
    DTR = 0;
}

static void CloseHL6528(void) {
    PWR = 0; //电源控制
    PWRON = 0; //电源关闭
    CTS = 0; //请求接受
    RTS = 0; //请求发送
    DSR = 0; //设备
    DTR = 0; //终端
}

static void CmdChangeData(void) {

    DSR = 1; //切换数据至AT命令 mark
    DTR = 1;
    Delay1s(); //(0, 0, 1, 0); //延时1s
    DSR = 0; //请求发送数据
    DTR = 0;
    Delay1s(); //(0, 0, 1, 0); //延时1s
}

uint8_t HL6528_DialingIsERR(uint8_t mode) {
    uint8_t sta;
    OpenHL6528();
    Delay1s();
    Delay1s();
    Delay1s();
    Delay1s();


    HL6528SendCmd("ATE0\r\n", OK, sizeof (OK) - 1, 3, 2);
    if (HL6528SendCmd(D1, OK, sizeof (OK) - 1, 1, 2)) {
        //U2Rx4Byte();
        ClrUART2Buf(); //BufferRead_UART2);
        if (HL6528SendCmd(CPIN, READY, sizeof (READY) - 1, 3, 5)) {
            ClrUART2Buf(); //BufferRead_UART2);
            if (HL6528SendCREG(500)) {//CREG, _5, _1, 2, 30, 5)) {//设置网络模式
                ClrUART2Buf(); //BufferRead_UART2);
                if (HL6528SendCmd(KCNXCFG, OK, sizeof (OK) - 1, 3, 2)) {
                    ClrUART2Buf(); //BufferRead_UART2);
                    //HL6528_GetIP_Port(); //刷新IP地址和端口号
                    if (mode == GETTIME) {
                        CopyDat(KTCPCFG1, KTCPCFG2, sizeof (KTCPCFG2));
                    } else {
                        HL6528_GetIP_Port();
                    }
                    if (HL6528SendCmd(KTCPCFG1, OK, sizeof (OK) - 1, 3, 10)) {
                        ClrUART2Buf(); //BufferRead_UART2);
                        if (mode == GETTIME) {
                            if (HL6528SendTCPStart(3, 10)) {
                                sta = 0;
                            } else {
                                sta = 6; //未开启TCP，
                            }
                        } else {
                            if (HL6528SendCmd(KTCPSTART, CONNECT, sizeof (CONNECT) - 1, 5, 30)) {
                                sta = 0;
                            } else {
                                sta = 6; //未开启TCP，
                            }
                        }
                    } else {
                        sta = 5; //设置TCP失败
                    }
                } else {
                    sta = 4; //设置APN的问题
                }
            } else {
                sta = 3; //手机信号未找到 电压不足可能导致
            }
        } else {
            sta = 2; //手机信号未找到 电压不足可能导致
        }
    } else {
        sta = 1; //模块损坏
    }
    //    WCGCON1bits.TestGPRSShow = 0;

    return sta;
}

void HL6528_Close(void) {
    uint8_t tmp[20];
    uint8_t get_bytes = 0;
    //    StrCmp stcp;
    ClrUART2Buf(); //BufferRead_UART2);
    //    do {
    CmdChangeData();
    U2Rx4Byte();
    while (BufferRead_UART2(tmp + get_bytes))//获取剩余字节
        get_bytes++;

    if (Str_Find_Head(tmp, "OK", get_bytes, 2)) //等待接受成功下线返回OK
        if (HL6528SendCmd(KTCPCLOSE, OK, sizeof (OK) - 1, 2, 5))//关闭并删除TCP的ID通道
            HL6528SendCmd(KTCPDEL, OK, sizeof (OK) - 1, 2, 5);
    Delay1s(); // (0, 0, 1, 0); //延时1s    
    CloseHL6528();
    UART2_Close();
}






//static void HL6528_IOStart(void) {
//    PWR = 1;
//    PWRON = 1;
//    CTS = 0;
//    RTS = 0;
//    DSR = 0;
//    DTR = 0;
//}
//
//static void HL6528_IOClose(void) {
//    PWRON = 0;
//    PWR = 0;
//    CTS = 1;
//    RTS = 1;
//    DSR = 1;
//    DTR = 1;
//}

void HL6528_GetIP_Port(void) {
    uint8_t net_addr[25] = {'\0'};
    uint8_t str_tmp[4] = {1, 2, 3, 4};
    uint8_t cnt;
    uint8_t all_bytes = 0;

    //获取网络地址
    all_bytes = my_itoa(WCGIPbits.IP3, net_addr);
    net_addr[all_bytes] = '.';
    net_addr[all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WCGIPbits.IP2, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[all_bytes ] = '.';
    net_addr[ all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WCGIPbits.IP1, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[all_bytes ] = '.';
    net_addr[ all_bytes + 1] = '\0';
    all_bytes = all_bytes + 1;

    all_bytes += my_itoa(WCGIPbits.IP0, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[ all_bytes ] = '"';
    net_addr[all_bytes + 1 ] = ',';
    net_addr[ all_bytes + 2] = '\0';
    all_bytes = all_bytes + 2;

    all_bytes += my_itoa(WCGPORT, str_tmp);
    strcat(net_addr, str_tmp);
    net_addr[ all_bytes ] = '\r';
    net_addr[ all_bytes + 1] = '\n';
    net_addr[ all_bytes + 2] = '\0';
    all_bytes = all_bytes + 2;
    //   uint8_t KTCPCFG1[] = {"AT+KTCPCFG=1,0,\"183.230.40.40\",1811\r\n\n"};
    for (cnt = 0; cnt < all_bytes; cnt++)
        *(KTCPCFG1 + 16 + cnt) = *(net_addr + cnt);
    //    return all_bytes;
}





