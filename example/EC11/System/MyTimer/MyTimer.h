#ifndef __MYTIMER_H
#define __MYTIMER_H

#include "config.h"
#include "timer.h"

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

#define Timer0_Int_Times (1200)  // ��ʱ��0��Ƶ��
#define Timer2_Int_Times (1600)  // ��ʱ��2��Ƶ��

#define My_Timer Timer2
#define My_Timer_Int_Times Timer2_Int_Times

/*---------------- ����ʹ�õĶ�ʱ�� ----------------*/

void My_Timer_Init(void);

#endif