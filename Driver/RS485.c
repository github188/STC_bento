/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           RS485.c
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        485通信接口驱动       
********************************************************************************************************/
#include "..\config.h"


/*********************************************************************************************************
** Function name:     	SetRS485AsTxdMode
** Descriptions:	   
** input parameters:    
** output parameters:   
** Returned value:      
*********************************************************************************************************/
void SetRS485AsTxdMode(void)
{
	RS485TXDENABLE  = 1;
	delayMs(10);
}



/*********************************************************************************************************
** Function name:     	SetRS485AsRxdMode
** Descriptions:	    
** input parameters:    
** output parameters:   
** Returned value:     
*********************************************************************************************************/
void SetRS485AsRxdMode(void)
{
	RS485TXDENABLE  = 0;
}



