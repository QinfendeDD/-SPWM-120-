#include "LED.h"


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //����AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);// �ı�ָ���ܽŵ�ӳ�� 
	//��������ʹ��PB3��PB4��IO����
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //PC13
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.13
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13);			//PC.13��λ
}
