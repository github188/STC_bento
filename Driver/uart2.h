
#ifndef __UART2_H__
#define __UART2_H__

#define UART2_BAUD		(9600)
#define UART2_BUF_SIZE  (32)


#define S2RI			(0x01) //S2CON.0
#define S2TI			(0x02) //S2CON.1


#define S2RB8			(0x04) //S2CON.2
#define S2TB8			(0x08) //S2CON.3


sbit RS485TXDENABLE = P3^2;

void uart2PutChar(uchar ch);
void uart2PutStr(uchar *str,uint len);
uchar uart2IsEmpty(void);
uchar uart2GetChar(void);
void uart2Clear(void);
unsigned char uart2Init(void);

#endif




