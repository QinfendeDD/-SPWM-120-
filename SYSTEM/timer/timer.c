/***********************************************************************************
* 定时器 驱动代码
*
*
* TIME1 中断 （作者城东，已校验）
* TIME1 PWM  （作者城东，已校验）

* TIME2 中断 已校验
* TIME2 PWM  已校验
*
* TIME3 中断 已校验
* TIME3 PWM  已校验
*
* TIME4 中断 已校验
* TIME4 PWM  
*
* TIME5 中断 已校验
* TIME5 PWM  
*
* TIME6 中断 已校验
*
* TIME7 中断 已校验
*
* 说明：
* 除了 TIM6 和 TIM7，其他的定时器都可以用来产生 PWM 输出。
* 其中高级定时器 TIM1 和 TIM8 可以同时产生多达 7 路的 PWM 输出。
* 通用定时器也能同时产生 4 路的 PWM 输出。
*
* 作者：星希望（未完成）
* 日期：2015年8月6日
************************************************************************************/
#include "timer.h"
#include "TASK.H"



/*************************************************  定时器1  *******************************************************/
//高级定时器1中断初始化
//时钟72MHz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3

//void TIM1_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
//	
//	//定时器TIM1初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //因为初始值不是0  所以这里必须初始化
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //使能指定的TIM1中断,允许更新中断

//	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

//	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM1, ENABLE);  //使能TIMx					 
//}

////定时器1中断服务程序
//void TIM1_UP_IRQHandler(void)   //TIM1中断
//{
//  	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
//	{
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx更新中断标志 

//	}
//}
////TIM1 PWM部分初始化 
////PWM输出初始化
////arr：自动重装值
////psc：时钟预分频数
//void TIM1_PWM_Init(u16 arr,u16 psc)
//{  
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能定时器3时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟

//	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

//	//初始化TIM3
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //因为初始值不是0  所以这里必须初始化
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

//	//	//初始化TIM1 Channel2 PWM模式	 
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_OutputNState=TIM_OutputNState_Disable;//选择互补输出比较状态
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//设置输出极性
//	TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCNPolarity_Low;//设置互补输出极性
//	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;//空闲状态下得非工作模式
//	TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCNIdleState_Reset;//互补空闲状态下得非工作模式

//	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
//	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
//	TIM_CtrlPWMOutputs(TIM1,ENABLE);
//	TIM_Cmd(TIM1, ENABLE);  //使能TIM3
//}

/*************************************************  定时器2  *******************************************************/
//通用定时器2中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM2_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); 		//使能指定的TIM2中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
}
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		// 以下为用户代码

	}
}

//TIM2 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM2_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.0
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_0; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//复用推挽输出
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.1
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_1; 		//TIM_CH2
	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO	
// 	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.2
// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_2; 		//TIM_CH3
// 	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO	
// 	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.3
// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_3; 		//TIM_CH4
// 	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO	

	/* 重映射为 B10 + B11 */
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE); //Timer2部分重映射  
 
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.10
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_10; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.11
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_11; 		//TIM_CH2
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO	
 
   //初始化TIM2
	TIM_TimeBaseCfg.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseCfg); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM2 Ch 1 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; 	//输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitCfg);  					//根据T指定的参数初始化外设TIM2 OC1
	//初始化TIM2 Ch 2 PWM模式 
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC2Init(TIM2, &TIM_OCInitCfg);  					//根据T指定的参数初始化外设TIM2 OC2
	//初始化TIM2 Ch 3 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC3Init(TIM2, &TIM_OCInitCfg);  					//根据T指定的参数初始化外设TIM2 OC3
	//初始化TIM2 Ch 4 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 			//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC4Init(TIM2, &TIM_OCInitCfg);  					//根据T指定的参数初始化外设TIM2 OC4
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//使能TIM2在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//使能TIM2在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//使能TIM2在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  		//使能TIM2在CCR4上的预装载寄存器
	
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
}


/*************************************************  定时器3  *******************************************************/

//通用定时器3中断初始化
//APB1时钟为36M这里时钟选择为APB1的2倍，72Mhz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); 		//使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  						//使能TIMx外设
							 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		// 以下为用户代码
		Timer_Task_Server(); 
	}
}


//TIM3 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 
    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.6
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//复用推挽输出
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOA.7
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
	GPIO_Init(GPIOA, &GPIO_Cfg);			//初始化GPIO

	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.0
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_0; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.1
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_1; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
 
    //初始化TIM3
	TIM_TimeBaseCfg.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseCfg); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Ch 1 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM3 OC1
	//初始化TIM3 Ch 2 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC2Init(TIM3, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM3 OC2
	//初始化TIM3 Ch 3 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC3Init(TIM3, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM3 OC3
	//初始化TIM3 Ch 4 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC4Init(TIM3, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM3 OC4

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR4上的预装载寄存器
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
}


/*************************************************  定时器4  *******************************************************/
//通用定时器4中断初始化
//APB1时钟为36M这里时钟选择为APB1的2倍，72Mhz
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM4_Int_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 		//使能指定的TIM3中断,允许更新中断

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  						//使能TIMx外设
							 
}
//定时器4中断服务程序
 void TIM4_IRQHandler(void)   //TIM4中断
 {
 	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
 	{
 		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
 		
 		// 以下为用户代码


 	}
 }

//TIM4 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM4_PWM_Init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef 			GPIO_Cfg;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
	TIM_OCInitTypeDef  			TIM_OCInitCfg;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
 
    //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.6
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//复用推挽输出
	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.7
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO

	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.8
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_8; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
	//设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.9
	GPIO_Cfg.GPIO_Pin = GPIO_Pin_9; 		//TIM_CH1
	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
 
    //初始化TIM4
	TIM_TimeBaseCfg.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseCfg); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM4 Ch 1 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM4, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM4 OC1
	//初始化TIM4 Ch 2 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC2Init(TIM4, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM4 OC2
	//初始化TIM4 Ch 3 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC3Init(TIM4, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM4 OC3
	//初始化TIM4 Ch 4 PWM模式
	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OC4Init(TIM4, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM4 OC4

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR3上的预装载寄存器
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR4上的预装载寄存器
 
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
}



///*************************************************  定时器5  *******************************************************/
////通用定时器5中断初始化
////APB1时钟为36M这里时钟选择为APB1的2倍，72Mhz
////arr：自动重装值。
////psc：时钟预分频数
////这里使用的是定时器3!
//void TIM5_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE ); 		//使能指定的TIM5中断,允许更新中断

//	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	TIM_Cmd(TIM5, ENABLE);  						//使能TIMx外设
//							 
//}
////定时器5中断服务程序
//void TIM5_IRQHandler(void)   //TIM5中断
//{
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		// 以下为用户代码
//		
//	}
//}

////TIM5 PWM部分初始化
////PWM输出初始化
////arr：自动重装值
////psc：时钟预分频数
//void TIM5_PWM_Init(u16 arr, u16 psc)
//{  
//// 	GPIO_InitTypeDef 			GPIO_Cfg;
//	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseCfg;
//	TIM_OCInitTypeDef  			TIM_OCInitCfg;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能定时器5时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
// 
////     //设置该引脚为复用输出功能,输出TIM5 CH2的PWM脉冲波形	GPIOB.6
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_6; 		//TIM_CH1
//// 	GPIO_Cfg.GPIO_Mode = GPIO_Mode_AF_PP;  	//复用推挽输出
//// 	GPIO_Cfg.GPIO_Speed = GPIO_Speed_50MHz;
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
//// 	//设置该引脚为复用输出功能,输出TIM5 CH2的PWM脉冲波形	GPIOB.7
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_7; 		//TIM_CH2
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO

//// 	//设置该引脚为复用输出功能,输出TIM5 CH2的PWM脉冲波形	GPIOB.8
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_8; 		//TIM_CH1
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
//// 	//设置该引脚为复用输出功能,输出TIM5 CH2的PWM脉冲波形	GPIOB.9
//// 	GPIO_Cfg.GPIO_Pin = GPIO_Pin_9; 		//TIM_CH1
//// 	GPIO_Init(GPIOB, &GPIO_Cfg);			//初始化GPIO
// 
//    //初始化TIM4
//	TIM_TimeBaseCfg.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
//	TIM_TimeBaseCfg.TIM_Prescaler =psc; 	//设置用来作为TIMx时钟频率除数的预分频值 
//	TIM_TimeBaseCfg.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseCfg.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseCfg); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
//	
//	//初始化TIM4 Ch 1 PWM模式
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
// 	TIM_OCInitCfg.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OCInitCfg.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
//	TIM_OC1Init(TIM5, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM5 OC1
//	//初始化TIM4 Ch 2 PWM模式
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OC2Init(TIM5, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM5 OC2
//	//初始化TIM4 Ch 3 PWM模式
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OC3Init(TIM5, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM5 OC3
//	//初始化TIM5 Ch 4 PWM模式
//	TIM_OCInitCfg.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式2
//	TIM_OC4Init(TIM5, &TIM_OCInitCfg);  				//根据T指定的参数初始化外设TIM5 OC4

//	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR1上的预装载寄存器
//	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR2上的预装载寄存器
//	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR3上的预装载寄存器
//	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);  //使能TIM5在CCR4上的预装载寄存器
// 
//	TIM_Cmd(TIM5, ENABLE);  //使能TIM5
//}


///*************************************************  定时器6  *******************************************************/
////通用定时器6中断初始化
////APB1时钟为36M这里时钟选择为APB1的2倍，72Mhz
////arr：自动重装值。
////psc：时钟预分频数
////这里使用的是定时器6!
//void TIM6_Int_Init(u16 arr, u16 psc)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE ); 		//使能指定的TIM6中断,允许更新中断

//	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	TIM_Cmd(TIM6, ENABLE);  						//使能TIMx外设
//							 
//}
////定时器6中断服务程序
//void TIM6_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		// 以下为用户代码
//		
//	}
//}


///*************************************************  定时器7  *******************************************************/
////定时器7初始化函数
//void TIM7_Int_Init(u16 arr,u16 psc)
//{
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

//	TIM_TimeBaseStructure.TIM_Period = arr; 		//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; 		//设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 	//设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE ); 		//使能指定的TIM中断,允许更新中断

//	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  				//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	TIM_Cmd(TIM7, ENABLE);  						//使能TIMx外设
//}
////定时器7中断服务程序
//void TIM7_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//	{
//		TIM_ClearITPendingBit(TIM7, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		
//		// 以下为用户代码
//		
//	}
//}

