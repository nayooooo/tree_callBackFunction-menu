#ifndef __SCREEN_H
#define __SCREEN_H

#include "config.h"
#include "oled.h"

#include "menu.h"

typedef enum{
	OLED_No_Event,			// 无事件
	OLED_Refresh_Event		// 更新事件
}OLED_Event_Flag_Typedef;

void OLED_Show_Hello_Type1(void);
void OLED_Show_Hello_Type2(void);

/*===========================================================
	menu
===========================================================*/

void OLED_Show_Menu_Infor(menu_t* menu);


#endif
