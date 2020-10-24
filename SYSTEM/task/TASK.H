#ifndef __TASK_H
#define __TASK_H
#include "COMMON.H"


/* 定时器任务管理用 全局变量 */
typedef struct TimerTask_str
{
	u32 Run100msTime; 		// 运行时间，单位（100ms），由定时器任务定时器累加

	u8 Task_10ms_Flag;		//10ms任务提醒标志，由定时器任务定时器置位
	u8 Task_20ms_Flag;		//20ms任务提醒标志，由定时器任务定时器置位
	u8 Task_50ms_Flag;		//50ms任务提醒标志，由定时器任务定时器置位
	u8 Task_100ms_Flag;		//100ms任务提醒标志，由定时器任务定时器置位
	u8 Task_200ms_Flag;		//200ms任务提醒标志，由定时器任务定时器置位
	u8 Task_500ms_Flag;		//500ms任务提醒标志，由定时器任务定时器置位
	u8 Task_1s_Flag;			//1s任务提醒标志，由定时器任务定时器置位
	u8 Task_2s_Flag;			//2s任务提醒标志，由定时器任务定时器置位


} TimerTask_str;


extern TimerTask_str TimerTask;





void Timer_Task_Server(void);
void Timer_Task(void);



#endif

