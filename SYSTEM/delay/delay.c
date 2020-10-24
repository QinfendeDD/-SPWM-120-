#include "delay.h"



/*
++++++++++++++++++++++++++	
+	us����ʱ
+	����SysTick��ʱ��ʵ��
++++++++++++++++++++++++++
*/
void Delay_us( __IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SYSCLOCKFREQ);
	
	for(i=0;i<us;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1	
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

/*
++++++++++++++++++++++++++	
+	ms����ʱ
+	����SysTick��ʱ��ʵ��
++++++++++++++++++++++++++
*/
void Delay_ms( __IO uint32_t ms)
{
	uint32_t i;	
	SysTick_Config(SYSCLOCKFREQ*1000);
	
	for(i=0;i<ms;i++)
	{
		// ����������ֵ��С��0��ʱ��CRTL�Ĵ�����λ16����1
		// ����1ʱ����ȡ��λ����0
		while( !((SysTick->CTRL)&(1<<16)) );
	}
	// �ر�SysTick��ʱ��
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}


/*
++++++++++++++++++++++++++	
	SysTick_Handler�ض���
	���û�����ʹ������
++++++++++++++++++++++++++
*/
void SysTick_Handler(void)
{
		
}






