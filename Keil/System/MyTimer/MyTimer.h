#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

#define TIMER_PER_SECOND		(1000)					// 1ms
#define Timer0_Int_Times		TIMER_PER_SECOND		// TIM0���Ƶ��

#define My_Timer				Timer0
#define My_Timer_Int_Times		Timer0_Int_Times

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

extern uint32_t timer_sec;

void MyTimer_Init(void);

#endif