/**
 * @file screen.c
 * @brief ��Ļ��ʾ�ļ�������SSD1306
 * @author yewan
 * @encoding GB2312
 */

#include "screen.h"

#include <stdlib.h>
#include <math.h>

#include "delay.h"

uint8_t OLED_Event_Flag = OLED_No_Event;
uint8_t OLED_Screen_Freq = 30;  // ��Ļˢ��Ƶ��
Screen_ResRatio_t Screen_ResRatio;  // ��������������ָ�����ʽ���з���

void OLED_Show_Hello(void)
{
	OLED_ShowString(0, 0, (uint8_t*)"Hello C51!", 8, FILL);
}

void OLED_Show_Freq(void)
{
	OLED_ShowString(0, 0, (u8*)"screen freq: ", 8, FILL);
	OLED_ShowNum(OLED_COL_MAX - SCREEN_FREQ_DIGITAL * SCREEN_FREQ_SIZE, 0,
					OLED_Screen_Freq, SCREEN_FREQ_DIGITAL, SCREEN_FREQ_SIZE,
					FILL);
}

void OLED_Set_Freq(uint8_t newFreq)
{
	if((newFreq >= SCREEN_FREQ_MIN)
		&& (newFreq <= SCREEN_FREQ_MAX))
	{ OLED_Screen_Freq = newFreq; }
}

void OLED_Add_Freq(void)
{
	OLED_Clear();
	OLED_Set_Freq(OLED_Screen_Freq + 1);
	OLED_Show_Freq();
}

void OLED_Sub_Freq(void)
{
	OLED_Clear();
	OLED_Set_Freq(OLED_Screen_Freq - 1);
	OLED_Show_Freq(); 
}

/**
 * @fn Screen_ResRatio_t* Screen_ResRatio_Init(
 *		uint16_t total_Col, uint16_t total_Row,
 *		uint16_t pixel_Width, uint16_t pixel_Hight,
 *		uint16_t pixels_Total_Col, uint16_t pixels_Total_Row
 *		)
 * @brief ��ʼ����Ļ��������
 *
 * @param [total_Col] ��Ļ�ܵ�����
 * @param [total_Row] ��Ļ�ܵ�����
 * @param [pixel_Width] �������صĿ��
 * @param [pixel_Hight] �������صĸ߶�
 * @param [pixels_Total_Col] �ܹ����е����ص�����
 * @param [pixels_Total_Row] �ܹ����е����ص�����
 * @return [Screen_ResRatio_t*] ��Ļ�ֱ��ʲ�����ָ��
 */
Screen_ResRatio_t* Screen_ResRatio_Init(
	uint16_t total_Col, uint16_t total_Row,
	uint16_t pixel_Width, uint16_t pixel_Hight,
	uint16_t pixels_Total_Col, uint16_t pixels_Total_Row
)
{
	Screen_ResRatio.total_Col = total_Col;
	Screen_ResRatio.total_Row = total_Row;
	Screen_ResRatio.pixel_Width = pixel_Width;
	Screen_ResRatio.pixel_Hight = pixel_Hight;
	Screen_ResRatio.pixels_Total_Col = pixels_Total_Col;
	Screen_ResRatio.pixels_Total_Row = pixels_Total_Row;
	
	return &Screen_ResRatio;
}

void OLED_Refresh_Time(uint32_t sec)
{
	uint8_t digital = 0;
	uint32_t temp = sec;
	
	do {
		temp /= 10;
		digital++;
	} while(temp);
	
	if(digital * 8 < 128) OLED_Fill(0, 24, digital * 8, 24 + 8, CLEAR);
	else OLED_Fill(0, 24, 128 - 1, 24 + 8, CLEAR);
	OLED_ShowNum(0, 16, sec, digital, 8, FILL);
}

/*===========================================
	��Ϣ��������
===========================================*/

/**
 * @fn uint8_t read_Pixel(Screen_Pixel_Coor pixel)
 * @brief ��ȡ��Ļ��һ�����ص����Ϣ
 *
 * @param [pixel] ���ص��λ������
 * @return uint8_t ���ص����Ϣ
 */
uint8_t read_Pixel(Screen_Pixel_Coor pixel)
{
	Point_uint16_t point;
	uint8_t pixel_State;
	
	if((pixel.x >= Screen_ResRatio.pixels_Total_Col)
		|| (pixel.y >= Screen_ResRatio.pixels_Total_Row)) return -1;
	point.x = Screen_ResRatio.pixel_Width * pixel.x;
	point.y = Screen_ResRatio.pixel_Hight * pixel.y;
	pixel_State = OLED_ReadPoint(point.x, point.y);
	if(pixel_State == -1) pixel_State = SCREEN_POINT_BLACK;
	
	return pixel_State;
}

uint16_t get_Screen_ResRatio_totalCol(void)
{
	return Screen_ResRatio.total_Col;
}

uint16_t get_Screen_ResRatio_totalRow(void)
{
	return Screen_ResRatio.total_Row;
}

uint16_t get_Screen_ResRatio_PixelWidth(void)
{
	return Screen_ResRatio.pixel_Width;
}

uint16_t get_Screen_ResRatio_PixelHight(void)
{
	return Screen_ResRatio.pixel_Hight;
}

uint16_t get_Screen_ResRatio_PixelsTotalCol(void)
{
	return Screen_ResRatio.pixels_Total_Col;
}

uint16_t get_Screen_ResRatio_PixelsTotalRow(void)
{
	return Screen_ResRatio.pixels_Total_Row;
}

/*===========================================
	������ͼ����
===========================================*/

/**
 * @fn void Screen_DrawPixel(Screen_Pixel_Coor pixel, uint8_t mode)
 * @brief ����һ�����ص�
 *
 * @param [pixel] ���ص������
 * @param [mode] ����ģʽ
 * @return None
 */
void Screen_DrawPixel(Screen_Pixel_Coor pixel, uint8_t mode)
{
	uint16_t i, j;
	Point_uint16_t point_max, point_min;
	
	if((pixel.x >= Screen_ResRatio.pixels_Total_Col)
		|| (pixel.y >= Screen_ResRatio.pixels_Total_Row)) return;
	
	point_min.x = Screen_ResRatio.pixel_Width * pixel.x;
	point_min.y = Screen_ResRatio.pixel_Hight * pixel.y;
	point_max.x = Screen_ResRatio.pixel_Width * (pixel.x + 1);
	point_max.y = Screen_ResRatio.pixel_Hight * (pixel.y + 1);
	
	for(i = point_min.x; i < point_max.x; i++)
	{
		for(j = point_min.y; j < point_max.y; j++)
			OLED_DrawPoint(i, j, mode);
	}
}









