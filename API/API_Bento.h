/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           API_bento.h
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        便利柜驱动板通信协议        
********************************************************************************************************/
#ifndef _API_BENTO_H_
#define _API_BENTO_H_


#define BT_HEAD		0xC7
#define BT_HEAD_LEN 5
#define BT_CRC_LEN  2

/*********************************************************************************************************
** 协议包头索引标示
*********************************************************************************************************/
#define ID_HEAD  		0
#define ID_LEN   		1
#define ID_MT    		2
#define ID_SN			3
#define ID_INFO      	4




#define BT_BUF_SIZE  	16


typedef struct _st_bt_data_{

	unsigned char  req;
	unsigned char  rdata[BT_BUF_SIZE];
	unsigned char  rlen;
	unsigned char  wdata[BT_BUF_SIZE];
	unsigned char  wlen;
}ST_BT_DATA;





void BT_task(void);
#endif
