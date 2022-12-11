#ifndef __MENU_EVENT_H
#define __MENU_EVENT_H

#include "config.h"
#include "menu.h"

/*=========================================================
	三级菜单功能函数
=========================================================*/

menuEventState screen_Show_Freq(void) reentrant;
menuEventState screen_Set_Freq(uint8_t newFreq) reentrant;

#endif /* __MENU_EVENT_H */









