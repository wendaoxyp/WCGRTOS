#include "Debug.h"


/*define num to string*/
const unsigned char Num2Str[16] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/*************************************
 * Function: vDeBugPrintInformation
 * Description: print string 
 * Input: pvString
 * Output: void
 * notice: print stop by 0x00
 *************************************/
void vDeBugPrintInformation(void *pvStrings) {
    vDebugSendString(pvStrings);
    vDebugSendString("\n");
}

/*************************************
 * Function: vDeBugPrintStringAndNums
 * Description: print String and nums
 * Input: pvStrings,usNums
 * Output: void
 * notice: print String stop by 0x00,usNums range from 0 to 65536
 *************************************/

void vDeBugPrintStringAndNums(void *pvStrings, uint16_t usNums) {
    uint8_t ucNumsString[6] = {0, 0, 0, 0, 0, 0}, ucNumsStringLength = 0;
    /*print strings*/
    vDebugSendString(pvStrings);
    /*nums change strings*/
    ucNumsStringLength = my_itoa(usNums, ucNumsString);
    /*print nums*/
    vDebugSend(ucNumsString, ucNumsStringLength);
    vDebugSendString("\n");
}

/*************************************
 * Function: vDeBugPrintHexNums
 * Description: print String and nums
 * Input: pvStrings,usNums
 * Output: void
 * notice: print String stop by 0x00,usNums range from 0 to 65536
 *************************************/

void vDeBugPrintHexNums(void *pvStrings, uint8_t* pucNums, unsigned char ucBytes) {
    unsigned char ucCnt;
    unsigned char ucTmp;
    unsigned char ucNumsString[2];
    char cCh = ' ';
    /*print strings*/
    if (pvStrings != NULL)
        vDebugSendString(pvStrings);
    /*nums change strings and print*/
    for (ucCnt = 0; ucCnt < ucBytes; ucCnt++) {
        ucTmp = *(pucNums + ucCnt);
        /*low 4 bits*/
        ucNumsString[1] = Num2Str[ucTmp & 0x0f];
        /*high 4 bits*/
        ucNumsString[0] = Num2Str[ucTmp >> 4];
        /*print nums*/
        vDebugSend(ucNumsString, 2);
        vUART3Send((unsigned char *) &cCh, 1);
    }
    vDebugSendString("\n");
}





