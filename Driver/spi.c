/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           spi.c
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        spi���߽ӿ�����   
********************************************************************************************************/
#include "..\config.h"








void spi_init(void)
{
#if 0
	SPCTL = 0xFD;
	SPSTAT = 0xC0;
	SPDAT = 0;
	IE2  = 0x03;//���� SPI�ж�
	SS = 1;
	EA	 =	1;
#else
	SPCTL	= 0xFC;
	SPDAT = 0;			// clear spi data
	SPSTAT = SPIF | WCOL; //clear spi status
	SPCTL	= SPEN | MSTR; //master mode
	SS	= 1;
	IE2  = 0x03;//���� SPI�ж�
	EA	 =	1;
	MOSI = 0;  
	MISO = 1;    
	SCLK = 0;
#endif
}


/*********************************************************************************************************
** Function name:     	spi_sendByte
** Descriptions:	    ����һ���ֽ����� 
** input parameters:    
** output parameters:   
** Returned value:     
*********************************************************************************************************/
unsigned char spi_sendByte(unsigned char byte)
{
	
	SPDAT = byte;
	trace("spi_sendByte1:%x",byte);
	SS = 1;
	while(!SPIF);
	
	SPSTAT = 0xC0;
	SS = 0;
	trace("spi_sendByte[over]:%x",byte);
	return (SPDAT);
#if 0
	SPDAT = byte;
	trace("spi_sendByte");
	while(!(SPIF & SPSTAT));
	SPSTAT = SPIF | WCOL;
	trace("spi_sendByte1");

	return (SPDAT);
#endif
}


unsigned char spi_recvByte(void)
{
	while(!SPIF);
	SPSTAT = SPIF | WCOL;
	return (SPDAT);
}



void spi_write_data(unsigned char cmd)
{	
	spi_sendByte(cmd);	
}


unsigned char spi_write(unsigned char cmd,unsigned char wdata)
{
	unsigned char rdata = 0;
	spi_sendByte(cmd);
	rdata = spi_sendByte(wdata);
	return rdata;
}


void spi_readwrite(unsigned char cmd,unsigned int addr,
	unsigned char len,unsigned char *prdata,unsigned char *pwdata)
{
	spi_sendByte(cmd);
	spi_sendByte(HUINT16(addr));
	spi_sendByte(LUINT16(addr));
	while(len--)
	{
		*prdata++ = spi_sendByte(*pwdata++);		
	}
}





