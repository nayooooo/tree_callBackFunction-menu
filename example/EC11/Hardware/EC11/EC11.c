#include "EC11.h"

#include "delay.h"

uint16_t EC11_A_Vol, EC11_B_Vol;
EC11_Rotate_Dir_Flag EC11_Rotate_Dir = EC11_NO_ROTATE;
// EC11��תĳ���������������
// 0 -> ˳ʱ�뷽��
// 1 -> ��ʱ�뷽��
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
	
	ADC_InitStructure.ADC_SMPduty = 10;				// ADC����ʱ��10
	ADC_InitStructure.ADC_CsSetup = 0;				// ADCͨ��ѡ��ʱ���������Ϊ0
	ADC_InitStructure.ADC_CsHold = 1;				// ADCͨ��ѡ�񱣳�ʱ���������Ϊ1
	ADC_InitStructure.ADC_Speed = ADC_SPEED_2X1T;	// ADC����ʱ��Ƶ��
	ADC_InitStructure.ADC_Power = ENABLE;			// ��ADC��Դ
	ADC_InitStructure.ADC_AdjResult = ADC_RIGHT_JUSTIFIED;	// ADC����Ҷ���
	ADC_InitStructure.ADC_Priority = Priority_0;	// 1���ȼ�
	ADC_InitStructure.ADC_Interrupt = ENABLE;		// �����ж�
	ADC_Inilize(&ADC_InitStructure);
	
	EAXSFR();
	ADCEXCFG |= 0X04;  // ADCת��2�β�ȡƽ��ֵ
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
	if(pwr == ENABLE) delay_ms(1);  // �ȴ�MCU�ڲ�ADC��Դ�ȶ�
}

uint16_t EC11_GetADCResult(uint8_t channel)
{
	return Get_ADCResult(channel);
}

/**
 * @fn static EC11_Rotate_Dir_Flag judge_EC11_Rotate_Dir(uint8_t counter)
 * @brief ����EC11_Rotate_Dir_Counter�ж���ת����
 *
 * @param [EC11_Rotate_Dir_Counter] EC11��ת������
 * @return [EC11_Rotate_Dir_Flag] ��ת����
 */
static EC11_Rotate_Dir_Flag judge_EC11_Rotate_Dir(uint8_t counter)
{
	EC11_Rotate_Dir_Flag dir = EC11_NO_ROTATE;
	
	if((counter & 0X03) + ((counter & 0X04) >> 2) + ((counter & 0X18) >> 3) >= 3)  // ɨ�赽����������״̬���ź�
	{
		if(counter & 0X18) {  // ˳ʱ�뷽�����ź�
			if(((counter & 0X18) >> 3) == 1)
				dir |= EC11_CW_ROTATION;
			else  // ��ʱ�뷽��
				dir |= EC11_CCW_ROTATION;
		} else {  // ˳ʱ�뷽��û���ź�, ��ô���������ź�һ������
			if((counter & 0X03) + ((counter & 0X04) >> 2) == 3)  // ˳ʱ�뷽��
				dir |= EC11_CW_ROTATION;
			else  // ��ʱ�뷽��
				dir |= EC11_CCW_ROTATION;
		}
	}
	
	return dir;
}

//========================================================================
// ����: void ADC_int(void) interrupt ADC_VECTOR
// ����: ADC�жϺ���.
// ����: none.
// ����: none.
// �汾: V1.0, 2012-10-22
//========================================================================
void ADC_int(void) interrupt ADC_VECTOR
{
	static uint8_t i = 1;
	static uint8_t scanFlag = FALSE;  // ����ɨ��EC11����״̬�ı�־λ
	// ��¼�жϳ�����ת����
	// [4,3] ˳ʱ�뷽��
	//  [2]  ��Ϊ�͵�ƽ
	// [1,0] ��ʱ�뷽��
	static uint8_t EC11_Rotate_Dir_Counter = 0X00;
	
	if(ADC_CONTR & ADC_FLAG)
	{
		ADC_CONTR &= ~ADC_FLAG;
		
		// ADCת��
		if(i) {  // ADCת��EC11_A
			i = 0;
			if(ADCCFG &  (1<<5)) {  // ת������Ҷ���
				EC11_A_Vol = ((uint16_t)ADC_RES << 8) | ADC_RESL;
			} else {  // ת����������
				#if ADC_RES_12BIT == 1
					EC11_A_Vol = ((uint16_t)ADC_RES << 4) | ((ADC_RESL >> 4) & 0X0F);
				#else
					EC11_A_Vol = ((uint16_t)ADC_RES << 2) | ((ADC_RESL >> 6) & 0X03);
				#endif /* ADC_RES_12BIT == 1 */
			}
			if(EC11_A_Vol < EC11_ACTION_VOL) scanFlag = TRUE;
			ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | EC11_B_Channel;
		} else {  // ADCת��EC11_B
			i = 1;
			if(ADCCFG &  (1<<5)) {  // ת������Ҷ���
				EC11_B_Vol = ((uint16_t)ADC_RES << 8) | ADC_RESL;
			} else {  // ת����������
				#if ADC_RES_12BIT == 1
					EC11_B_Vol = ((uint16_t)ADC_RES << 4) | ((ADC_RESL >> 4) & 0X0F);
				#else
					EC11_B_Vol = ((uint16_t)ADC_RES << 2) | ((ADC_RESL >> 6) & 0X03);
				#endif /* ADC_RES_12BIT == 1 */
			}
			if(EC11_B_Vol < EC11_ACTION_VOL) scanFlag = TRUE;
			ADC_CONTR = (ADC_CONTR & 0xf0) | ADC_START | EC11_A_Channel;
		}
		
		// ��ת״̬��¼
		if((scanFlag == TRUE)
			&& ((EC11_A_Vol < EC11_ACTION_VOL) || (EC11_B_Vol < EC11_ACTION_VOL)))
		{
			if(EC11_A_Vol < EC11_ACTION_VOL) {
				if(EC11_B_Vol > EC11_ACTION_VOL) {  // ˳ʱ�뷽��
					if(!(EC11_Rotate_Dir_Counter & 0X18)) {  // û�м�¼
						if(EC11_Rotate_Dir_Counter & 0X07)  // ��������ʱ�뷽����Ϊ�͵�ƽ���ź�
							EC11_Rotate_Dir_Counter |= (1 << 4);
						else EC11_Rotate_Dir_Counter |= (1 << 3);
					}
				} else {  // ��Ϊ�͵�ƽ
					EC11_Rotate_Dir_Counter |= (1 << 2);
				}
			} else {  // ������EC11_AΪ�͵�ƽ����ôEC11_B��Ϊ�͵�ƽ
				if(!(EC11_Rotate_Dir_Counter & 0X03)) {  // û�м�¼
					if(EC11_Rotate_Dir_Counter & 0X1C)  // ������˳ʱ�뷽����Ϊ�͵�ƽ���ź�
						EC11_Rotate_Dir_Counter |= (1 << 1);
					else EC11_Rotate_Dir_Counter |= 1;
				}
			}
		}
		
		// ��ת����ж�
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









