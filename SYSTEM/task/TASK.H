#ifndef __TASK_H
#define __TASK_H
#include "COMMON.H"


/* ��ʱ����������� ȫ�ֱ��� */
typedef struct TimerTask_str
{
	u32 Run100msTime; 		// ����ʱ�䣬��λ��100ms�����ɶ�ʱ������ʱ���ۼ�

	u8 Task_10ms_Flag;		//10ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_20ms_Flag;		//20ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_50ms_Flag;		//50ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_100ms_Flag;		//100ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_200ms_Flag;		//200ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_500ms_Flag;		//500ms�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_1s_Flag;			//1s�������ѱ�־���ɶ�ʱ������ʱ����λ
	u8 Task_2s_Flag;			//2s�������ѱ�־���ɶ�ʱ������ʱ����λ


} TimerTask_str;


extern TimerTask_str TimerTask;





void Timer_Task_Server(void);
void Timer_Task(void);



#endif
