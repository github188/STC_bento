/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           board.c
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        ����֧��       
********************************************************************************************************/


#include "..\config.h"




/*********************************************************************************************************
** Function name:     	delayMs
** Descriptions:	    ������ʱ����
** input parameters:    ms ��λ����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

void delayMs(unsigned int ms)
{	 
	 unsigned char idata i;
	 while(ms--)
	 {	 
	 	for(i=124;i>0;i--);      //124*8+10=1002us
	 }
}

/*********************************************************************************************************
** Function name:     	delay100us
** Descriptions:	    100us��ʱ����
** input parameters:    ms ��λ����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void delay100us(void)		//@11.0592MHz
{
	unsigned char idata i;
	_nop_();
	i = 43;
	while (--i);
}


/*********************************************************************************************************
** Function name:     	xorCheck
** Descriptions:	    
** input parameters:    
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
uchar xorCheck(uchar *ptr,uchar len)
{
	uchar i,crc = 0;
	for(i = 0;i < len;i++)
		crc ^= ptr[i];
		
	return crc;	
}




/*********************************************************************************************************
** Function name:     	uartInit
** Descriptions:	    ���ڳ�ʼ�� ��������1 2
** input parameters:    ��
** output parameters:   ��
** Returned value:      0-ʧ�� 1-�ɹ�
*********************************************************************************************************/
uchar uartInit(void)
{
	uart1Clear();
	uart2Clear();
	
	SCON  = 0x40;
	REN	  = 1;
	BRT   = -(11059200/32/UART1_BAUD);
	ES 	  = 0;
	S2CON = 0x40;
	BRT   = -(11059200/32/UART2_BAUD);
	AUXR  = 0x15;					// T0x12,T1x12,UART_M0x6,BRTR,S2SMOD,BRTx12,EXTRAM,S1BRS

	AUXR1 = AUXR1&0xef;
	SCON  = 0x50;
	S2CON = 0x50;	
	IE2   = 0x01;//������2���ж�
	ES	  = 1;						//20130328��ʼ�������ж�
	EA    = 1;


	
	return 1;
}



/*********************************************************************************************************
** Function name:     	InitGpio
** Descriptions:	    ��ʼ���������IO
** input parameters:    ��	    
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void InitGpio(void)
{
    P0M1 = 0x00;
    P0M0 = 0xff;
    P1M1 = 0x40;	// 01000000b
    P1M0 = 0xf0;	// 10110000b
    P2M1 = 0x00;
    P2M0 = 0xff;
    P3M1 = 0x00;
    P3M0 = 0x0C;
}



void systemInit(void)
{
	InitGpio();
	//spi_init();
	//uartInit();
	uart1Init();
	uart2Init();
	
	timer0Init();
	timer1Init();
}

