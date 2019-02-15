#ifndef WCGARG_H
#define WCGARG_H

enum xScreenID {
    eMainPage1 = 0, ePasswordPage = 1, eSetPage1 = 2, eSetPage2 = 3, eSetPage3 = 4,
    eSetPage4 = 5, eSetPage5 = 6, eSetPage6 = 7, eSetPage7 = 8, eSetPage8 = 9, eSetPage9 = 10,
    eMainPage2 = 11, eMainPage3 = 12
    /* Other page SetPage2 = 3,*/
};
#define MaxScreenPage      13

extern void vArgShowInLCD(void*);



#endif

