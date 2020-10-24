#include "LED.h"


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //开启AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// 改变指定管脚的映射 
	//以上两句使能PB3，PB4的IO功能
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOC时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //PC13
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOC.13
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);			//PC.13置位
}
