/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart.c
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        串口驱动        
********************************************************************************************************/

#include "..\config.h"
#include "uart1.h"
#include <stdarg.h>


#define BUF_SIZE 	    32 
#define DATA_BIT  		8
#define VERIFY_BIT 	    0
#define STOP_BIT   		1







uchar xdata   uart1RxBuf[BUF_SIZE];//接收缓冲区
uchar xdata   uart1Rd;//缓冲区读索引
uchar xdata   uart1Wd;//缓冲区写索引

unsigned char uart1Init(void)
{
	uart1Clear();
	SCON  = 0X50; 		//8位可变波特率，无奇偶校验	
	BRT   = -(FCLIK/32/UART1_BAUD);
	AUXR  = 0x15; 
	REN   =	1;      		//允许接收
	ES    =	1;   			// 允许串口1中断
	EA    = 1;   		// 开总中断
	
	return 1;
}

void uart1_isr( void ) interrupt 4 using 1 
{
	if(RI)//recv isr
	{
		RI = 0;
		uart1RxBuf[uart1Wd] = SBUF;
		if(uart1Wd < (BUF_SIZE - 1))
			uart1Wd = uart1Wd + 1;
		else
			uart1Wd = 0;
	}
	if(TI)
	{
		TI = 0;
	}

}


/*********************************************************************************************************
** Function name:     	uartPutChar
** Descriptions:	    发送一字节数据
** input parameters:    ch 发送的字节
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart1PutChar(uchar ch)
{
	ES=0;
	TI=0;
	SBUF=ch;
	while(TI==0);
	TI=0;
	ES=1;

}



/*********************************************************************************************************
** Function name:     	uartPutStr
** Descriptions:	    发送字符串
** input parameters:    str 发送字符串指针 len 发送长度
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart1PutStr(uchar *str,uint len)
{
	uint i;
	for(i = 0;i < len;i++)
		uart1PutChar(str[i]);				
}

/*********************************************************************************************************
** Function name:     	uart1IsNotEmpty
** Descriptions:	    判断接收缓冲区不为空
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uchar uart1IsNotEmpty(void)
{
	return  (!(uart1Rd == uart1Wd));
}

/*********************************************************************************************************
** Function name:     	uartGetChar
** Descriptions:	    接收一字节数据
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

uchar uart1GetChar(void)
{
	uchar ch;
	ch =  uart1RxBuf[uart1Rd];
	uart1RxBuf[uart1Rd] = 0;
	uart1Rd++;
	if(uart1Rd >= BUF_SIZE )
		uart1Rd = 0;
	return ch;
}



/*********************************************************************************************************
** Function name:     	uartClear
** Descriptions:	    清串口缓存区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart1Clear(void)
{
	uart1Wd = 0;
	uart1Rd = 0;
}




/*********************************************************************************************************
** Function name:	    Trace
** Descriptions:	    调试Trace
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void trace(unsigned char *format,...)
{
	va_list arg_ptr;
	unsigned char xdata StringTemp[64];
	unsigned int xdata i;
	unsigned int xdata len;
	va_start(arg_ptr,format);
	len = vsprintf((char *)StringTemp,(const char *)format,arg_ptr);
	va_end(arg_ptr);
	for(i=0;i<len;i++)
	{
		uart1PutChar(StringTemp[i]);
	}	
}


