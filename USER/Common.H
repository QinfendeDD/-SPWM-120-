#ifndef __COMMON_H
#define __COMMON_H

#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "TASK.h"
#include "Watchdog.h"
#include "clkconfig.h"


//定义系统时钟以便合理配置SysTick定时器延时
#define   SYSCLOCKFREQ    72


//全局变量声明
extern int FREQUENCY;







#endif    /*  __COMMON_H  */
