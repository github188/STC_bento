/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           timer.h
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        定时器中断头文件        
********************************************************************************************************/

#ifndef _TIMER_H_
#define _TIMER_H_

typedef struct _st_timer_{

	volatile unsigned short cp_uart;//货道接收串口超时

}ST_TIMER;
extern ST_TIMER xdata timer;


extern uchar second;



typedef struct _st_timer1_{

	volatile unsigned short cp_uart;//货道接收串口超时
	volatile unsigned short uart1_recv;//串口1接收超时
	volatile unsigned short uart2_recv;//串口2接收超时
	volatile unsigned short uart2_radio;//串口2广播超时

}ST_TIMER1;
extern ST_TIMER1 xdata timer1;

extern uchar second1;
void timer0Init(void);
void timer1Init(void);
#endif