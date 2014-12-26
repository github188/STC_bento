/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           timer.c
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        ��ʱ���ж�        
********************************************************************************************************/
#include "..\config.h"

#define T10MS 			(0xDC00) //(65536 - 11059200 / 12 / 100)  == 0xDC00

uchar data tick;
uchar data second;

uchar data tick1;
uchar data second1;

ST_TIMER  xdata timer;
ST_TIMER1  xdata timer1;
/*********************************************************************************************************
** Function name:     	timer0Init
** Descriptions:	    ��ʱ��0��ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void timer0Init(void)
{
	AUXR &= 0x7F;// ��ʱ��ʱ���趨Ϊ12T ģʽ
	TMOD &= 0xF0;
	TMOD |= 0x01;//set timer0 as 16bit mode
	TL0 = T10MS;
    TH0 = T10MS >> 8;
	tick = 0;
	second = 0;
	TR0 = 1; //timer0 start running
	ET0 = 1;//enable timer0 interrupt
	EA = 1;//enable global interrupt
	delayMs(5);
}


/*********************************************************************************************************
** Function name:     	timer0_isr
** Descriptions:	    ��ʱ��0�жϷ������	 ����10ms����ʱ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void timer0_ISR( void ) interrupt 1 using 1 
{
	TL0 = T10MS;
    TH0 = T10MS >> 8;
	tick++;
	if(tick >= 100)
	{
		tick = 0;
		if(second > 0)
			second--;
		if(timer.cp_uart)
			timer.cp_uart--;
	}
}




/*********************************************************************************************************
** Function name:     	timer1Init
** Descriptions:	    ��ʱ��1��ʼ��  10ms��ʱ��
** input parameters:    
** output parameters:   
** Returned value:      
*********************************************************************************************************/
void timer1Init(void) 				
{
	AUXR &= 0xBF;// ��ʱ��ʱ���趨Ϊ12T ģʽ
	TMOD &= 0x0F;
    TMOD |= 0x10;
	TH1   = 0xDC;
	TL1   = 0x00;

	tick1 = 0;
	second1 = 0;
	
	ET1 = 1;
	TR1   = 1;
	EA = 1;
	delayMs(5);
}



/*********************************************************************************************************
** Function name:     	Timer1ISR
** Descriptions:	    ��ʱ��1�жϷ������	 ����10ms����ʱ��
** input parameters:    
** output parameters:   
** Returned value:      
*********************************************************************************************************/
void timer1_ISR(void) interrupt 3		
{

	TH1 = 0xDC;
	TL1 = 0x00;
	tick1++;
	if(timer1.uart1_recv)
		timer1.uart1_recv--;
	if(timer1.uart2_recv)
		timer1.uart2_recv--;
	if(timer1.uart2_radio)
		timer1.uart2_radio--;
	if(tick1 >= 100)
	{
		tick1 = 0;
		if(second1> 0)
			second1--;
		
	}

}

