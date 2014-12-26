/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart1.c
** Last modified Date:  2012-10-08
** Last Version:        No
** Descriptions:        串口1相关驱动                     
**------------------------------------------------------------------------------------------------------
** Created by:          chensunwei
** Created date:        2012-10-08
** Version:             V1.0
** Descriptions:        The original version        
********************************************************************************************************/
#include "..\config.h"
#include "uart2.h"



uchar xdata  uart2RxBuf[UART2_BUF_SIZE];//接收缓冲区
uchar xdata   uart2Rd;//缓冲区读索引
uchar xdata   uart2Wd;//缓冲区写索引

unsigned char uart2Init(void)
{
	uart2Clear();
	S2CON = 0X50;     //8位可变波特率，无奇偶校验 允许接受字符
	BRT = -(FCLIK/32/UART2_BAUD);;//波特率发生器装载
	AUXR = 0x15;
	IE2 = 0X01;         //允许串口2中断
	EA	 =	1;
	return 1;
}



void uart2_isr( void ) interrupt 8
{
	
	if(S2CON & S2RI)//recv isr
	{
		S2CON &= ~S2RI;
		uart2RxBuf[uart2Wd] = S2BUF;		
		uart2Wd = (++uart2Wd % UART2_BUF_SIZE);	
	}

	if(S2CON & S2TI)
	{
		S2CON &= ~S2TI;
	}

}


/*********************************************************************************************************
** Function name:     	uartPutChar
** Descriptions:	    发送一字节数据
** input parameters:    ch 发送的字节
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart2PutChar(uchar ch)
{

	IE2 = 0x00;	
	S2BUF=ch;
	while((S2CON&S2TI)==0);	//Wait for send ok
	S2CON&=~S2TI;			//Clear transmit busy flag
	IE2 = 0x01;	
}



/*********************************************************************************************************
** Function name:     	uartPutStr
** Descriptions:	    发送字符串
** input parameters:    str 发送字符串指针 len 发送长度
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart2PutStr(uchar *str,uint len)
{
	uint i;
	for(i = 0;i < len;i++)
		uart2PutChar(str[i]);				
}

/*********************************************************************************************************
** Function name:     	uartIsEmpty
** Descriptions:	    判断接收缓冲区空
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uchar uart2IsEmpty(void)
{
	return  (uart2Rd == uart2Wd);
}

/*********************************************************************************************************
** Function name:     	uartGetChar
** Descriptions:	    接收一字节数据
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

uchar uart2GetChar(void)
{
	uchar ch;
	ch =  uart2RxBuf[uart2Rd];
	uart2Rd = (++uart2Rd % UART2_BUF_SIZE);	
	return ch;
}



/*********************************************************************************************************
** Function name:     	uartClear
** Descriptions:	    清串口缓存区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

void uart2Clear(void)
{
	uart2Wd = 0;
	uart2Rd = 0;
}




/*****************************************END OF FILE****************************************************/
