/*--------------------------------------------------------------------------
STC12C5A16S2.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __STC12C5A16S2_H__
#define __STC12C5A16S2_H__

/*  BYTE Register  */
sfr P0   = 0x80;
sfr P1   = 0x90;
sfr P2   = 0xA0;
sfr P3   = 0xB0;
sfr P4	 = 0xC0;	//Added by chen
sfr PSW  = 0xD0;
sfr ACC  = 0xE0;
sfr B    = 0xF0;
sfr SP   = 0x81;
sfr DPL  = 0x82;
sfr DPH  = 0x83;
sfr PCON = 0x87;
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0  = 0x8A;
sfr TL1  = 0x8B;
sfr TH0  = 0x8C;
sfr TH1  = 0x8D;
sfr IE   = 0xA8;
sfr IP   = 0xB8;
sfr SCON = 0x98;
sfr SBUF = 0x99;


/*  BIT Register  */
/*  PSW   */
sbit CY   = 0xD7;
sbit AC   = 0xD6;
sbit F0   = 0xD5;
sbit RS1  = 0xD4;
sbit RS0  = 0xD3;
sbit OV   = 0xD2;
sbit P    = 0xD0;

/*  TCON  */
sbit TF1  = 0x8F;
sbit TR1  = 0x8E;
sbit TF0  = 0x8D;
sbit TR0  = 0x8C;
sbit IE1  = 0x8B;
sbit IT1  = 0x8A;
sbit IE0  = 0x89;
sbit IT0  = 0x88;

/*  IE   */
sbit EA   = 0xAF;
sbit ES   = 0xAC;
sbit ET1  = 0xAB;
sbit EX1  = 0xAA;
sbit ET0  = 0xA9;
sbit EX0  = 0xA8;

/*  IP   */ 
sbit PS   = 0xBC;
sbit PT1  = 0xBB;
sbit PX1  = 0xBA;
sbit PT0  = 0xB9;
sbit PX0  = 0xB8;

/*  P3  */
sbit RD   = 0xB7;
sbit WR   = 0xB6;
sbit T1   = 0xB5;
sbit T0   = 0xB4;
sbit INT1 = 0xB3;
sbit INT0 = 0xB2;
sbit TXD  = 0xB1;
sbit RXD  = 0xB0;

/*  SCON  */
sbit SM0  = 0x9F;
sbit SM1  = 0x9E;
sbit SM2  = 0x9D;
sbit REN  = 0x9C;
sbit TB8  = 0x9B;
sbit RB8  = 0x9A;
sbit TI   = 0x99;
sbit RI   = 0x98;

/*  S2CON */
sfr S2CON = 0x9A;
sfr S2BUF = 0x9B;
sfr BRT   = 0x9C;
sfr IE2   = 0xAF;

/*  AUXR */
sfr AUXR  = 0x8E;
sfr AUXR1 = 0xA2;

/********************************PWM¼Ä´æÆ÷Added by chensunwei****************************/
sfr		CCON		=   0xD8;                  //PCA control register
sbit	CCF0		=   CCON^0;                //PCA module-0 interrupt flag
sbit	CCF1		=   CCON^1;                //PCA module- interrupt flag
sbit    CR      	=   CCON^6;                //PCA timer run control bit
sbit    CF      	=   CCON^7;                //PCA timer overflow flag
sfr		CMOD		=   0xD9;                  //PCA mode register
sfr		CL			=   0xE9;                  //PCA base timer LOW
sfr		CH			=   0xF9;                  //PCA base timer HIGH
sfr		CCAPM0		=   0xDA;                  //PCA module-0 mode register
sfr		CCAP0L		=   0xEA;                  //PCA module-0 capture register LOW
sfr		CCAP0H      =   0xFA;                  //PCA module-0 capture register HIGH
sfr		CCAPM1     	=   0xDB;                  //PCA module- mode register
sfr		CCAP1L     	=   0xEB;                  //PCA module- capture register LOW
sfr		CCAP1H     	=   0xFB;                  //PCA module- capture register HIGH
sfr		CCAPM2     	=   0xDC;                  //PCA module-2 mode register
sfr		CCAP2L     	=   0xEC;                  //PCA module-2 capture register LOW
sfr		CCAP2H     	=   0xFC;                  //PCA module-2 capture register HIGH
sfr		CCAPM3      =   0xDD;                  //PCA module-3 mode register
sfr		CCAP3L      =   0xED;                  //PCA module-3 capture register LOW
sfr		CCAP3H     	=   0xFD;                  //PCA module-3 capture register HIGH
sfr		PCAPWM0     =   0xF2;
sfr		PCAPWM1    	=   0xF3;
sfr		PCAPWM2    	=   0xF4;
sfr		PCAPWM3    	=   0xF5;

/********************************IOÅäÖÃ¼Ä´æÆ÷Added by chensunwei**************************/
sfr		P0M0		=  	0x94;
sfr		P0M1		=	0x93;

sfr		P1M0		=	0x92;
sfr		P1M1		= 	0x91;

sfr		P2M0		=	0x96;
sfr		P2M1		= 	0x95;

sfr		P3M0		=	0xB2;
sfr		P3M1		= 	0xB1;

sfr		ADC_CONTR	=0xBC;			//ADC Control Register
sfr		ADC_RES	 	=0xBD;			//ADC Hight 8-bit Result Register
sfr		ADC_LOW2 	=0xBE;			//ADC Low 2-bit Rezult Register
sfr		P1ASF	 	=0x9D;			//P1 Secondary Function Control Register



/********************************SPIÅäÖÃ¼Ä´æÆ÷Added by yoc**************************/
sfr		SPSTAT		=	0x8E;	//SPI status register
sfr		SPCTL		=	0xCE;	//SPI control	register		
sfr		SPDAT		=	0xCF;	//SPI data register
sbit  SPISS		= 	P1^3;	//SPI slave select,connnect


sbit	SCLK		=	P1^7;
sbit	MISO		=	P1^6;
sbit	MOSI		=	P1^5;
sbit	SS			=	P1^4;
		
#endif
