/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           spi.h
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        spi接口驱动    
********************************************************************************************************/

#ifndef _SPI_H_
#define _SPI_H_


#define SPIF		(SPSTAT & 0x80)	//SPI输出完成标志
#define WCOL		0x40	//SPI写冲突标志
#define SSIG		0x80
#define SPEN		0x40
#define DORD		0x20
#define MSTR		0x10
#define CPOL		0x08
#define CPHA		0x04
#define SPDHH		0x00
#define SPDH		0x01
#define SPDL		0x02
#define SPDLL		0x03






unsigned char spi_sendByte(unsigned char byte);
void spi_write_data(unsigned char cmd);
unsigned char spi_write(unsigned char cmd,unsigned char wdata);
unsigned char spi_recvByte(void);
#endif
