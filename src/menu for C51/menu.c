/**
 * @file menu.c
 * @detail menu system
 * @author yewan
 * @encoding GB2312
 */

#include "menu.h"

#include "screen.h"

// 一般来说，currentMenu 比 pointerMenu 指向的菜单等级高一级
menu_t* currentMenu = NULL;
menu_t* pointerMenu = NULL;

/**
 * @fn menu_t* screen_Show_subMenus(menu_t* parMenu)
 * @brief 将一个菜单的下一级菜单显示到屏幕上
 *
 * @param [parMenu] 将要显示的菜单的父级菜单
 * @return [menu_t*] 正在显示的菜单的父级菜单指针
 */
menu_t* screen_Show_subMenus(menu_t* parMenu)
{
	uint8_t i = 0;
	menu_t* p = parMenu;
	
	OLED_Clear();
	if (p->nextLevel != NULL) {
		p = p->nextLevel;
		do {
			OLED_ShowString(MENU_INFOR_COL + POINTERMENU_SPACE * MENU_INFOR_WIDTH,
							MENU_INFOR_ROW + i * MENU_INFOR_HIGHT,
							p->name, MENU_INFOR_SIZE, FILL);
			i++;
			p = p->next;
		} while ((p != NULL) && (i < OLED_ROW_MAX / MENU_INFOR_HIGHT));
	} else {
		OLED_ShowString(MENU_INFOR_COL + POINTERMENU_SPACE * MENU_INFOR_WIDTH,
						MENU_INFOR_ROW, (u8*)"None!", MENU_INFOR_SIZE, FILL);
	}
	OLED_Fill(0, 0, POINTERMENU_SPACE * MENU_INFOR_HIGHT, get_Screen_ResRatio_totalRow(), CLEAR);

	return parMenu;
}

/**
 * @fn menu_t* screen_Show_PointerMenu(void)
 * @brief 在屏幕中突出显示当前选中的菜单
 *
 * @return [menu_t*] 当前选中的菜单的指针
 */
menu_t* screen_Show_PointerMenu(void)
{
	uint8_t i = 0;
	// get_Screen_ResRatio_totalRow() 用于获取屏幕最大行数
	uint8_t num = get_Screen_ResRatio_totalRow() / MENU_INFOR_HIGHT;  // 一面屏幕最大容纳菜单数
	menu_t* p = pointerMenu;
	
	// 检查选中的菜单在当前菜单栏中的序号，0号为第一个菜单
	while((p->prev != NULL) && (p->prev->level == p->level))
	{
		i++;
		p = p->prev;
	}
	OLED_Fill(0, 0, POINTERMENU_SPACE * MENU_INFOR_HIGHT, get_Screen_ResRatio_totalRow(), CLEAR);
	OLED_ShowString(MENU_INFOR_COL, MENU_INFOR_ROW + (i % num) * MENU_INFOR_HIGHT,
					(u8*)">", MENU_INFOR_SIZE, FILL);
	
	return pointerMenu;
}

/**
 * @fn menu_t* pointerMenu_JumpForward(const menu_t_ptr menu_Start)
 * @brief 选中前一个菜单
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] 跳转之后的被选中的菜单的指针
 */
menu_t* pointerMenu_JumpForward(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;
	
	tempMenu_ptr = find_prevMenu(menu_Start, pointerMenu);
	if(tempMenu_ptr != NULL) pointerMenu = tempMenu_ptr;
	screen_Show_PointerMenu();
	
	return pointerMenu;
}

/**
 * @fn menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start)
 * @brief 选中后一个菜单
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] 跳转之后的被选中的菜单的指针
 */
menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;
	
	tempMenu_ptr = find_nextMenu(menu_Start, pointerMenu);
	if(tempMenu_ptr != NULL) pointerMenu = tempMenu_ptr;
	screen_Show_PointerMenu();
	
	return pointerMenu;
}









