/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           main.c
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        STC  C�������        
********************************************************************************************************/

#include "..\config.h"






/*********************************************************************************************************
** Function name:     	main
** Descriptions:	    ��ں���
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/

void main(void)
{
	systemInit();
	delayMs(500);
	delay100us();
	//FM_init();
	while(1)
	{
		trace("Hello my C51..\n");
		delayMs(500);
		while(1)
		{		
			BT_task();
		}
			
	}
			
}