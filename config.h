#ifndef _CONFIG_H_
#define _CONFIG_H_

//#include <reg52.h>
#include "stc12c5a16s2.h"
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

//API
//#include "API_channelProtocol.h"
#include "API_Bento.h"

//Driver
#include "uart1.h"
#include "uart2.h"
#include "timer.h"
#include "board.h"
#include "RS485.h"
//#include "spi.h"
//#include "fm25040b.h"



#endif