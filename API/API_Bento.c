/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           API_bento.c	 
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        ������ͨ��Э��ӿ�  ���к�������BT ��ͷ �� bento   
********************************************************************************************************/
#include "..\config.h"




static ST_BT_DATA xdata st_data;

static unsigned char xdata address = 0x01;

/*********************************************************************************************************
** Function name:     	BT_uart1_send
** Descriptions:	    ����1�������ݽӿ�
** input parameters:    wdata ���ͻ�����ָ��  wlen �������ݳ���
** output parameters:   ��
** Returned value:      1�ɹ�  0ʧ��
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
** Descriptions:	    ����1�������ݽӿ�
** input parameters:    rdata ���ջ�����ָ��  rlen �������ݳ���
** output parameters:   ��
** Returned value:      0 �����ݽ��� 1������ȷ����  2�������ݴ���
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
** Descriptions:	    ����2�������ݽӿ�
** input parameters:    wdata ���ͻ�����ָ��  wlen �������ݳ���
** output parameters:   ��
** Returned value:      1�ɹ�  0ʧ��
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
** Descriptions:	    ����2�������ݽӿ�
** input parameters:    rdata ���ջ�����ָ��  rlen �������ݳ���
** output parameters:   ��
** Returned value:      0 �����ݽ��� 1������ȷ����  2�������ݴ���
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
** Descriptions:	    ������������
** input parameters:    rdata ���ջ�����ָ��  rlen �������ݳ���
** output parameters:   ��
** Returned value:      0 �����ݽ��� 1������ȷ����  2�������ݴ���
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
** Descriptions:	    ����1����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void BT_uart1_task()
{
	unsigned char xdata buf[4] = {0},index = 0,res;
		
	//��ѵPC�����Ƿ�������
	res = BT_uart1_recv(st_data.rdata,&st_data.rlen);
	if(res == 1) //������ȷ����
	{	
		if(!BT_isMacAddr(st_data.rdata[ID_INFO]))//�жϲ��Ǳ�����ַ
		{
			BT_uart2_send(st_data.rdata,st_data.rlen);//�� ͨ������2 �㲥��ȥ 
			timer1.uart2_radio = 500;//5s timeout
			st_data.wdata[ID_INFO] = 0;//��ʱ
			while(timer1.uart2_radio)
			{
				if(BT_uart2_recv(st_data.rdata,&st_data.rlen))//�յ���Ӧ
				{
					st_data.wdata[ID_INFO] = 1;
					break;
				}
			}
			BT_uart1_send(st_data.wdata,st_data.wlen);//��Ӧ���
		}
		else
		{
			//��������
			BT_handle_req(&st_data);//������ַ ֱ�Ӵ�������  Ȼ���Ӧ
			st_data.wdata[ID_INFO] = 1;
			BT_uart1_send(st_data.wdata,st_data.wlen);//��Ӧ���
		}
		
		
	}
	else if(res == 2)//�������ݴ��� ���ǻ�Ӧ������Ϣ
	{
		res = res;
	}
	else//�����ݽ���
	{
		res = res;
	}
	
}


/*********************************************************************************************************
** Function name:     	BT_uart2_task
** Descriptions:	    ����2����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void BT_uart2_task()
{

	unsigned char xdata res;
	res = BT_uart2_recv(st_data.rdata,&st_data.rlen);//���մ���2���� 
	if(res == 1)//�л�Ӧ ����������ȷ
	{
		if(BT_isMacAddr(st_data.rdata[ID_INFO]))//�Ƿ񱾻�����
		{
			res = BT_handle_req(&st_data);//�������� �����ͻ�Ӧ
			st_data.wdata[ID_INFO] = 1;
			BT_uart2_send(st_data.wdata,st_data.wlen);
			
		}
		else//���Ǳ���������ֱ������
		{
			return;
		}
	}
	

}


/*********************************************************************************************************
** Function name:     	BT_task
** Descriptions:	    ����������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void BT_task(void)
{
	// 1.��ѵ����1
	BT_uart1_task();
	// 2.��ѵ����2
	BT_uart2_task();
	
}
