#ifndef __EC11_H
#define __EC11_H

#include "config.h"
#include "ADC.h"
#include "GPIO.h"

/* 端口宏 ------------------------------------*/

#define EC11_Port			GPIO_P1
#define EC11_A_Mode			GPIO_HighZ
#define EC11_B_Mode			GPIO_HighZ
#define EC11_A_Pin			GPIO_Pin_0
#define EC11_B_Pin			GPIO_Pin_1
#define EC11_A				P10
#define EC11_B				P11
#define EC11_A_Channel		ADC_CH0
#define EC11_B_Channel		ADC_CH1

/* EC11状态 ----------------------------------*/
typedef enum{
	EC11_NO_ROTATE = 0X00,			// 无旋转
	EC11_CW_ROTATION = 0X01,		// 顺时针
	EC11_CCW_ROTATION = 0X02,		// 逆时针
}EC11_Rotate_Dir_Flag;

#define EC11_ACTION_VOL		(2000)		/* EC11变化时的引脚电平阈值 */

/* 向外声明变量 ------------------------------*/
extern uint16_t EC11_A_Vol, EC11_B_Vol;
extern EC11_Rotate_Dir_Flag EC11_Rotate_Dir;
extern uint8_t EC11_Rotate_Times[2];

/* 配置函数 ----------------------------------*/
void EC11_Init(void);
void EC11_ADC_PowerControl(uint8_t pwr);
uint16_t EC11_GetADCResult(uint8_t channel);

#endif /* __EC11_H */









