#include "EC11.h"

#include "delay.h"

uint16_t EC11_A_Vol, EC11_B_Vol;
EC11_Rotate_Dir_Flag EC11_Rotate_Dir = EC11_NO_ROTATE;
// EC11旋转某方向次数缓存数组
// 0 -> 顺时针方向
// 1 -> 逆时针方向
uint8_t EC11_Rotate_Times[2] = { 0, 0 };

static void EC11_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.Mode = EC11_A_Mode;
	GPIO_InitStructure.Pin = EC11_A_Pin;
	GPIO_Inilize(EC11_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.Mode = EC11_B_Mode;
	GPIO_InitStructure.Pin = EC11_B_Pin;
	GPIO_Inilize(EC11_Port, &GPIO_InitStructure);
}

static void EC11_ADC_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_SMPduty = 10;				// ADC采样时间10
	ADC_InitStructure.ADC_CsSetup = 0;				// ADC通道选择时间控制设置为0
	ADC_InitStructure.ADC_CsHold = 1;				// ADC通道选择保持时间控制设置为1
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;	// ADC采样时钟频率
	ADC_InitStructure.ADC_Power = ENABLE;			// 打开ADC电源
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	// ADC结果右对齐
	ADC_InitStructure.ADC_Priority = Priority_0;	// 1优先级
	ADC_InitStructure.ADC_Interrupt = ENABLE;		// 允许中断
	ADC_Inilize(&ADC_InitStructure);
	
	EAXSFR();
	ADCEXCFG |= 0X04;  // ADC转换2次并取平均值
	EAXRAM();
	
	EC11_ADC_PowerControl(ENABLE);
}

void EC11_Init(void)
{
	EC11_GPIO_Config();
	EC11_ADC_Config();
	ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | EC11_A_Channel;
}

void EC11_ADC_PowerControl(uint8_t pwr)
{
	ADC_PowerControl(pwr);
	if(pwr == ENABLE) delay_ms(1);  // 等待MCU内部ADC电源稳定
}

uint16_t EC11_GetADCResult(uint8_t channel)
{
	return Get_ADCResult(channel);
}

/**
 * @fn static EC11_Rotate_Dir_Flag judge_EC11_Rotate_Dir(uint8_t counter)
 * @brief 根据EC11_Rotate_Dir_Counter判断旋转方向
 *
 * @param [EC11_Rotate_Dir_Counter] EC11旋转计数器
 * @return [EC11_Rotate_Dir_Flag] 旋转方向
 */
static EC11_Rotate_Dir_Flag judge_EC11_Rotate_Dir(uint8_t counter)
{
	EC11_Rotate_Dir_Flag dir = EC11_NO_ROTATE;
	
	if((counter & 0X03) + ((counter & 0X04) >> 2) + ((counter & 0X18) >> 3) >= 3)  // 扫描到了至少两个状态的信号
	{
		if(counter & 0X18) {  // 顺时针方向有信号
			if(((counter & 0X18) >> 3) == 1)
				dir |= EC11_CW_ROTATION;
			else  // 逆时针方向
				dir |= EC11_CCW_ROTATION;
		} else {  // 顺时针方向没有信号, 那么另外两个信号一定都有
			if((counter & 0X03) + ((counter & 0X04) >> 2) == 3)  // 顺时针方向
				dir |= EC11_CW_ROTATION;
			else  // 逆时针方向
				dir |= EC11_CCW_ROTATION;
		}
	}
	
	return dir;
}

//========================================================================
// 函数: void ADC_int(void) interrupt ADC_VECTOR
// 描述: ADC中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2012-10-22
//========================================================================
void ADC_int(void) interrupt ADC_VECTOR
{
	static uint8_t i = 1;
	static uint8_t scanFlag = FALSE;  // 允许扫描EC11引脚状态的标志位
	// 记录判断出的旋转方向
	// [4,3] 顺时针方向
	//  [2]  均为低电平
	// [1,0] 逆时针方向
	static uint8_t EC11_Rotate_Dir_Counter = 0X00;
	
	if(ADC_CONTR & ADC_FLAG)
	{
		ADC_CONTR &= ~ADC_FLAG;
		
		// ADC转换
		if(i) {  // ADC转换EC11_A
			i = 0;
			if(ADCCFG &  (1<<5)) {  // 转换结果右对齐
				EC11_A_Vol = ((uint16_t)ADC_RES << 8) | ADC_RESL;
			} else {  // 转换结果左对齐
				#if ADC_RES_12BIT == 1
					EC11_A_Vol = ((uint16_t)ADC_RES << 4) | ((ADC_RESL >> 4) & 0X0F);
				#else
					EC11_A_Vol = ((uint16_t)ADC_RES << 2) | ((ADC_RESL >> 6) & 0X03);
				#endif /* ADC_RES_12BIT == 1 */
			}
			if(EC11_A_Vol < EC11_ACTION_VOL) scanFlag = TRUE;
			ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | EC11_B_Channel;
		} else {  // ADC转换EC11_B
			i = 1;
			if(ADCCFG &  (1<<5)) {  // 转换结果右对齐
				EC11_B_Vol = ((uint16_t)ADC_RES << 8) | ADC_RESL;
			} else {  // 转换结果左对齐
				#if ADC_RES_12BIT == 1
					EC11_B_Vol = ((uint16_t)ADC_RES << 4) | ((ADC_RESL >> 4) & 0X0F);
				#else
					EC11_B_Vol = ((uint16_t)ADC_RES << 2) | ((ADC_RESL >> 6) & 0X03);
				#endif /* ADC_RES_12BIT == 1 */
			}
			if(EC11_B_Vol < EC11_ACTION_VOL) scanFlag = TRUE;
			ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | EC11_A_Channel;
		}
		
		// 旋转状态记录
		if((scanFlag == TRUE)
			&& ((EC11_A_Vol < EC11_ACTION_VOL) || (EC11_B_Vol < EC11_ACTION_VOL)))
		{
			if(EC11_A_Vol < EC11_ACTION_VOL) {
				if(EC11_B_Vol > EC11_ACTION_VOL) {  // 顺时针方向
					if(!(EC11_Rotate_Dir_Counter & 0X18)) {  // 没有记录
						if(EC11_Rotate_Dir_Counter & 0X07)  // 产生过逆时针方向或均为低电平的信号
							EC11_Rotate_Dir_Counter |= (1 << 4);
						else EC11_Rotate_Dir_Counter |= (1 << 3);
					}
				} else {  // 均为低电平
					EC11_Rotate_Dir_Counter |= (1 << 2);
				}
			} else {  // 若不是EC11_A为低电平，那么EC11_B必为低电平
				if(!(EC11_Rotate_Dir_Counter & 0X03)) {  // 没有记录
					if(EC11_Rotate_Dir_Counter & 0X1C)  // 产生过顺时针方向或均为低电平的信号
						EC11_Rotate_Dir_Counter |= (1 << 1);
					else EC11_Rotate_Dir_Counter |= 1;
				}
			}
		}
		
		// 旋转完毕判断
		if((scanFlag == TRUE)
			&& (EC11_A_Vol > EC11_ACTION_VOL) && (EC11_B_Vol > EC11_ACTION_VOL))
		{
			scanFlag = FALSE;
			EC11_Rotate_Dir = judge_EC11_Rotate_Dir(EC11_Rotate_Dir_Counter);
			if(EC11_Rotate_Dir & EC11_CW_ROTATION) EC11_Rotate_Times[0]++;
			if(EC11_Rotate_Dir & EC11_CCW_ROTATION) EC11_Rotate_Times[1]++;
			EC11_Rotate_Dir_Counter = 0X00;
		}
	}
}









