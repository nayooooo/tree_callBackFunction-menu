#include "key.h"

#include "delay.h"
#include "MyTimer.h"

uint16_t Key_Pres_Time = 0;  // 按键按下时间，单位：ms，量程：0~65s

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

/**
 * @fn Key_Value_Enum_t Key_Scan(Key_Scan_Mode_Enum_t mode)
 * @brief 扫描按键状态
 *
 * @param [mode] 扫描模式
 * @return [Key_Value_Enum_t] 按键值
 */
Key_Value_Enum_t Key_Scan(Key_Scan_Mode_Enum_t mode)
{
	static Key_State_Enum_t key_state = KEY_UP;
	static Key_Value_Enum_t KeyVal_Temp = KEY_NULL;
	Key_Value_Enum_t KeyValue = KEY_NULL;
	
	if(mode == KEY_SCAN_CONTINUE) key_state = KEY_UP;
	if((key_state == KEY_UP) && (KEY0 == KEY_PRES))  // 有按键按下且允许扫描
	{
		delay_ms(10);
		key_state = KEY_PRES;
		if(KEY0 == KEY_PRES) {  // 10ms后仍然有按键按下
			Key_Long_Pres_Scan_Start();  // 开启定时器1，记录按键按下时间，单位：ms
			if(KEY0 == KEY_PRES) KeyVal_Temp = KEY0_PRES;
		} 
	}
	else if(KEY0 == KEY_UP)  // 所有按键均已松开
	{
		Key_Long_Pres_Scan_Stop();  // 停止计时
		if(Key_Pres_Time >= KEY_LONG_PRES_SCAN_THRE) {  // 达到长按标准
			switch(KeyVal_Temp)  // 按键值由按下变成长按
			{
				case KEY0_PRES:
					KeyVal_Temp = KEY0_LONG_PRES;
					break;
			}
		}
		key_state = KEY_UP;
		KeyValue = KeyVal_Temp;
		KeyVal_Temp = KEY_NULL;
	}
 	return KeyValue;
}









