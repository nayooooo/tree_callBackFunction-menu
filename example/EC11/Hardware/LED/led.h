#ifndef __LED_H
#define __LED_H

#include "config.h"
#include "GPIO.h"

/*------------- LED GPIO �˿ڶ��� -------------*/

#define LED_GPIO_Port GPIO_P0
#define LED_Pin(N)	GPIO_Pin_##N
#define LED_0_Pin	LED_Pin(0)
#define LED_1_Pin	LED_Pin(1)
#define LED_0	P00
#define LED_1	P01
#define LED(N)	LED_##N

/*------------- LED GPIO �˿ڶ��� -------------*/

/*------------- LED ״̬���� -------------*/

typedef enum{
	LED_ON		= 0,
	LED_OFF		= 1,
}LED_State_Typedef;

/*------------- LED ״̬���� -------------*/

void LED_Init(void);

#endif