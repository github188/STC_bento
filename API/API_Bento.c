/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           API_bento.c	 
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        便利柜通信协议接口  所有函数均已BT 开头 即 bento   
********************************************************************************************************/
#include "..\config.h"




static ST_BT_DATA xdata st_data;

static unsigned char xdata address = 0x01;

/*********************************************************************************************************
** Function name:     	BT_uart1_send
** Descriptions:	    串口1发送数据接口
** input parameters:    wdata 发送缓冲区指针  wlen 发送数据长度
** output parameters:   无
** Returned value:      1成功  0失败
*********************************************************************************************************/
unsigned char BT_uart1_send(unsigned char *wdata,unsigned char wlen)
{
	unsigned char xdata index = ID_INFO;
	if(wdata == NULL)
		return 0;
	wdata[ID_HEAD] = BT_HEAD;
	wdata[ID_LEN] = index + 1 + wlen;
	//wdata[ID_SN] =
	uart1Clear();
	uart1PutStr(wdata,wlen);
	return 1;
}

/*********************************************************************************************************
** Function name:     	BT_uart1_recv
** Descriptions:	    串口1接收数据接口
** input parameters:    rdata 接收缓冲区指针  rlen 接收数据长度
** output parameters:   无
** Returned value:      0 无数据接收 1接收正确数据  2接收数据错误
*********************************************************************************************************/

unsigned char BT_uart1_recv(unsigned char *rdata,unsigned char *rlen)
{
	unsigned char xdata temp,index = 0;
	unsigned int xdata crc;
	*rlen = 0;
	if(!uart1IsNotEmpty())
	{
		return 0;
	}
	temp = uart1GetChar();//head
	if(temp != BT_HEAD)
		return 2;
	rdata[index++] = temp;

	temp = uart1GetChar();//len
	if(temp < BT_HEAD_LEN)  
		return 2;
	rdata[index++] = temp;
	
	timer1.uart1_recv = 20;// 500ms recver timeout
	while(timer1.uart1_recv)
	{	
		if(uart1IsNotEmpty())
		{
			rdata[index++] = uart1GetChar();
			if(index >= (rdata[ID_LEN] + BT_CRC_LEN))
			{
				crc = xorCheck(rdata,rdata[ID_LEN]);
				if(crc != INTEG16(rdata[ID_LEN],rdata[ID_LEN + 1]))
					return 2;//crc err
				*rlen = rdata[ID_LEN] + BT_CRC_LEN;		
				return 1;
			}
				
		}
	}
	
	return 2;
}











/*********************************************************************************************************
** Function name:     	BT_uart2_send
** Descriptions:	    串口2发送数据接口
** input parameters:    wdata 发送缓冲区指针  wlen 发送数据长度
** output parameters:   无
** Returned value:      1成功  0失败
*********************************************************************************************************/
unsigned char BT_uart2_send(unsigned char *wdata,unsigned char wlen)
{
	unsigned char xdata index = ID_INFO;
	if(wdata == NULL)
		return 0;
	wdata[ID_HEAD] = BT_HEAD;
	wdata[ID_LEN] = index + 1 + wlen;
	//wdata[ID_SN] =
	uart2Clear();
	uart2PutStr(wdata,wlen);
	return 1;
}




/*********************************************************************************************************
** Function name:     	BT_uart2_recv
** Descriptions:	    串口2接收数据接口
** input parameters:    rdata 接收缓冲区指针  rlen 接收数据长度
** output parameters:   无
** Returned value:      0 无数据接收 1接收正确数据  2接收数据错误
*********************************************************************************************************/

unsigned char BT_uart2_recv(unsigned char *rdata,unsigned char *rlen)
{
	unsigned char xdata temp,index = 0;
	unsigned int xdata crc;
	*rlen = 0;
	if(uart2IsEmpty())
	{
		return 0;
	}
	temp = uart2GetChar();//head
	if(temp != BT_HEAD)
		return 2;
	rdata[index++] = temp;

	temp = uart2GetChar();//len
	if(temp < BT_HEAD_LEN)  
		return 2;
	rdata[index++] = temp;
	
	timer1.uart2_recv = 20;// 500ms recver timeout
	while(timer1.uart2_recv)
	{	
		if(!uart2IsEmpty())
		{
			rdata[index++] = uart2GetChar();
			if(index >= (rdata[ID_LEN] + BT_CRC_LEN))
			{
				crc = xorCheck(rdata,rdata[ID_LEN]);
				if(crc != INTEG16(rdata[ID_LEN],rdata[ID_LEN + 1]))
					return 2;//crc err

				*rlen = rdata[ID_LEN] + BT_CRC_LEN;	
				return 1;
			}
				
		}
	}
	
	return 2;
}



/*********************************************************************************************************
** Function name:     	BT_handle_req
** Descriptions:	    处理数据请求
** input parameters:    rdata 接收缓冲区指针  rlen 接收数据长度
** output parameters:   无
** Returned value:      0 无数据接收 1接收正确数据  2接收数据错误
*********************************************************************************************************/
unsigned char BT_handle_req(ST_BT_DATA *st_data)
{
	st_data = st_data;
	return 1;
}


unsigned char BT_isMacAddr(unsigned char addr)
{
	return (addr == address);
}

/*********************************************************************************************************
** Function name:     	BT_uart1_task
** Descriptions:	    串口1任务
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void BT_uart1_task()
{
	unsigned char xdata buf[4] = {0},index = 0,res;
		
	//轮训PC串口是否有数据
	res = BT_uart1_recv(st_data.rdata,&st_data.rlen);
	if(res == 1) //接收正确数据
	{	
		if(!BT_isMacAddr(st_data.rdata[ID_INFO]))//判断不是本机地址
		{
			BT_uart2_send(st_data.rdata,st_data.rlen);//否 通过串口2 广播出去 
			timer1.uart2_radio = 500;//5s timeout
			st_data.wdata[ID_INFO] = 0;//超时
			while(timer1.uart2_radio)
			{
				if(BT_uart2_recv(st_data.rdata,&st_data.rlen))//收到回应
				{
					st_data.wdata[ID_INFO] = 1;
					break;
				}
			}
			BT_uart1_send(st_data.wdata,st_data.wlen);//回应结果
		}
		else
		{
			//解析数据
			BT_handle_req(&st_data);//本机地址 直接处理命令  然后回应
			st_data.wdata[ID_INFO] = 1;
			BT_uart1_send(st_data.wdata,st_data.wlen);//回应结果
		}
		
		
	}
	else if(res == 2)//接收数据错误 考虑回应错误信息
	{
		res = res;
	}
	else//无数据接收
	{
		res = res;
	}
	
}


/*********************************************************************************************************
** Function name:     	BT_uart2_task
** Descriptions:	    串口2任务
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void BT_uart2_task()
{

	unsigned char xdata res;
	res = BT_uart2_recv(st_data.rdata,&st_data.rlen);//接收串口2数据 
	if(res == 1)//有回应 并且数据正确
	{
		if(BT_isMacAddr(st_data.rdata[ID_INFO]))//是否本机命令
		{
			res = BT_handle_req(&st_data);//处理命令 并发送回应
			st_data.wdata[ID_INFO] = 1;
			BT_uart2_send(st_data.wdata,st_data.wlen);
			
		}
		else//不是本机的命令直接抛弃
		{
			return;
		}
	}
	

}


/*********************************************************************************************************
** Function name:     	BT_task
** Descriptions:	    便利柜任务
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void BT_task(void)
{
	// 1.轮训串口1
	BT_uart1_task();
	// 2.轮训串口2
	BT_uart2_task();
	
}
