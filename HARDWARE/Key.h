#ifndef __KEY_H
#define __KEY_H

#include "COMMON.H"

#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)		//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)		//��ȡ����2
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)	//��ȡ����3
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)	//��ȡ����4
#define KEY5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)	//��ȡ����4


 



void Key_Init(void);
u8 Key_Scan(void);


#endif
