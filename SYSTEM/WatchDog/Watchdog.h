/**********************************************************************************
* 
**********************************************************************************/ 	
#ifndef __Watchdog_H
#define __Watchdog_H
#include "COMMON.H"



void Watchdog_Init(u8 prer,u16 rlr);	//看门狗初始化
void FeedWatchdog(void); 					//看门狗 喂狗



#endif

