#include "spwm.h"
//�����߼���ʱ���ļ����ȿ���Ұ��Ľ�ѧ��Ƶ
                                               //�ز�Ƶ��=��������*����Ƶ��=������ʱ��Ƶ��/�ز�����ֵ
#define TIMEPERIOD  9000000.0/(150*FREQUENCY) //�ز�����ֵ ������Լ�����ʱ�Ӽ�Ϊһ���ز����ڣ�9000000��ϵͳʱ��8��Ƶ�õ���
                                             //150�����Ҳ�����������ע���ڵ�ƵʱTIMEPERIOD����ܳ���65535

double Voltage = 1.0;  //��ѹϵ��
u32 sinpwm;

//���������ʼֵ��ʹ�������120��
__IO  u16 PhraseA=0; 
__IO  u16 PhraseB=50; 
__IO  u16 PhraseC=100;


///*******************************************************
// *	  �������ݱ� ʹ��SPWM������ɹ������� �����������£�
// *	  SPWM��ֵ��16384 ��ƫ��ֵ ʹ�õ������ݶ�Ϊ����
// *		SPWM��ֵ��16383 ���õ�������ֵ��ΧΪ1-32767��
// *	  ���ڵ�����150   ��һ�����������ڵĲ������� �ɸı��ز�Ƶ�� �ز�Ƶ��=������*����Ƶ�� ���������Ϊ150 ����Ƶ��Ϊ50 ��ô�ز�Ƶ��Ϊ7.5K��
// *		���ƶȣ�1        (���ƶ�=�ز���ֵ/������ֵ �����ز���ֵ�������ֵ������32767)
// *	  ÿ�����ݣ�15
// *		��ѡ��������+16����
// *		
// *		��������μ������ɵ��أ�
// *    ����ڶ������� "0x42AE" ��Ӧʮ����Ϊ 17070
// *		17070 =	sin(360/150*n)*16383+16384 ����n=1 ��ʾ��һ��������		
// ******************************************************/
const u32 spwm[150]={
0x4000,0x42AE,0x455B,0x4805,0x4AAC,0x4D4E,0x4FEA,0x527F,0x550C,0x578F,0x5A08,0x5C74,0x5ED5,0x6127,0x636A,
0x659E,0x67C0,0x69D1,0x6BCF,0x6DB9,0x6F8F,0x714F,0x72FA,0x748D,0x7609,0x776C,0x78B7,0x79E8,0x7AFF,0x7BFB,
0x7CDD,0x7DA3,0x7E4E,0x7EDD,0x7F4F,0x7FA5,0x7FDF,0x7FFB,0x7FFB,0x7FDF,0x7FA5,0x7F4F,0x7EDD,0x7E4E,0x7DA3,
0x7CDD,0x7BFB,0x7AFF,0x79E8,0x78B7,0x776C,0x7609,0x748D,0x72FA,0x714F,0x6F8F,0x6DB9,0x6BCF,0x69D1,0x67C0,
0x659E,0x636A,0x6127,0x5ED5,0x5C74,0x5A08,0x578F,0x550C,0x527F,0x4FEA,0x4D4E,0x4AAC,0x4805,0x455B,0x42AE,
0x4000,0x3D52,0x3AA5,0x37FB,0x3554,0x32B2,0x3016,0x2D81,0x2AF4,0x2871,0x25F8,0x238C,0x212B,0x1ED9,0x1C96,
0x1A62,0x1840,0x162F,0x1431,0x1247,0x1071,0x0EB1,0x0D06,0x0B73,0x09F7,0x0894,0x0749,0x0618,0x0501,0x0405,
0x0323,0x025D,0x01B2,0x0123,0x00B1,0x005B,0x0021,0x0005,0x0005,0x0021,0x005B,0x00B1,0x0123,0x01B2,0x025D,
0x0323,0x0405,0x0501,0x0618,0x0749,0x0894,0x09F7,0x0B73,0x0D06,0x0EB1,0x1071,0x1247,0x1431,0x162F,0x1840,
0x1A62,0x1C96,0x1ED9,0x212B,0x238C,0x25F8,0x2871,0x2AF4,0x2D81,0x3016,0x32B2,0x3554,0x37FB,0x3AA5,0x3D52
}; 										



///*******************************************************
// *	  ��ʱ��1����3��6·������PWM�� ������ ��λ��120��
// *	  channel1  ->A.8
// *		channel1N ->B.13(����)
// *	  channel2  ->A.9
// *		channel2N ->B.14(����)
// *	  channel3  ->A.10
// *		channel3N ->B.15(����)
// *		TIMEPERIOD	  --> �Զ���װ������ֵ
// *		ChannelxPulse --> ռ������ֵ
// ******************************************************/

void SPWM_Init()
{
	
	NVIC_InitTypeDef NVIC_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1, ENABLE);	//*****************
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period = TIMEPERIOD-1;             //������װ������ֵ��Ҳ����һ���ز�����     // ARR
  TIM_TimeBaseStructure.TIM_Prescaler =7;	                     //����Ԥ��Ƶ��Fcnt=72M/��psc+1������psc����Ϊ7 �൱��8��Ƶ     //������ʱ��9M
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;               //�ظ���������������=0
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	               //����ʱ�ӷ�Ƶϵ��������Ƶ(������ʱ���й�)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);                         //�������жϱ�־
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);                     //�������ʱ�����ж�

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;	              //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;	     //�Ƚ����ʹ��
  TIM_OCInitStructure.TIM_OutputNState  =TIM_OutputNState_Enable;     //ʹ�ܻ������
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;        //����ߵ�ƽ��Ч
	TIM_OCInitStructure.TIM_OCNPolarity   =TIM_OCNPolarity_High;      //��������ߵ�ƽ��Ч	
  TIM_OCInitStructure.TIM_OCIdleState   =TIM_OCIdleState_Reset;    //����״̬ ɲ���������
  TIM_OCInitStructure.TIM_OCNIdleState  =TIM_OCNIdleState_Reset;  //����״̬ ɲ���󻥲������


	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseA];	    ///��������ֵ�������������������ֵʱ����ƽ�������� 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);	         ///ʹ��ͨ��1
	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseB];	  ///��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);	       ///ʹ��ͨ��2
	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseC];  ///��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);       ///ʹ��ͨ��3


	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //ʹ��ͨ��1Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); //ʹ��ͨ��2Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); //ʹ��ͨ��3Ԥװ�ؼĴ���
			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; //TIM1_UP_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//�߼���ʱ������--������ɲ��
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;            //����ģʽ���ѡ�� 
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;           //����ģʽ���ѡ��
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;              //��������
  TIM_BDTRInitStructure.TIM_DeadTime = 27;                            //����ʱ������ 3��s
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;                  //ɲ������ʧ��
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;      //ɲ�����뼫��
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable; //�Զ����ʹ�� 

  TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);       	
  TIM_ARRPreloadConfig(TIM1, ENABLE);	    //ʹ��TIM1���ؼĴ���ARR	

	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);     	//pwm���ʹ��	

}


///*******************************************************
// *	  TIM1�жϷ�����
// *	  �ж�ʱ���� TIMEPERIOD �й�
// *	  ����CCR�Ĵ����е� TIM_Pulse �ɶ�̬�ı��ز�ռ�ձ� ռ�ձ�=TIM_Pulse/TIMEPERIOD
// *	  TIM_Pulse=���ұ仯����*TIMEPERIOD ռ�ձȼ������������ӱ仯���仯
// *    ���� ���ұ仯����=���ұ������ֵ/������ֵ32767 ������ֵ��Χ0~1��
// ******************************************************/

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		
#if 0 //��ʹ�õ�ѹ����
			TIM1->CCR1 = TIMEPERIOD*spwm[PhraseA]/32767;
			TIM1->CCR2 = TIMEPERIOD*spwm[PhraseB]/32767;
			TIM1->CCR3 = TIMEPERIOD*spwm[PhraseC]/32767;

//		printf("%d  %d  %d\r\n",spwm[PhraseA],spwm[PhraseB],spwm[PhraseC]);		
		
//		TIM_SetCompare1(TIM1,TIMEPERIOD*sin_table[PhraseA]);	
//		TIM_SetCompare2(TIM1,TIMEPERIOD*sin_table[PhraseB]);	
//		TIM_SetCompare3(TIM1,TIMEPERIOD*sin_table[PhraseC]);
		
#else	 //������ѹ���� ��������Ҫ�ֿ���	(VVVF�ı�ռ�ձ�ʵ�ֵ�ѹ ����������ʱʹ��)
		 if(FREQUENCY<=50)Voltage=0.1+0.9*FREQUENCY/50;//��Ƶ����Ϊ50HZ ��Ƶ����Ϊ��ת�ص���(��Ƶ��ѹ ѹƵ�ȱ��ֲ���) ��Ƶ����Ϊ�㹦�ʵ���(��Ƶ����ѹ) 
		
	   if(spwm[PhraseA]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseA]-16384);
            TIM1->CCR1 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseA]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseA]);
            TIM1->CCR1 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//�޸�TIM1ͨ��1��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
        }
	   if(spwm[PhraseB]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseB]-16384);
            TIM1->CCR2 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseB]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseB]);
            TIM1->CCR2 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//�޸�TIM1ͨ��2��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
        }
	   if(spwm[PhraseC]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseC]-16384);
            TIM1->CCR3 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseC]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseC]);
            TIM1->CCR3 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//�޸�TIM1ͨ��3��PWMռ�ձȣ�����Ϊ����/�ȽϼĴ���1��ֵ
        }
//Voltage=1;		
#endif	
			PhraseA=(PhraseA+1)%(150);
			PhraseB=(PhraseB+1)%(150);
			PhraseC=(PhraseC+1)%(150);		
		}
    TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);
}


