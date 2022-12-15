/**
 * @file menu.h
 * @detail menu system
 * @author yewan
 * @encoding GB2312
 */

#ifndef __MENU_H
#define __MENU_H

#include "menu_type.h"
#include "menu_configMicro.h"
#include "menu_link.h"

#define MENU_INFOR_SIZE				(8)							/* 在OLED上显示菜单信息的字体大小 */
#define MENU_INFOR_WIDTH			(MENU_INFOR_SIZE)			/* 在OLED上显示菜单信息的字体宽度 */
#define MENU_INFOR_HIGHT			(MENU_INFOR_SIZE)			/* 在OLED上显示菜单信息的字体高度 */
#define MENU_INFOR_COL				(0)							/* 在OLED上显示菜单信息的字体起始横坐标 */
#define MENU_INFOR_ROW				(0)							/* 在OLED上显示菜单信息的字体起始纵坐标 */

#define POINTERMENU_SPACE			(1)							/* 突出显示选中的菜单所用的标识的字符数 */

#define SUBMENUS_MAX_DIGITAL		(2)							/* 每个父级菜单下一级的子级菜单数目的位数最大值 */

/* 当前菜单的指针 */
extern menu_t* currentMenu;
/* 正指向的菜单的指针 */
extern menu_t* pointerMenu;

menu_t* screen_Show_subMenus(menu_t* parMenu);
menu_t* screen_Show_PointerMenu(void);
menu_t* pointerMenu_JumpForward(const menu_t_ptr menu_Start);
menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start);
menu_t* enter_pointerMenu(void);
menu_t* back_SafeMenu(const menu_t_ptr menu_Start);
menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start);
menu_t* carryOut_event(void);

#endif /* __MENU_H */









