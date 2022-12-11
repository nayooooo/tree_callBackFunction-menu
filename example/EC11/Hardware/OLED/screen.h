/**
 * @file screen.h
 * @brief ��Ļ��ʾ�ļ�������SSD1306
 * @encoding GB2312
 * @author yewan
 */

#ifndef __SCREEN_H
#define __SCREEN_H

#include "config.h"
#include "oled.h"

/* ��Ļ��Ϣ�� --------------------------------------------*/

#define SCREEN_COL_MAX			OLED_COL_MAX
#define SCREEN_ROW_MAX			OLED_ROW_MAX

#define SCREEN_PIXEL_WIDTH_DEFAULT				(2)
#define SCREEN_PIXEL_HIGHT_DEFAULT				(2)
#define SCREEN_PIXELS_TOTAL_COL_DEFAULT			(SCREEN_COL_MAX / SCREEN_PIXEL_WIDTH_DEFAULT)
#define SCREEN_PIXELS_TOTAL_ROW_DEFAULT			(SCREEN_ROW_MAX / SCREEN_PIXEL_HIGHT_DEFAULT)

/* ���Ʊ���ö�� ------------------------------------------*/

typedef enum{
	OLED_No_Event = 0X00,			// ���¼�
	OLED_Update_Event = 0X01,		// ������Ļ
	OLED_Update_Sec  =0X02			// ����ʱ��
}OLED_Event_Flag_Typedef;

/* �����������Ʊ��� --------------------------------------*/

extern uint8_t OLED_Event_Flag;

/* ״̬�� ------------------------------------------------*/

#define SCREEN_POINT_WHITE		OLED_POINT_WHITE
#define SCREEN_POINT_BLACK		OLED_POINT_BLACK

#define SCREEN_FREQ_DIGITAL		(3)
#define SCREEN_FREQ_SIZE		(8)

/* ��������״̬���� --------------------------------------*/

extern uint8_t OLED_Screen_Freq;

/* ��Ļ���ñ������� --------------------------------------*/

/* ��Ļ�ֱ��� */
typedef struct{
	uint16_t total_Col;					// ��Ļ�ܵ�����
	uint16_t total_Row;					// ��Ļ�ܵ�����
	uint16_t pixel_Width;				// �������صĿ��
	uint16_t pixel_Hight;				// �������صĸ߶�
	uint16_t pixels_Total_Col;			// �ܹ����е����ص�����
	uint16_t pixels_Total_Row;			// �ܹ����е����ص�����
}Screen_ResRatio_t;

/* ��Ļ��ͼ�������� --------------------------------------*/

/* ���ص����� */
typedef struct{
	uint16_t x;
	uint16_t y;
}Screen_Pixel_Coor;

/* ��Ļ��ʾ���� ------------------------------------------*/

void OLED_Show_Hello(void);
void OLED_Show_Freq(void);
void OLED_Set_Freq(uint8_t newFreq);
void OLED_Refresh_Time(uint32_t sec);

void Screen_DrawPixel(Screen_Pixel_Coor pixel, uint8_t mode);
uint8_t read_Pixel(Screen_Pixel_Coor pixel);

uint16_t get_Screen_ResRatio_totalCol(void);
uint16_t get_Screen_ResRatio_totalRow(void);
uint16_t get_Screen_ResRatio_PixelWidth(void);
uint16_t get_Screen_ResRatio_PixelHight(void);
uint16_t get_Screen_ResRatio_PixelsTotalCol(void);
uint16_t get_Screen_ResRatio_PixelsTotalRow(void);

/* ��Ļ���ú��� ------------------------------------------*/

Screen_ResRatio_t* Screen_ResRatio_Init(
	uint16_t total_Col, uint16_t total_Row,
	uint16_t pixel_Width, uint16_t pixel_Hight,
	uint16_t pixels_Total_Col, uint16_t pixels_Total_Row
);

#endif
