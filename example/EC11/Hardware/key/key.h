#ifndef __KEY_H
#define __KEY_H

#include "config.h"
#include "GPIO.h"

/* �����˿ں� ----------------------------------*/

#define KEY_Port			GPIO_P1
#define KEY0_Mode			GPIO_HighZ
#define KEY0_Pin			GPIO_Pin_3
#define KEY0				P13

/* ����״̬ö�� --------------------------------*/

typedef enum{
	KEY_PRES = 0,
	KEY_UP = 1
}Key_State_Enum_t;

typedef enum{
	KEY_NULL = 0,
	KEY0_PRES
}Key_Value_Enum_t;

/* ����ɨ�跽ʽö�� ----------------------------*/

typedef enum{
	KEY_SCAN_SINGLE = 0,
	KEY_SCAN_CONTINUE = 1
}Key_Scan_Mode_Enum_t;

/* ������غ��� --------------------------------*/

void Key_Init(void);

Key_Value_Enum_t Key_Scan(Key_Scan_Mode_Enum_t mode);

#endif /* __KEY_H */









