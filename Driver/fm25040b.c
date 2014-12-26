/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           FM25040b.c
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        Ìúµç´æ´¢Æ÷Çý¶¯
********************************************************************************************************/
#include "..\config.h"


void FM_init()
{
	SPCTL = 0;
	MOSI = 0;
	MISO = 0;
	SCLK = 0;
}


void FM_delay()
{
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
void FM_spiWr(unsigned char dat)
{
	unsigned char i;
	SCLK = 0;
	FM_delay();
	for(i = 0;i < 8;i++)
	{
		SCLK = 0;
		FM_delay();
		if(dat & 0x80){MOSI = 1;}
		else {MOSI = 0;}
		dat <<= 1;
		SCLK = 0;
		FM_delay();
		SCLK = 1;
		FM_delay();
	}
}

unsigned char FM_spiRd( void ) 
{
	unsigned char i,dat;
	for(i = 0;i < 8;i++)
	{
		SCLK = 0;
		dat = dat << 1;
		dat |= MISO;
		SCLK = 1;		
	}
	SCLK = 1;
	return (dat);
	
}

unsigned char FM_readStatus(void)
{
	unsigned char u;
	SS = 0;
	FM_spiWr(FM_RDSR);
	u = FM_spiRd();
	SS = 1;

	return u;
}




void FM_writeEnable(void)
{
	SS = 0;
	FM_spiWr(FM_WREN);
	SS = 1;
}

void FM_writeStatus(unsigned char dat)
{
	FM_writeEnable();
	SS = 0;
	FM_spiWr(FM_WRSR);
	FM_spiWr(dat);
	SS = 1;
	FM_readStatus();
	
}


unsigned char FM_readByte(unsigned int addr)
{
	unsigned char dat;
	SS = 0;
	//FM_spiWr(FM_RDSR);
	FM_spiWr(FM_READ);
	FM_spiWr(HUINT16(addr));
	FM_spiWr(LUINT16(addr));

	dat = FM_spiRd();

	SS = 1;
	return (dat);
}



void FM_writeByte(unsigned int addr,unsigned char dat)
{
	FM_writeEnable();
	SS = 0;
	//FM_spiWr(FM_WRSR);
	FM_spiWr(FM_WRITE);
	FM_spiWr(HUINT16(addr));
	FM_spiWr(LUINT16(addr));
	FM_spiWr(dat);
	SS = 1;
	//FM_readStatus();
	
	
}



