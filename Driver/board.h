#ifndef _BOARD_H_
#define _BOARD_H_



#define FCLIK      11059200UL   /*使用22.1184M晶体*/



/*********************************************************************************************************
**定义通用宏函数
*********************************************************************************************************/

#define HUINT16(v)   	(((v) >> 8) & 0x0F)
#define LUINT16(v)   	((v) & 0x0F)
#define INTEG16(h,l)  	(((unsigned int)h << 8) | l)






void delayMs(unsigned int ms);
void delay100us(void);
uchar xorCheck(uchar *ptr,uchar len);
uchar uartInit(void);
void InitGpio(void);
void systemInit(void);
#endif