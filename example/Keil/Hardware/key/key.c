/**
 * @file key.h
 * @encoding GB2312
 * @brief ����ģ��
 * @author yewan
 *
 */

#include "key.h"

#include "delay.h"

void key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Pin = KEY0_Pin;
	GPIO_InitStructure.Mode = KEY0_Pin_Mode;
	while(GPIO_Inilize(KEY0_Port, &GPIO_InitStructure));
	
	KEY0_IN();
}

KeyValue_t keyScan(KeyScan_Mode_t mode)
{
	static uint8_t key_up = 1;  // 1->�����ɿ���0->��������
	
	if(mode) key_up = 1;  // ����ɨ��
	if(key_up && KEY0 == 0) {
		key_up = 0;
		delay_ms(10);
		if(KEY0 == 0) return KEY0_PRES;
	} else if (KEY0 == 1) key_up = 1;
	return NO_PRES;
}









