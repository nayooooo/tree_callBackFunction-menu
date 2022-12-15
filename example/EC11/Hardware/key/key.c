#include "key.h"

#include "delay.h"
#include "MyTimer.h"

uint16_t Key_Pres_Time = 0;  // ��������ʱ�䣬��λ��ms�����̣�0~65s

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
 * @brief ɨ�谴��״̬
 *
 * @param [mode] ɨ��ģʽ
 * @return [Key_Value_Enum_t] ����ֵ
 */
Key_Value_Enum_t Key_Scan(Key_Scan_Mode_Enum_t mode)
{
	static Key_State_Enum_t key_state = KEY_UP;
	static Key_Value_Enum_t KeyVal_Temp = KEY_NULL;
	Key_Value_Enum_t KeyValue = KEY_NULL;
	
	if(mode == KEY_SCAN_CONTINUE) key_state = KEY_UP;
	if((key_state == KEY_UP) && (KEY0 == KEY_PRES))  // �а�������������ɨ��
	{
		delay_ms(10);
		key_state = KEY_PRES;
		if(KEY0 == KEY_PRES) {  // 10ms����Ȼ�а�������
			Key_Long_Pres_Scan_Start();  // ������ʱ��1����¼��������ʱ�䣬��λ��ms
			if(KEY0 == KEY_PRES) KeyVal_Temp = KEY0_PRES;
		} 
	}
	else if(KEY0 == KEY_UP)  // ���а��������ɿ�
	{
		Key_Long_Pres_Scan_Stop();  // ֹͣ��ʱ
		if(Key_Pres_Time >= KEY_LONG_PRES_SCAN_THRE) {  // �ﵽ������׼
			switch(KeyVal_Temp)  // ����ֵ�ɰ��±�ɳ���
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









