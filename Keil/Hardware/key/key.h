/**
 * @file key.h
 * @encoding GB2312
 * @brief ����ģ��
 * @author yewan
 *
 */

#ifndef __KEY_H
#define __KEY_H

#include "config.h"

#include "GPIO.h"

/* key GPIO�˿ڶ��� --------------------------------*/
#define KEY0_Port				GPIO_P3
#define KEY0_Pin				GPIO_Pin_2
#define KEY0_Pin_Mode			GPIO_PullUp  // ����׼˫���
#define KEY0					P32

#define KEY0_IN()				KEY0 = 1

/* key scan ģʽö�� -------------------------------*/
typedef enum{
	KeyScan_Mode_Single,
	KeyScan_Mode_Cont
}KeyScan_Mode_t;

/* key value ö�� ----------------------------------*/
typedef enum{
	NO_PRES,
	KEY0_PRES
}KeyValue_t;

/* key ��غ��� ------------------------------------*/
void key_Init(void);

KeyValue_t keyScan(KeyScan_Mode_t mode);

#endif /* __KEY_H */









