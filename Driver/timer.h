/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           timer.h
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        ��ʱ���ж�ͷ�ļ�        
********************************************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

typedef struct _st_timer_{

	volatile unsigned short cp_uart;//�������մ��ڳ�ʱ

}ST_TIMER;
extern ST_TIMER xdata timer;


extern uchar second;



typedef struct _st_timer1_{

	volatile unsigned short cp_uart;//�������մ��ڳ�ʱ
	volatile unsigned short uart1_recv;//����1���ճ�ʱ
	volatile unsigned short uart2_recv;//����2���ճ�ʱ
	volatile unsigned short uart2_radio;//����2�㲥��ʱ

}ST_TIMER1;
extern ST_TIMER1 xdata timer1;

extern uchar second1;
void timer0Init(void);
void timer1Init(void);
#endif