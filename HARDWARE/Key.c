#include "key.h"




void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO模块时钟
	
	//设置该引脚为上拉输入功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
	
	
}


u8 Key_Scan(void)
{
	static u8 State = 0;
	static u8 Key_val = 0;


	switch (State)
	{
		case 0:
			if(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0)
			{
				State = 1;	
			}
			break;

		case 1:
			if(KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0)
			{
				State = 2;	
			}
			else
			{
				State = 0;
			}

			break;

		case 2:
			if(!KEY1)	Key_val = 1;
			if(!KEY2)	Key_val = 2;
			if(!KEY3)	Key_val = 3;
			if(!KEY4)	Key_val = 4;
			if(!KEY5)	Key_val = 5;
			State = 3;
			break;

		case 3:
			if(KEY1&&KEY2&&KEY3&&KEY4&&KEY5)
			{
				State = 0;
				return Key_val;
			}
			break;

		default:
			break;
	}
	return 0;
}



