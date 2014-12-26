/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart.h
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        ´®¿ÚÇý¶¯        
********************************************************************************************************/
#ifndef _UART1_H_
#define _UART1_H_


#define UART1_BAUD		(9600) 


void  uart1PutChar( uchar ch );
void uart1PutStr(uchar *str,uint len);
uchar uart1GetChar(void);
uchar uart1IsNotEmpty(void);
void uart1Clear(void);
unsigned char uart1Init(void);
void trace(unsigned char *format,...);
#endif