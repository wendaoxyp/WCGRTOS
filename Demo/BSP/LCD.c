#include "LCD.h"
#include "WCGDeBug.h"
#include "Common.h"
#include "WCGArg.h"
#ifdef DebugLCD
#include "Debug.h"
#endif

/*定义one num={"0123456789abcdef"};-:a |:b */
const uint8_t Data_Code[16] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71
};
const uint8_t LCD_Num12_Code[7] = {
    eN1A, eN1B, eN1C, eN1D, eN1E, eN1F, eN1G
};
const uint8_t LCD_Num34567_Code[7] = {
    eN3A, eN3B, eN3C, eN3D, eN3E, eN3F, eN3G
};
/*定义数字偏移量*/
const uint8_t LCD_NUM_OFFSET[7] = {0, 2, 0, 2, 4, 6, 8};

struct xLCDArg sLCDArg = {
    {0},
    {0},
    0, //MainPage1,
};


/************************************************定义函数*****************************/

/*************************************
 * Function: vLCDInit
 * Description: LCD initialization
 * Input: pvString,ucBytes
 * Output: void
 * notice: void
 *************************************/
void vLCDInit(void) {
    /*设置SEG0-15为段驱动引脚*/
    LCDSE0 = 0xFFFF;
    /*设置SEG16-17为段驱动引脚*/
    LCDSE1 = 0x0003;
    LCDDATA0 = LCDDATA1 = LCDDATA4 = LCDDATA5 = 0;
    LCDDATA8 = LCDDATA9 = LCDDATA16 = LCDDATA17 = 0;
    LCDREG = 0x0004;
    //	LCDREF=0x07F0;  //external
    /*internal regsistor ladder*/
    LCDREF = 0x805F;
    LCDPS = 0x0002;
    LCDREFbits.LCDCST = 0;
    /*use four common pin*/
    LCDCON = 0x800B;
}

/*************************************
 * Function: vLCDShowPoint
 * Description: 通过usSeg值,判断段码位置，并设置为bOperation;
 * Input: usSeg,ucBytes
 * Output: void
 * notice: ep:vLCDShowPoint(ePower) LCDDATA
 *************************************/

void vLCDShowPoint(uint16_t usSeg, bool bOperation) {
    uint8_t ucCom;
    uint8_t ucSeg;
    /*overflow 18*4=72*/
    if (usSeg > 71) {
        usSeg = 71;
    }

    ucCom = (((usSeg & 0x00FF) / LCDSEGSIZE) << 2); //获取公共码
    ucSeg = usSeg % LCDSEGSIZE; //获取段码

    /*根据公共端，设置段码*/
    if (ucSeg > 15) {
        ucCom += 1;
        ucSeg -= 16;
    }
    switch (ucCom) {
        case 0:
            LCD_Set(0, ucSeg, bOperation);
            break;
        case 1:
            LCD_Set(1, ucSeg, bOperation);
            break;
        case 4:
            LCD_Set(4, ucSeg, bOperation);
            break;
        case 5:
            LCD_Set(5, ucSeg, bOperation);
            break;
        case 8:
            LCD_Set(8, ucSeg, bOperation);
            break;
        case 9:
            LCD_Set(9, ucSeg, bOperation);
            break;
        case 12:
            LCD_Set(12, ucSeg, bOperation);
            break;
        case 13:
            LCD_Set(13, ucSeg, bOperation);
            break;
        case 16:
            LCD_Set(16, ucSeg, bOperation);
            break;
        case 17:
            LCD_Set(17, ucSeg, bOperation);
            break;
    }
}

/*************************************
 * Function: vLCDShowNum
 * Description: LCD show one Num 
 * Input: ucNum,ucPosition
 * Output: void
 * notice: parameter ucNum:0-9
 *         parameter ucPosition:0-6
 *************************************/

void vLCDShowNum(uint8_t ucNum, uint8_t ucPosition) {
    uint8_t ucCnt;
    bool bShowOrHide = SEGSHOW;

    if (ucNum > 9)
        ucNum = 9;
    if (ucPosition > 6)
        ucPosition = 6;

    /*shou Num in Seg,*/
    for (ucCnt = 0; ucCnt < 7; ucCnt++) {
        bShowOrHide = (Data_Code[ucNum] &(1 << ucCnt)); //如果已经找到了OxFF，则接下来的数据都是隐藏,并且跳过0xff
        if (ucPosition > 1)
            vLCDShowPoint(LCD_Num34567_Code[ucCnt] - LCD_NUM_OFFSET[ucPosition], bShowOrHide);
        else
            vLCDShowPoint(LCD_Num12_Code[ucCnt] + LCD_NUM_OFFSET[ucPosition], bShowOrHide);
    }
}

/*************************************
 * Function: vLCDShowBattery
 * Description:LCD show Battery Segmnet pin
 * Input: ucBatterySign
 * Output: void
 * notice: parameter:ucBatterySign
 *         0:ucBatterySign Frame
 *         1:one ucBatterySign
 *          ...
 *         3:Full ucBatterySign
 *************************************/

void vLCDShowBattery(uint8_t ucBatterySign) {
    unsigned char ucCnt;
    unsigned char ucNowSign;
    bool bNowState;

    if (ucBatterySign > 3)
        ucBatterySign = 3;
    vLCDShowPoint(eBattery0, SEGSHOW);
    ucNowSign = eBattery1;
    for (ucCnt = 0; ucCnt < 4; ucCnt++) {
        bNowState = (ucBatterySign > ucCnt) ? SEGSHOW : SEGHIDE;
        vLCDShowPoint(ucNowSign, bNowState);
        ucNowSign -= LCDSEGSIZE;
    }
}

/*************************************
 * Function: vLCDShowGPRSSign
 * Description: LCD show GPRS sign
 * Input: ucGPRSSign
 * Output: void
 * notice:  parameter:ucGPRSSign
 *          0:none GPRSSign
 *          1:one GPRSSign
 *          ...
 *          3:Full GPRSSign
 *************************************/

void vLCDShowGPRSSign(uint8_t ucGPRSSign) {
    unsigned char ucCnt;
    unsigned char ucNowSign;
    bool bNowState;

    if (ucGPRSSign > 4)
        ucGPRSSign = 4;
    ucNowSign = eSign0;
    for (ucCnt = 0; ucCnt < 4; ucCnt++) {
        bNowState = (ucGPRSSign > ucCnt) ? SEGSHOW : SEGHIDE;
        vLCDShowPoint(ucNowSign, bNowState);
        ucNowSign -= LCDSEGSIZE;
    }
}

/*************************************
 * Function: vLCDShowDigitalPoint
 * Description: 显示小数点
 * Input: ucPosition
 * Output: void
 * notice:  parameter:ucPosition
 *          0:12345
 *          1:1234.5
 *            ...
 *          4:12.3424
 *************************************/
void vLCDShowDigitalPoint(uint8_t ucPosition) {
    unsigned char ucCnt;
    unsigned char ucNowPosition;
    unsigned char ucDigitalPoint[4] = {eP1, eP2, eP3, eP4};
    bool bNowState;

    if (ucPosition > 4)
        ucPosition = 0;
    for (ucCnt = 1; ucCnt < 5; ucCnt++) {
        ucNowPosition = ucDigitalPoint[ucCnt - 1];
        bNowState = (ucPosition == ucCnt) ? SEGSHOW : SEGHIDE;
        vLCDShowPoint(ucNowPosition, bNowState);
    }
}

/*************************************
 * Function: vLCDShowNums
 * Description: LCD Show Nums,like 123412
 * Input: ulNums,bFirstZeroshow
 * Output: void
 * notice: 
 *************************************/

void vLCDShowNums(uint32_t ulNums, bool bFirstZeroshow) {
    char cCnt; //
    uint8_t ucNumTmep;
    bool bIsFindHead = false;

    vLCDClearNums();
    /*if ulNums equal zero , LCD show "0"*/
    if (ulNums > 9999999L)
        ulNums = 9999999L;
    /*获取数字位数*/
    for (cCnt = 6; cCnt >= 0; cCnt--) {
        ucNumTmep = (unsigned char) ((unsigned long) (ulNums / pow(10, cCnt)) % 10);
        /*find first*/
        if (ucNumTmep&&!bIsFindHead) {
            bIsFindHead = true;
        }
        /*all show|| first not zero num finded || only zero*/
        if (bFirstZeroshow || bIsFindHead || ((!cCnt)&&(!ucNumTmep))) {
            vLCDShowNum(ucNumTmep, cCnt);
        }
    }
}

/*************************************
 * Function: vLCDClearNums
 * Description: LCD Clear Nums,vLCDShowNums(1234567L, FristZeroShow);
 * Input: void
 * Output: void
 * notice: number last bit must add L
 *************************************/

void vLCDClearNums(void) {
    unsigned char x, y;
    unsigned char ucOffset;

    /*清楚字母部分*/
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 7; x++) {
            ucOffset = (y < 2) ? (LCD_Num12_Code[x] + LCD_NUM_OFFSET[y]) : (LCD_Num34567_Code[x] - LCD_NUM_OFFSET[y]);
            vLCDShowPoint(ucOffset, SEGHIDE);
        }
    }
    /*clear digital piont*/
    vLCDShowDigitalPoint(0);
}

/*************************************
 * Function: vLCDClearScreen
 * Description: LCD clear Screen
 * Input: void
 * Output: void
 * notice: 
 *************************************/

void vLCDClearScreen(void) {
    uint16_t lcd_x = 0, lcd_y = 0;
    for (lcd_y = 0; lcd_y < 4; lcd_y++)
        for (lcd_x = 0; lcd_x < LCDSEGSIZE; lcd_x++)
            vLCDShowPoint(lcd_x + lcd_y * LCDSEGSIZE, SEGHIDE);
}

/*************************************
 * Function: vLCDShowScreen
 * Description: LCD show Screen
 * Input: LCDArg
 * Output: void
 * notice: use Global varible sLCDArg
 *************************************/

void vLCDShowScreen(void) {
    /*clear screen*/
    vLCDClearScreen();
    /*show nums*/
    if (sLCDArg.sLCDArg1.num0 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num0, 0);
    if (sLCDArg.sLCDArg1.num1 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num1, 0);
    if (sLCDArg.sLCDArg1.num2 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num2, 0);
    if (sLCDArg.sLCDArg1.num3 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num3, 0);
    if (sLCDArg.sLCDArg1.num4 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num4, 0);
    if (sLCDArg.sLCDArg1.num5 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num5, 0);
    if (sLCDArg.sLCDArg1.num6 < 0xa)
        vLCDShowNum(sLCDArg.sLCDArg1.num6, 0);
    /*show Vb*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg1.Vb);
    /*show Qm*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg1.Qm);
    /*show charge*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg1.Charge);
    /*show error*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg1.Error);
    /*show sign*/
    vLCDShowGPRSSign(sLCDArg.sLCDArg2.Sign);
    /*show battery*/
    vLCDShowGPRSSign(sLCDArg.sLCDArg2.Battery);
    /*show cc*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg2.CC);
    /*show m3h*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg2.M3H);
    /*show Kpa*/
    vLCDShowPoint(eBackword, sLCDArg.sLCDArg2.KPa);
    /*show digital point*/
    vLCDShowDigitalPoint(sLCDArg.sLCDArg2.Point);
}