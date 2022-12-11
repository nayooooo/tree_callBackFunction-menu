/**
 * @file screen.h
 * @brief 屏幕显示文件，基于SSD1306
 * @encoding GB2312
 * @author yewan
 */

#ifndef __SCREEN_H
#define __SCREEN_H

#include "config.h"
#include "oled.h"

/* 屏幕信息宏 --------------------------------------------*/

#define SCREEN_COL_MAX			OLED_COL_MAX
#define SCREEN_ROW_MAX			OLED_ROW_MAX

#define SCREEN_PIXEL_WIDTH_DEFAULT				(2)
#define SCREEN_PIXEL_HIGHT_DEFAULT				(2)
#define SCREEN_PIXELS_TOTAL_COL_DEFAULT			(SCREEN_COL_MAX / SCREEN_PIXEL_WIDTH_DEFAULT)
#define SCREEN_PIXELS_TOTAL_ROW_DEFAULT			(SCREEN_ROW_MAX / SCREEN_PIXEL_HIGHT_DEFAULT)

/* 控制变量枚举 ------------------------------------------*/

typedef enum{
	OLED_No_Event = 0X00,			// 无事件
	OLED_Update_Event = 0X01,		// 更新屏幕
	OLED_Update_Sec  =0X02			// 更新时间
}OLED_Event_Flag_Typedef;

/* 对外声明控制变量 --------------------------------------*/

extern uint8_t OLED_Event_Flag;

/* 状态宏 ------------------------------------------------*/

#define SCREEN_POINT_WHITE		OLED_POINT_WHITE
#define SCREEN_POINT_BLACK		OLED_POINT_BLACK

#define SCREEN_FREQ_DIGITAL		(3)
#define SCREEN_FREQ_SIZE		(8)

/* 对外声明状态变量 --------------------------------------*/

extern uint8_t OLED_Screen_Freq;

/* 屏幕设置变量类型 --------------------------------------*/

/* 屏幕分辨率 */
typedef struct{
	uint16_t total_Col;					// 屏幕总的列数
	uint16_t total_Row;					// 屏幕总的行数
	uint16_t pixel_Width;				// 单个像素的宽度
	uint16_t pixel_Hight;				// 单个像素的高度
	uint16_t pixels_Total_Col;			// 总共含有的像素的列数
	uint16_t pixels_Total_Row;			// 总共含有的像素的行数
}Screen_ResRatio_t;

/* 屏幕绘图变量类型 --------------------------------------*/

/* 像素点坐标 */
typedef struct{
	uint16_t x;
	uint16_t y;
}Screen_Pixel_Coor;

/* 屏幕显示函数 ------------------------------------------*/

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

/* 屏幕设置函数 ------------------------------------------*/

Screen_ResRatio_t* Screen_ResRatio_Init(
	uint16_t total_Col, uint16_t total_Row,
	uint16_t pixel_Width, uint16_t pixel_Hight,
	uint16_t pixels_Total_Col, uint16_t pixels_Total_Row
);

#endif
