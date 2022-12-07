#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"

/*---------------- 隐藏使用的定时器 ----------------*/

#define TIMER_PER_SECOND		(1000)					// 1ms
#define Timer0_Int_Times		TIMER_PER_SECOND		// TIM0溢出频率

#define My_Timer				Timer0
#define My_Timer_Int_Times		Timer0_Int_Times

/*---------------- 隐藏使用的定时器 ----------------*/

extern uint32_t timer_sec;

void MyTimer_Init(void);

#endif