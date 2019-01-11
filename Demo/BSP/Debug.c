#include "Debug.h"

/*************************************
 * Function: vDeBugPrintString
 * Description: print char by setting bytes
 * Input: pvString,ucBytes
 * Output: void
 * notice: can print 0x00
 *************************************/
void vDeBugPrintString(void *pvStrings, uint8_t ucBytes) {
    vDebugSendString((uint8_t*) pvStrings, ucBytes);
}

/*************************************
 * Function: vDeBugPrintInformation
 * Description: print string 
 * Input: pvString
 * Output: void
 * notice: print stop by 0x00
 *************************************/
void vDeBugPrintInformation(void *pvStrings) {
    uint8_t* pucFirstChar;

    pucFirstChar = (uint8_t*) pvStrings;
    while (*pucFirstChar != '\0') {
        vDebugSendChar(*pucFirstChar);
        pucFirstChar += 1;
    }
    vDebugSendChar('\n');
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
    uint8_t* pucFirstChar;

    pucFirstChar = (uint8_t*) pvStrings;
    while (*pucFirstChar != '\0') {
        vDebugSendChar(*pucFirstChar);
        pucFirstChar += 1;
    }
    ucNumsStringLength = my_itoa(usNums, ucNumsString);
    vDebugSendString(ucNumsString, ucNumsStringLength);
    vDebugSendChar('\n');
}



