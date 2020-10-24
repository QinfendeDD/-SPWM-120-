#include "spwm.h"
//不懂高级定时器的简易先看看野火的教学视频
                                               //载波频率=采样点数*基波频率=计数器时钟频率/载波周期值
#define TIMEPERIOD  9000000.0/(150*FREQUENCY) //载波周期值 如果乘以计数器时钟即为一个载波周期，9000000经系统时钟8分频得到，
                                             //150是正弦波采样点数。注意在调频时TIMEPERIOD最大不能超出65535

double Voltage = 1.0;  //调压系数
u32 sinpwm;

//设置三相初始值，使输出互差120°
__IO  u16 PhraseA=0; 
__IO  u16 PhraseB=50; 
__IO  u16 PhraseC=100;


///*******************************************************
// *	  正弦数据表 使用SPWM表格生成工具生成 参数设置如下：
// *	  SPWM中值：16384 （偏置值 使得到的数据都为正）
// *		SPWM幅值：16383 （得到的数据值范围为1-32767）
// *	  周内点数：150   （一个基波周期内的采样点数 可改变载波频率 载波频率=采样点*基波频率 假设采样点为150 基波频率为50 那么载波频率为7.5K）
// *		调制度：1        (调制度=载波幅值/基波幅值 这里载波幅值与基波幅值都等于32767)
// *	  每行数据：15
// *		勾选四舍五入+16进制
// *		
// *		数据是如何计算生成的呢？
// *    比如第二个数据 "0x42AE" 对应十进制为 17070
// *		17070 =	sin(360/150*n)*16383+16384 其中n=1 表示第一个采样点		
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
// *	  定时器1产生3相6路互补的PWM波 带死区 相位差120°
// *	  channel1  ->A.8
// *		channel1N ->B.13(互补)
// *	  channel2  ->A.9
// *		channel2N ->B.14(互补)
// *	  channel3  ->A.10
// *		channel3N ->B.15(互补)
// *		TIMEPERIOD	  --> 自动重装载周期值
// *		ChannelxPulse --> 占空周期值
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
	TIM_TimeBaseStructure.TIM_Period = TIMEPERIOD-1;             //设置重装载周期值，也就是一个载波周期     // ARR
  TIM_TimeBaseStructure.TIM_Prescaler =7;	                     //设置预分频：Fcnt=72M/（psc+1）这里psc设置为7 相当于8分频     //计数器时钟9M
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;               //重复计数器。。不用=0
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	               //设置时钟分频系数：不分频(与死区时间有关)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);                         //清除溢出中断标志
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);                     //计数溢出时触发中断

	TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;	              //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable;	     //比较输出使能
  TIM_OCInitStructure.TIM_OutputNState  =TIM_OutputNState_Enable;     //使能互补输出
	TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;        //输出高电平有效
	TIM_OCInitStructure.TIM_OCNPolarity   =TIM_OCNPolarity_High;      //互补输出高电平有效	
  TIM_OCInitStructure.TIM_OCIdleState   =TIM_OCIdleState_Reset;    //空闲状态 刹车后输出低
  TIM_OCInitStructure.TIM_OCNIdleState  =TIM_OCNIdleState_Reset;  //空闲状态 刹车后互补输出低


	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseA];	    ///设置跳变值，当计数器计数到这个值时，电平发生跳变 
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);	         ///使能通道1
	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseB];	  ///设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);	       ///使能通道2
	TIM_OCInitStructure.TIM_Pulse = spwm[PhraseC];  ///设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);       ///使能通道3


	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //使能通道1预装载寄存器
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); //使能通道2预装载寄存器
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); //使能通道3预装载寄存器
			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; //TIM1_UP_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//高级定时器才有--死区，刹车
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Disable;            //运行模式输出选择 
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Disable;           //空闲模式输出选择
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;              //锁定设置
  TIM_BDTRInitStructure.TIM_DeadTime = 27;                            //死区时间设置 3μs
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;                  //刹车功能失能
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;      //刹车输入极性
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable; //自动输出使能 

  TIM_BDTRConfig(TIM1,&TIM_BDTRInitStructure);       	
  TIM_ARRPreloadConfig(TIM1, ENABLE);	    //使能TIM1重载寄存器ARR	

	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);     	//pwm输出使能	

}


///*******************************************************
// *	  TIM1中断服务函数
// *	  中断时间与 TIMEPERIOD 有关
// *	  设置CCR寄存器中的 TIM_Pulse 可动态改变载波占空比 占空比=TIM_Pulse/TIMEPERIOD
// *	  TIM_Pulse=正弦变化因子*TIMEPERIOD 占空比即可随正弦因子变化而变化
// *    其中 正弦变化因子=正弦表采样点值/基波幅值32767 （因子值范围0~1）
// ******************************************************/

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)==SET)
	{
		
#if 0 //不使用调压功能
			TIM1->CCR1 = TIMEPERIOD*spwm[PhraseA]/32767;
			TIM1->CCR2 = TIMEPERIOD*spwm[PhraseB]/32767;
			TIM1->CCR3 = TIMEPERIOD*spwm[PhraseC]/32767;

//		printf("%d  %d  %d\r\n",spwm[PhraseA],spwm[PhraseB],spwm[PhraseC]);		
		
//		TIM_SetCompare1(TIM1,TIMEPERIOD*sin_table[PhraseA]);	
//		TIM_SetCompare2(TIM1,TIMEPERIOD*sin_table[PhraseB]);	
//		TIM_SetCompare3(TIM1,TIMEPERIOD*sin_table[PhraseC]);
		
#else	 //开启调压功能 正负半周要分开乘	(VVVF改变占空比实现调压 驱动三相电机时使用)
		 if(FREQUENCY<=50)Voltage=0.1+0.9*FREQUENCY/50;//基频设置为50HZ 基频以下为恒转矩调速(变频变压 压频比保持不变) 基频以上为恒功率调速(变频不变压) 
		
	   if(spwm[PhraseA]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseA]-16384);
            TIM1->CCR1 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseA]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseA]);
            TIM1->CCR1 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//修改TIM1通道1的PWM占空比，后者为捕获/比较寄存器1的值
        }
	   if(spwm[PhraseB]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseB]-16384);
            TIM1->CCR2 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseB]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseB]);
            TIM1->CCR2 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//修改TIM1通道2的PWM占空比，后者为捕获/比较寄存器1的值
        }
	   if(spwm[PhraseC]>16384)
        {
            sinpwm = Voltage * (spwm[PhraseC]-16384);
            TIM1->CCR3 = TIMEPERIOD * (sinpwm + 16384)/32767 ;
        }
        else if(spwm[PhraseC]<=16384)
        {
            sinpwm = Voltage * (16384 - spwm[PhraseC]);
            TIM1->CCR3 = TIMEPERIOD * (16384 - sinpwm)/32767 ;	//修改TIM1通道3的PWM占空比，后者为捕获/比较寄存器1的值
        }
//Voltage=1;		
#endif	
			PhraseA=(PhraseA+1)%(150);
			PhraseB=(PhraseB+1)%(150);
			PhraseC=(PhraseC+1)%(150);		
		}
    TIM_ClearITPendingBit(TIM1,TIM_FLAG_Update);
}


