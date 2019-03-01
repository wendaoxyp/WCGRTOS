#ifndef _LCD_H
#define _LCD_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <xc.h>


/*定义段码总长*/
#define LCDSEGSIZE 18  
/*  pic MCU LCD control
COM Lines                      Segments
            |   0 to 15    |    16 to 31     |     32 to 47     |     48 to 64
0               LCDDATA0        LCDDATA1           LCDDATA2           LCDDATA3
                S00C0:S15C0     S16C0:S31C0        S32C0:S47C0        S48C0:S63C0
1               LCDDATA4        LCDDATA5           LCDDATA6           LCDDATA7
                S00C1:S15C1     S16C1:S31C1        S32C1:S47C1        S48C1:S63C1
2               LCDDATA8        LCDDATA9           LCDDATA10          LCDDATA11
                S00C2:S15C2     S16C2:S31C2        S32C2:S47C2        S48C2:S63C2
3               LCDDATA12       LCDDATA13          LCDDATA14          LCDDATA15
                S00C3:S15C3     S16C3:S31C3        S32C3:S47C3        S48C3:S63C3
4               LCDDATA16       LCDDATA17          LCDDATA18          LCDDATA19
                S00C4:S15C4     S16C4:S31C4        S32C4:S47C4        S48C4:S59C4
...
7               LCDDATA28       LCDDATA29          LCDDATA30          LCDDATA31
                S00C7:S15C7     S16C7:S31C7        S32C7:S47C7        S48C7:S59C7
 */

///*设置段码y位拉低*/
//#define  LCD_SetLow(x,y) (LCDDATA##x &= ~(1 << y)) 
///*设置段码y位拉高*/
//#define  LCD_SetHigh(x,y) (LCDDATA##x |= (1 << y))  
/*根据z的真假，判断设置段码y位状态*/
#define  LCDCOM(x)  (x/LCDSEGSIZE)
#define  LCDSEG(x)  (x%LCDSEGSIZE)
#define  LCD_Set(x,y,z) ((LCDDATA##x)=((z)?((LCDDATA##x) | (1 << y)):((LCDDATA##x) & ~(1 << y))))



/*            
 PIN	1       2       3       4       5       6       7       8       9           10      11
COM0	--      --      --      *       1A      1B      2A      2B      5v          B_none	Sign
COM1	--      --      *       --      1F      1G      2F      2G      ERROR       B_1     Sign1
COM2	--      *       --      --      1E      1C      2E      2C      backword	B_2     Sing2
COM3	*       --      --      --      1D      P1      2D      22      forword     B_3     Sing3
 * 
PIN     12      13      14      15      16      17      18      19      20      21      22
COM0	KPa     3A      3B      4A      4B      5A      5B      6A      6B		7A      7B
COM1	m3      3F      3G      4F      4G      5F      5G      6F      6G		7F      7G
COM2	/h      3E      3C      4E      4C      5E      5C      6E      6C		7E      7C
COM3	℃      3D		P3      4D      P4      5D              6D              7D
 */

/*设置段码真值表序号*/
enum LCD_truth_table {
    eN1D, eP1, eN2D, eP2, eBackword, eBattery3, eSign3, eNUL5, eN7D, eNUL1, eN6D, eNUL0, eN5D, eP4, eN4D, eP3, eN3D, eCC, //COM3 DATA0
    eN1E, eN1C, eN2E, eN2C, eForword, eBattery2, eSign2, eN7C, eN7E, eN6C, eN6E, eN5C, eN5E, eN4C, eN4E, eN3C, eN3E, ePerh, //Com2 DATA4
    eN1F, eN1G, eN2F, eN2G, eError, eBattery1, eSign1, eN7G, eN7F, eN6G, eN6F, eN5G, eN5F, eN4G, eN4F, eN3G, eN3F, em3, //COM1 DATA8
    eN1A, eN1B, eN2A, eN2B, ePower, eBattery0, eSign0, eN7B, eN7A, eN6B, eN6A, eN5B, eN5A, eN4B, eN4A, eN3B, eN3A, eKPa //COM0 DATA12           
};




/*设置段码的状态*/
#define FristZeroShow 1
#define FristZeroHide 0
#define SEGSHOW 1
#define SEGHIDE 0
/*hide 1 bit Nun*/
#define NUMHIDE 0x0A

struct xLCDArg1 {
    unsigned long num0 : 4;
    unsigned long num1 : 4;
    unsigned long num2 : 4;
    unsigned long num3 : 4;
    unsigned long num4 : 4;
    unsigned long num5 : 4;
    unsigned long num6 : 4; //27   
    unsigned long Vb : 1; //28
    unsigned long Qm : 1; //29
    unsigned long Charge : 1; //30
    unsigned long Error : 1; //31
};

struct xLCDArg2 {
    unsigned int Sign : 3; //2
    unsigned int Battery : 3; //5
    /*number cursor for set arg*/
    unsigned int Cursor : 3; //8
    unsigned int CC : 2; //10
    unsigned int M3H : 1; //11
    unsigned int KPa : 1; //12
    unsigned int Point : 3; //15    
};

struct xLCDArg {
    struct xLCDArg1 sLCDArg1;
    struct xLCDArg2 sLCDArg2;
    /*current Screen ID*/
    unsigned char ucScreenID;
    /*lcd refresh time*/
    unsigned int uiRefreshTime;
};
/*define LCDArg*/
extern struct xLCDArg sLCDArg;

/*初始化LCD，使用单片机内部LCD驱动*/
extern void vLCDInit(void);
/*show point*/
extern void vLCDShowPoint(uint16_t usSeg, bool bOperation);
/*show num*/
extern void vLCDShowNum(uint8_t ucNum, uint8_t ucPosition);
/*LCD显示电池电量*/
extern void vLCDShowBattery(uint8_t bat);
/*LCD显示符号*/
extern void vLCDShowGPRSSign(uint8_t sign);
/*LCD显示小数点*/
extern void vLCDShowDigitalPoint(uint8_t dp_pos);
/*LCD清除数字显示*/
extern void vLCDClearNums(void);
/*LCD显示数字*/
void vLCDShowNums(uint32_t ulNums, bool bFirstZeroshow);
/*LCD Clear Screen*/
extern void vLCDClearScreen(void);
/*LCD Show Screen*/
extern void vLCDShowScreen(void);

#endif


//enum LCD_truth_table {
//    N1D, P1, N2D, P2, backword, B_3, Sign3, CC, N3D, P3, N4D, P4, N5D, NUL0, N6D, NUL1, N7D, NUL5, //COM3 DATA0
//    N1E, N1C, N2E, N2C, forword, B_2, Sign2, __h, N3E, N3C, N4E, N4C, N5E, N5C, N6E, N6C, N7E, N7C, //Com2 DATA4
//    N1F, N1G, N2F, N2G, error, B_1, Sign1, m3, N3F, N3G, N4F, N4G, N5F, N5G, N6F, N6G, N7F, N7G, //COM1 DATA8
//    N1A, N1B, N2A, N2B, power, B_0, Sign0, KPa, N3A, N3B, N4A, N4B, N5A, N5B, N6A, N6B, N7A, N7B //COM0 DATA12           
//};


