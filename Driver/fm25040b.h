/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           FM25040b.h
** Created by:          yoc
** Created date:        2014-12-10
** Version:             V1.0 
** Descriptions:        Ìúµç´æ´¢Æ÷Çý¶¯
********************************************************************************************************/

#ifndef _FM25040B_H_
#define _FM25040B_H_


#define FM_WREN		0x06	// write enable
#define FM_WRDI		0x04	//write disable
#define FM_RDSR		0x05	//read status register
#define FM_WRSR		0x01	//write status register
#define FM_READ		0x03	//read memory data
#define FM_WRITE	0x02	// write memory data

unsigned char FM_readByte(unsigned int addr);
void FM_writeByte(unsigned int addr,unsigned char dat);
void FM_writeStatus(unsigned char dat);
#endif
