#ifndef KEY_H
#define	KEY_H

#include <xc.h> 
#include <stdint.h>

/*set cup clock*/
#ifdef CUP_CLOCK_HZ
#define KEY_CLOCK_HZ         (CUP_CLOCK_HZ)
#else
/*set default clock*/
#define KEY_CLOCK_HZ            (4000000L)
#endif
/*use freertos*/

#define UseFreeRTOSInKey        (1)
/*use key by hardware interrupt*/
#define UseKeyInterrupt         (1)

/*key stutas*/
#define	NoKEY                    0x0
#define	ShortKEY                 0x1
#define	InvalidKEY               0x2
#define	LongKEY                  0x3

/*set key1 IO:S1Add CN16*/
#define SetKey1Tris             TRISDbits.TRISD7
#define ReadKey1State           PORTDbits.RD7
#define SetKey1ANS              ANSDbits.ANSD7
/*set key2 IO:S2Swift CN15*/
#define SetKey2Tris             TRISDbits.TRISD6
#define ReadKey2State           PORTDbits.RD6
#define SetKey2ANS              ANSDbits.ANSD6
/*set key3 IO:S3Setting CN14*/
#define SetKey3Tris             TRISDbits.TRISD5 
#define ReadKey3State           PORTDbits.RD5
//#define SetKey3ANS              ANSDbits.ANSD5


/*set delay const*/
#if (KEY_CLOCK_HZ == 2000000)
#define DELAY10MS                4251 
#define DELAY100MS               29761         
#elif (KEY_CLOCK_HZ == 4000000)
#define DELAY10MS                4251              
#define DELAY100MS               40900             
#endif

/*IO ³õÊ¼»¯*/
extern void vKeyInit(void);
/*É¨Ãè°´¼ü*/
extern void vKeyScan(void* vKeyState);
/*keyhandle*/
extern void vKeyUserFunction(unsigned char ucKeyState,unsigned char*);
#endif	/* XC_HEADER_TEMPLATE_H */
