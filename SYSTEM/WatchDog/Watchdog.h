/**********************************************************************************
* 
**********************************************************************************/ 	
#ifndef __Watchdog_H
#define __Watchdog_H
#include "COMMON.H"



void Watchdog_Init(u8 prer,u16 rlr);	//���Ź���ʼ��
void FeedWatchdog(void); 					//���Ź� ι��



#endif

