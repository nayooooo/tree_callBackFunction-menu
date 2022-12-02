/**
 * @file key.h
 * @encoding GB2312
 * @brief 按键模块
 * @author yewan
 *
 */

#ifndef __KEY_H
#define __KEY_H

#include "config.h"

#include "GPIO.h"

/* key GPIO端口定义 --------------------------------*/
#define KEY0_Port				GPIO_P3
#define KEY0_Pin				GPIO_Pin_2
#define KEY0_Pin_Mode			GPIO_PullUp  // 上拉准双向口
#define KEY0					P32

#define KEY0_IN()				KEY0 = 1

/* key scan 模式枚举 -------------------------------*/
typedef enum{
	KeyScan_Mode_Single,
	KeyScan_Mode_Cont
}KeyScan_Mode_t;

/* key value 枚举 ----------------------------------*/
typedef enum{
	NO_PRES,
	KEY0_PRES
}KeyValue_t;

/* key 相关函数 ------------------------------------*/
void key_Init(void);

KeyValue_t keyScan(KeyScan_Mode_t mode);

#endif /* __KEY_H */









