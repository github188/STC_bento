/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart1.c
** Last modified Date:  2012-10-08
** Last Version:        No
** Descriptions:        ����1�������                     
**------------------------------------------------------------------------------------------------------
** Created by:          chensunwei
** Created date:        2012-10-08
** Version:             V1.0
** Descriptions:        The original version        
********************************************************************************************************/
#include "..\config.h"
#include "uart2.h"



uchar xdata  uart2RxBuf[UART2_BUF_SIZE];//���ջ�����
uchar xdata   uart2Rd;//������������
uchar xdata   uart2Wd;//������д����

unsigned char uart2Init(void)
{
	uart2Clear();
	S2CON = 0X50;     //8λ�ɱ䲨���ʣ�����żУ�� ��������ַ�
	BRT = -(FCLIK/32/UART2_BAUD);;//�����ʷ�����װ��
	AUXR = 0x15;
	IE2 = 0X01;         //������2�ж�
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
** Descriptions:	    ����һ�ֽ�����
** input parameters:    ch ���͵��ֽ�
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:	    �����ַ���
** input parameters:    str �����ַ���ָ�� len ���ͳ���
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

void uart2PutStr(uchar *str,uint len)
{
	uint i;
	for(i = 0;i < len;i++)
		uart2PutChar(str[i]);				
}

/*********************************************************************************************************
** Function name:     	uartIsEmpty
** Descriptions:	    �жϽ��ջ�������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
uchar uart2IsEmpty(void)
{
	return  (uart2Rd == uart2Wd);
}

/*********************************************************************************************************
** Function name:     	uartGetChar
** Descriptions:	    ����һ�ֽ�����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
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
** Descriptions:	    �崮�ڻ�����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

void uart2Clear(void)
{
	uart2Wd = 0;
	uart2Rd = 0;
}




/*****************************************END OF FILE****************************************************/
