#ifndef WCGDEBUG_H
#define WCGDEBUG_H


/*if need Debug ,set ENABLE_DEBUG to 1*/
#define ENABLE_DEBUG              1
/*define test module,like LCD...*/
#if (ENABLE_DEBUG == 1)
/*if need debug LCD,change DebugLCD equal 1*/
#define DebugLCD                  0
#if (DebugLCD == 1)
#define TestSpecialSign           0
#define TestNum                   0
/*endif (DebugLCD == 1)*/
#endif
/*if need debug PCF8583,change DebugPCF8583 equal 1*/
#define DebugPCF8583              0
/*switch test which function*/
#if (DebugPCF8583 == 1)
#define TestReadTime              0
#define TestReadTimestamp         0
#define TestAlarm                 0
#define TestWriteReadRegister     0
/*endif (DebugPCF8583 == 1)*/
#endif

/*if need debug CAT24C512,change DebugCAT24C512 equal 1*/
#define DebugCAT24C512            0
/*swtich test which function*/
#if (DebugCAT24C512 == 1 )
#define TestReadByte              0
#define TestReadBytes             0
/*endif (DebugCAT24C512 == 1 )*/
#endif
/*endif (ENABLE_DEBUG == 1)*/
#endif 


extern void vDebugTaskHook(void);

#endif



