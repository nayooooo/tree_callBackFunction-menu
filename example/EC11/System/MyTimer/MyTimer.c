#include "MyTimer.h"

#include "screen.h"

uint32_t sec = 0;

static void MyTimer0_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Mode		= TIM_16BitAutoReload;	// 16位自动重装
	TIM_InitStructure.TIM_Priority	= Priority_1;			// 中断优先级1
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// 允许中断
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// 指定时钟源
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// 不输出高速脉冲
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer0_Int_Times);	// 初值
	TIM_InitStructure.TIM_Run		= ENABLE;				// 开始运行
	while(Timer_Inilize(Timer0, &TIM_InitStructure));
}

static void MyTimer1_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Mode		= TIM_16BitAutoReload;	// 16位自动重装
	TIM_InitStructure.TIM_Priority	= Priority_1;			// 中断优先级1
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// 允许中断
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// 指定时钟源
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// 不输出高速脉冲
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer1_Int_Times);	// 初值
	TIM_InitStructure.TIM_Run		= ENABLE;				// 开始运行
	while(Timer_Inilize(Timer1, &TIM_InitStructure));
}

static void MyTimer2_Init(void)
{
	TIM_InitTypeDef TIM_InitStructure;
	
	TIM_InitStructure.TIM_Interrupt	= ENABLE;				// 允许中断
	TIM_InitStructure.TIM_ClkSource	= TIM_CLOCK_1T;			// 指定时钟源
	TIM_InitStructure.TIM_ClkOut	= DISABLE;				// 不输出高速脉冲
	TIM_InitStructure.TIM_Value		= 65536UL - (MAIN_Fosc / Timer2_Int_Times);	// 初值
	TIM_InitStructure.TIM_Run		= ENABLE;				// 开始运行
	while(Timer_Inilize(Timer2, &TIM_InitStructure));
}

void My_Timer_Init(void)
{
	OLED_Screen_Freq = 30;
	MyTimer0_Init();
	MyTimer1_Init();
	MyTimer2_Init();
}

/********************* 中断函数部分 **************************/

/********************* Timer0中断函数 ************************/

void timer0_int (void) interrupt TIMER0_VECTOR
{
	static uint16_t counter = 0;
	
	counter++;
	if(counter >= Timer0_Int_Times / OLED_Screen_Freq) {  // 屏幕刷新频率
		counter = 0;
		OLED_Event_Flag |= OLED_Update_Event;
	}
}

/********************* Timer1中断函数************************/

extern uint16_t Key_Pres_Time;

void Key_Long_Pres_Scan_Start(void)
{
	Key_Pres_Time = 0;
	T1_Load((65536UL - (MAIN_Fosc / Timer1_Int_Times)));
	Timer1_Run();
}

void Key_Long_Pres_Scan_Stop(void)
{
	Timer1_Stop();
}

void timer1_int (void) interrupt TIMER1_VECTOR
{
	Key_Pres_Time++;
}

/********************* Timer2中断函数 ************************/

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









