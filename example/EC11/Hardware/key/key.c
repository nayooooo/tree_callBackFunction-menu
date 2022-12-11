#include "key.h"

#include "delay.h"

static void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = KEY0_Mode;
	GPIO_InitStructure.Pin = KEY0_Pin;
	GPIO_Inilize(KEY_Port, &GPIO_InitStructure);
	KEY0 = KEY_UP;
}

void Key_Init(void)
{
	Key_GPIO_Config();
}

Key_Value_Enum_t Key_Scan(Key_Scan_Mode_Enum_t mode)
{
	static Key_State_Enum_t key_state = KEY_UP;
	Key_Value_Enum_t KeyValue = KEY_NULL;
	
	if(mode == KEY_SCAN_CONTINUE) key_state = KEY_UP;
	if((key_state == KEY_UP) && (KEY0 == KEY_PRES))
	{
		delay_ms(10);
		key_state = KEY_PRES;
		if(KEY0 == KEY_PRES) KeyValue = KEY0_PRES;
	} else if(KEY0 == KEY_UP) key_state = KEY_UP;
 	return KeyValue;
}









