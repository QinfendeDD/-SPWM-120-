/***********************************************************************************
* ��ʱ�� ��������
*
*
* TIME1 �ж� �����߳Ƕ�����У�飩
* TIME1 PWM  �����߳Ƕ�����У�飩

* TIME2 �ж� ��У��
* TIME2 PWM  ��У��
*
* TIME3 �ж� ��У��
* TIME3 PWM  ��У��
*
* TIME4 �ж� ��У��
* TIME4 PWM  
*
* TIME5 �ж� ��У��
* TIME5 PWM  
*
* TIME6 �ж� ��У��
*
* TIME7 �ж� ��У��
*
* ˵����
* ���� TIM6 �� TIM7�������Ķ�ʱ���������������� PWM �����
* ���и߼���ʱ�� TIM1 �� TIM8 ����ͬʱ������� 7 ·�� PWM �����
* ͨ�ö�ʱ��Ҳ��ͬʱ���� 4 ·�� PWM �����
*
* ���ߣ���ϣ����δ��ɣ�
* ���ڣ�2015��8��6��
************************************************************************************/
#include "timer.h"
#include "TASK.H"



/*************************************************  ��ʱ��1  *******************************************************/
//�߼���ʱ��1�жϳ�ʼ��
//ʱ��72MHz
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3

//void TIM1_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
//	
//	//��ʱ��TIM1��ʼ��
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //��Ϊ��ʼֵ����0  ������������ʼ��
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM1�ж�,��������ж�

//	//�ж����ȼ�NVIC����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx					 
//}

////��ʱ��1�жϷ������
//void TIM1_UP_IRQHandler(void)   //TIM1�ж�
//{
//  	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//	{
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx�����жϱ�־ 

//	}
//}
////TIM1 PWM���ֳ�ʼ�� 
////PWM�����ʼ��
////arr���Զ���װֵ
////psc��ʱ��Ԥ��Ƶ��
//void TIM1_PWM_Init(u16 arr,u16 psc)
//{  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��

//	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.5
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO

//	//��ʼ��TIM3
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //��Ϊ��ʼֵ����0  ������������ʼ��
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

//	//	//��ʼ��TIM1 Channel2 PWMģʽ	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//ѡ�񻥲�����Ƚ�״̬
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//�����������
//	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_Low;//���û����������
//	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;//����״̬�µ÷ǹ���ģʽ
//	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//��������״̬�µ÷ǹ���ģʽ

//	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_CtrlPWMOutputs(TIM1,ENABLE);
//	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM3
//}

/*************************************************  ��ʱ��2  *******************************************************/
//ͨ�ö�ʱ��2�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM2_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM2�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx����
}
//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		// ����Ϊ�û�����

	}
}

//TIM2 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM2_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//ʹ�ܶ�ʱ��2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.0
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_0; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//�����������
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.1
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_1; 		//TIM_CH2
	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO	
// 	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.2
// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_2; 		//TIM_CH3
// 	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO	
// 	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.3
// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_3; 		//TIM_CH4
// 	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO	

	/* ��ӳ��Ϊ B10 + B11 */
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE); //Timer2������ӳ��  
 
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.10
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_10; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.11
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_11; 		//TIM_CH2
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO	
 
   //��ʼ��TIM2
	TIM_TimeBaseCfg.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseCfg); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM2 Ch 1 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; 	//�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM2, &TIM_OCInitCfg);  					//����Tָ���Ĳ�����ʼ������TIM2 OC1
	//��ʼ��TIM2 Ch 2 PWMģʽ 
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC2Init(TIM2, &TIM_OCInitCfg);  					//����Tָ���Ĳ�����ʼ������TIM2 OC2
	//��ʼ��TIM2 Ch 3 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC3Init(TIM2, &TIM_OCInitCfg);  					//����Tָ���Ĳ�����ʼ������TIM2 OC3
	//��ʼ��TIM2 Ch 4 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC4Init(TIM2, &TIM_OCInitCfg);  					//����Tָ���Ĳ�����ʼ������TIM2 OC4
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//ʹ��TIM2��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//ʹ��TIM2��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//ʹ��TIM2��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
}


/*************************************************  ��ʱ��3  *******************************************************/

//ͨ�ö�ʱ��3�жϳ�ʼ��
//APB1ʱ��Ϊ36M����ʱ��ѡ��ΪAPB1��2����72Mhz
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  						//ʹ��TIMx����
							 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		// ����Ϊ�û�����
		Timer_Task_Server(); 
	}
}


//TIM3 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.6
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//�����������
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOA.7
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
	GPIO_Init(GPIOA, &GPIO_Cfg);			//��ʼ��GPIO

	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.0
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_0; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.1
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_1; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
 
    //��ʼ��TIM3
	TIM_TimeBaseCfg.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseCfg); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Ch 1 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM3 OC1
	//��ʼ��TIM3 Ch 2 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC2Init(TIM3, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM3 OC2
	//��ʼ��TIM3 Ch 3 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC3Init(TIM3, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM3 OC3
	//��ʼ��TIM3 Ch 4 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC4Init(TIM3, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM3 OC4

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR4�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
}


/*************************************************  ��ʱ��4  *******************************************************/
//ͨ�ö�ʱ��4�жϳ�ʼ��
//APB1ʱ��Ϊ36M����ʱ��ѡ��ΪAPB1��2����72Mhz
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM4_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM3�ж�,��������ж�

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  						//ʹ��TIMx����
							 
}
//��ʱ��4�жϷ������
 void TIM4_IRQHandler(void)   //TIM4�ж�
 {
 	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
 	{
 		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
 		
 		// ����Ϊ�û�����


 	}
 }

//TIM4 PWM���ֳ�ʼ��
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
 
    //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.6
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//�����������
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.7
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO

	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.8
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_8; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
	//���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��	GPIOB.9
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_9; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
 
    //��ʼ��TIM4
	TIM_TimeBaseCfg.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseCfg); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM4 Ch 1 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM4, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM4 OC1
	//��ʼ��TIM4 Ch 2 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC2Init(TIM4, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM4 OC2
	//��ʼ��TIM4 Ch 3 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC3Init(TIM4, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM4 OC3
	//��ʼ��TIM4 Ch 4 PWMģʽ
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OC4Init(TIM4, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM4 OC4

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR4�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
}



///*************************************************  ��ʱ��5  *******************************************************/
////ͨ�ö�ʱ��5�жϳ�ʼ��
////APB1ʱ��Ϊ36M����ʱ��ѡ��ΪAPB1��2����72Mhz
////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��
////����ʹ�õ��Ƕ�ʱ��3!
//void TIM5_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM5�ж�,��������ж�

//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM5, ENABLE);  						//ʹ��TIMx����
//							 
//}
////��ʱ��5�жϷ������
//void TIM5_IRQHandler(void)   //TIM5�ж�
//{
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		// ����Ϊ�û�����
//		
//	}
//}

////TIM5 PWM���ֳ�ʼ��
////PWM�����ʼ��
////arr���Զ���װֵ
////psc��ʱ��Ԥ��Ƶ��
//void TIM5_PWM_Init(u16 arr, u16 psc)
//{  
//// 	GPIO_InitTypeDef 			GPIO_Cfg;
//	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
//	TIM_OCInitTypeDef  			TIM_OCInitCfg;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ�ܶ�ʱ��5ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
// 
////     //���ø�����Ϊ�����������,���TIM5 CH2��PWM���岨��	GPIOB.6
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
//// 	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//�����������
//// 	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
//// 	//���ø�����Ϊ�����������,���TIM5 CH2��PWM���岨��	GPIOB.7
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO

//// 	//���ø�����Ϊ�����������,���TIM5 CH2��PWM���岨��	GPIOB.8
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_8; 		//TIM_CH1
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
//// 	//���ø�����Ϊ�����������,���TIM5 CH2��PWM���岨��	GPIOB.9
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_9; 		//TIM_CH1
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//��ʼ��GPIO
// 
//    //��ʼ��TIM4
//	TIM_TimeBaseCfg.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
//	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
//	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseCfg); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
//	
//	//��ʼ��TIM4 Ch 1 PWMģʽ
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
// 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
//	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
//	TIM_OC1Init(TIM5, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM5 OC1
//	//��ʼ��TIM4 Ch 2 PWMģʽ
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OC2Init(TIM5, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM5 OC2
//	//��ʼ��TIM4 Ch 3 PWMģʽ
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OC3Init(TIM5, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM5 OC3
//	//��ʼ��TIM5 Ch 4 PWMģʽ
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
//	TIM_OC4Init(TIM5, &TIM_OCInitCfg);  				//����Tָ���Ĳ�����ʼ������TIM5 OC4

//	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR1�ϵ�Ԥװ�ؼĴ���
//	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR2�ϵ�Ԥװ�ؼĴ���
//	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR3�ϵ�Ԥװ�ؼĴ���
//	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR4�ϵ�Ԥװ�ؼĴ���
// 
//	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
//}


///*************************************************  ��ʱ��6  *******************************************************/
////ͨ�ö�ʱ��6�жϳ�ʼ��
////APB1ʱ��Ϊ36M����ʱ��ѡ��ΪAPB1��2����72Mhz
////arr���Զ���װֵ��
////psc��ʱ��Ԥ��Ƶ��
////����ʹ�õ��Ƕ�ʱ��6!
//void TIM6_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM6�ж�,��������ж�

//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM6, ENABLE);  						//ʹ��TIMx����
//							 
//}
////��ʱ��6�жϷ������
//void TIM6_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		// ����Ϊ�û�����
//		
//	}
//}


///*************************************************  ��ʱ��7  *******************************************************/
////��ʱ��7��ʼ������
//void TIM7_Int_Init(u16 arr,u16 psc)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //ʱ��ʹ��

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 		//ʹ��ָ����TIM�ж�,��������ж�

//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  				//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

//	TIM_Cmd(TIM7, ENABLE);  						//ʹ��TIMx����
//}
////��ʱ��7�жϷ������
//void TIM7_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//	{
//		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		
//		// ����Ϊ�û�����
//		
//	}
//}

