#include "Debug.h"

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



