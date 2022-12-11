#include "MyTimer.h"

#include "screen.h"

uint32_t sec = 0;

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
	while(Timer_Inilize(Timer0, &TIM_InitStructure));
}

static void MyTimer2_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// �����ж�
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// ָ��ʱ��Դ
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// �������������
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer2_Int_Times);	// ��ֵ
	TIM_InitStructure.TIM_Run		= ENABLE;				// ��ʼ����
	while(Timer_Inilize(Timer2, &TIM_InitStructure));
}

void My_Timer_Init(void)
{
	OLED_Screen_Freq = 30;
	MyTimer0_Init();
	MyTimer2_Init();
}

/********************* �жϺ������� **************************/

/********************* Timer0�жϺ��� ************************/

void timer0_int (void) interrupt TIMER0_VECTOR
{
	static uint16_t counter = 0;
	
	counter++;
	if(counter >= Timer0_Int_Times / OLED_Screen_Freq) {  // ��Ļˢ��Ƶ��
		counter = 0;
		OLED_Event_Flag |= OLED_Update_Event;
	}
}

/********************* Timer2�жϺ��� ************************/

void timer2_int (void) interrupt TIMER2_VECTOR
{
	static uint16_t counter = 0;
	
	counter++;
	if(counter>=Timer2_Int_Times) {  // 1Hz
		counter = 0;
		sec++;
		OLED_Event_Flag |= OLED_Update_Sec;
	}
}









