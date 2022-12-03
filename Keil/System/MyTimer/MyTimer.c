#include "MyTimer.h"

#include "timer.h"

uint32_t timer_sec = 0;

static void MyTimer0_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Mode		= TIM_16BitAutoReload;	// 16λ�Զ���װ
	TIM_InitStructure.TIM_Priority	= Priority_1;			// �ж����ȼ�1
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// �����ж�
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// ָ��ʱ��Դ
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// �������������
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer0_Int_Times);	// ��ֵ
	TIM_InitStructure.TIM_Run		= ENABLE;				// ��ʼ����
	while(Timer_Inilize(My_Timer, &TIM_InitStructure));
}

void MyTimer_Init(void)
{
	MyTimer0_Init();
}

/********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt TIMER0_VECTOR
{
	static u16 i = 0;
	
	i++;
	if(i>=Timer0_Int_Times)  // ÿ1�����һ��Ƶ��
	{
		i = 0;
		timer_sec++;
	}
}








