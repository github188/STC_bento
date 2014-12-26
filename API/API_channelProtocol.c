/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           API_channelProtocol.c	 
** Created by:          yoc
** Created date:        2014-07-10
** Version:             V1.0 
** Descriptions:        ����������ͨ��Э��ӿ�  ���к�������CP ��ͷ �� channel protocol     
********************************************************************************************************/


#include "..\config.h"

#if (CP_FUNCTION_OPEN == 1)

#define CP_DISPENSE 	0x70
#define CP_CHECK		0x72
#define CP_DATA_ERR		0xEE
#define CP_NO_DATA		0x00

ST_MSG_CP msg_cp;

/*********************************************************************************************************
** Function name:     	CP_init
** Descriptions:	    ��ʼ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      0-�����ݽ���  1-�������� 2-���ݴ���
*********************************************************************************************************/
void CP_init(void)
{
	memset((void *)&msg_cp,0,sizeof(ST_MSG_CP));	
	msg_cp.head = 	0xED;
}



/*********************************************************************************************************
** Function name:     	CP_recv
** Descriptions:	    ��������մ�������
** input parameters:    ��
** output parameters:   ��
** Returned value:      0-�����ݽ���  1-���� 2-check 3-���ݴ���
*********************************************************************************************************/
uchar CP_recv(void)
{
	uchar data i = 0;
	uchar data j = 0;
	uchar data check = 0;
	uchar buf[8] = {0},index = 0,ch,crc;
    static uchar data datLen = 0;

	if(uart1IsEmpty()) return 0;
    
	//�����ݽ���  200ms timeout
	timer.cp_uart = 20;
	while(timer.cp_uart)
	{
		if(!uart1IsEmpty())
		{
			buf[index++] = uart1GetChar();
			if(index >= 8)
				break;
		}
	}
	if(index < 8)	//recv data err
		return 3;

	if(buf[0] != msg_cp.head)
		return 3;

	crc = xorCheck(buf,7);
	if(crc != buf[7])
		return 3;

	if(msg_cp.sn != 0 && msg_cp.sn == buf[2])  //check
		return 2;

	//update st
	msg_cp.len 		= buf[1];
	msg_cp.sn 		= buf[2];
	msg_cp.mt 		= buf[3];
	msg_cp.column 	= buf[4];
	msg_cp.data1 	= buf[5];
	msg_cp.data2 	= buf[6];
	
	if(msg_cp.mt == 0x70)
		return 1;
	else
		return 2;		
}

/*********************************************************************************************************
** Function name:     	CP_send
** Descriptions:	    �����巢�ʹ�������
** input parameters:    ��
** output parameters:   ��
** Returned value:      0-fail  1-ok
*********************************************************************************************************/
uchar CP_send(const ST_MSG_CP *msg)
{
	uchar buf[8] = {0},crc;
	buf[0] = msg_cp.head + 1;
	buf[1] = msg_cp.status;
	buf[2] = msg_cp.sn;
	buf[3] = msg_cp.mt;
	buf[4] = msg_cp.column;
	buf[5] = 0x00;
	buf[6] = 0x00;
	crc = xorCheck(buf,7);
	buf[7] = crc;
	uart1PutStr(buf,8);

	return 1;		
}

/*********************************************************************************************************
** Function name:     	CP_dispense_req
** Descriptions:	    ��������
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void CP_dispense_req(void)
{
	if(msg_cp.column == 0 || msg_cp.column > CP_MAX_COLUMN)
		 msg_cp.status;
//	CP_send(&msg_cp);	
}


/*********************************************************************************************************
** Function name:     	CP_check_req
** Descriptions:	    ��ѯ����
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void CP_check_req(void)
{
	CP_send(&msg_cp);	
}



/*********************************************************************************************************
** Function name:     	CP_poll
** Descriptions:	    ������ѵ
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void CP_poll(void)
{
	 uchar res;

	 CP_init();
	 while(1)
	 {
	 	res = CP_recv();
		switch(res)
		{
			case 1:
				CP_dispense_req();
				break;
			case 2:
				CP_check_req();
				break;
			default:	break;
		}

	 }
}

#endif




