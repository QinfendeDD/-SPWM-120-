#ifndef __LED_H
#define __LED_H

#include "COMMON.H"
#define Set_LED()   PCout(13)=0; 
#define Reset_LED() PCout(13)=1;

void LED_Init(void);

#endif
