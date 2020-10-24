#ifndef __KEY_H
#define __KEY_H

#include "COMMON.H"

#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)		//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)		//读取按键2
#define KEY3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)	//读取按键3
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)	//读取按键4
#define KEY5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)	//读取按键4


 



void Key_Init(void);
u8 Key_Scan(void);


#endif
