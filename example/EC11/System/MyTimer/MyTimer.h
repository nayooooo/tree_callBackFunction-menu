#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"
#include "timer.h"

/*---------------- 隐藏使用的定时器 ----------------*/

#define Timer0_Int_Times (1200)  // 定时器0的频率
#define Timer1_Int_Times (1000)  // 定时器1的频率
#define Timer2_Int_Times (1600)  // 定时器2的频率

#define My_Timer Timer2
#define My_Timer_Int_Times Timer2_Int_Times

/*---------------- 隐藏使用的定时器 ----------------*/

void My_Timer_Init(void);

void Key_Long_Pres_Scan_Start(void);
void Key_Long_Pres_Scan_Stop(void);

#endif