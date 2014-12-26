/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           API_channelProtocol.h
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        货道驱动板通信协议        
********************************************************************************************************/
#ifndef _API_CHANNEL_PROTOCOL_H_
#define _API_CHANNEL_PROTOCOL_H_

#define CP_FUNCTION_OPEN  0

#if (CP_FUNCTION_OPEN == 1)

#define CP_MAX_COLUMN		80//max column 1- 80 

//出货失败原因
#define CP_FAIL				0x01  //0000_0001 出货失败(0表示出货成功)
#define CP_BUSY	  			0x02  //0000_0010 驱动板忙标志
#define CP_NOT_PLACE   		0x04  //0000_0100 出货前电机没有在正确的位置
#define CP_NOT_MOVE    		0x08  //0000_1000 电机未转动
#define CP_NOT_RETURN  		0x10  //0001_0000 电机未到位( 规定的时间没有回到触发点)
#define CP_NOT_PASS    		0x20  //0010_0000 出货确认开启的情况下未检测到商品

#define CP_HOLE_ERR	   		0x80  //1000_0000 出货检测故障


typedef struct {
	uchar  head;
	uchar  len;
	uchar  sn;
	uchar  mt;
	uchar  column;
	uchar  status;
    uchar  data1;
	uchar  data2;
}ST_MSG_CP;


void CP_poll(void);

#endif
#endif