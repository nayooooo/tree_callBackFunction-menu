#include "menu.h"

#include <stdio.h>

// 一般来说，currentMenu 比 pointerMenu 指向的菜单等级高一级
// 但是，当用户没有选择菜单时，currentMenu 和 pointerMenu 指向同一个菜单
// 这样做的目的是为了防止没有突出显示选定菜单时，用户可以进入一个菜单
menu_t* currentMenu = NULL;
menu_t* pointerMenu = NULL;

/**
 * @fn menu_t* screen_Show_subMenus(menu_t* parMenu)
 * @brief 显示菜单的下一级菜单
 *
 * @param [parMenu] 将要显示的菜单的父级菜单
 * @return [menu_t*] 正在显示的菜单的父级菜单指针
 */
menu_t* show_subMenus(menu_t* parMenu)
{
	uint8_t i = 0;
	uint8_t menu_Num = 0;
	menu_t* p = parMenu;

	if (p->nextLevel != NULL) {  // 当前菜单有子级菜单
		p = p->nextLevel;
		// 显示一页菜单
		do {
			printf("%s\r\n", p->name);
			i++;
			p = p->next;
		} while (p != NULL);
	}
	else {
		printf("None!\r\n");
	}

	return parMenu;
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

	// pointerMenu 和 currentMenu 均无异常时
	if ((pointerMenu != NULL) && (currentMenu != NULL)
		&& (pointerMenu->level == currentMenu->level + 1))
	{
		tempMenu_ptr = find_prevMenu(menu_Start, pointerMenu);
		if (tempMenu_ptr != NULL) pointerMenu = tempMenu_ptr;
	}
	else if ((pointerMenu != NULL) && (currentMenu != NULL))
	{
		if (currentMenu->nextLevel != NULL)
			pointerMenu = currentMenu->nextLevel;
	}

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

	// pointerMenu 和 currentMenu 均无异常时
	if ((pointerMenu != NULL) && (currentMenu != NULL)
		&& (pointerMenu->level == currentMenu->level + 1))
	{
		tempMenu_ptr = find_nextMenu(menu_Start, pointerMenu);
		if (tempMenu_ptr != NULL) pointerMenu = tempMenu_ptr;
	}
	else if ((pointerMenu != NULL) && (currentMenu != NULL))
	{
		if (currentMenu->nextLevel != NULL)
			pointerMenu = currentMenu->nextLevel;
	}

	return pointerMenu;
}

/**
 * @fn menu_t* enter_pointerMenu(void)
 * @brief 进入选中的菜单
 *
 * @return [menu_t*] 进入的菜单的指针
 */
menu_t* enter_pointerMenu(void)
{
	currentMenu = pointerMenu;
	return currentMenu;
}

/**
 * @fn menu_t* back_SafeMenu(const menu_t_ptr menu_Start)
 * @brief 返回到安全的菜单，前提是 currentMenu 处在不安全的菜单
 * @details 不安全的菜单指的是 [menu->nextLevel == NULL]
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] 处理后 currentMenu 指向的菜单的指针
 */
menu_t* back_SafeMenu(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	if (currentMenu->nextLevel == NULL)  // currentMenu 指向不安全的菜单
	{
		tempMenu_ptr = find_parMenu(menu_Start, currentMenu);
		if (tempMenu_ptr != NULL) {
			currentMenu = tempMenu_ptr;
			pointerMenu = currentMenu;  // 返回之后需要重新选择菜单
		}
	}
	return currentMenu;
}

/**
 * @fn menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start)
 * @brief 返回到上一级菜单
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] 处理后 currentMenu 指向的菜单的指针
 */
menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	if (pointerMenu->level > 0)  // 返回上一级菜单有意义
	{
		tempMenu_ptr = find_parMenu(menu_Start, currentMenu);  // 正在显示的菜单是 currentMenu 的子级菜单
		if (tempMenu_ptr != NULL) {
			currentMenu = tempMenu_ptr;
			pointerMenu = currentMenu;  // 返回之后需要重新选择菜单
		}
		else if (pointerMenu->level == 1) {  // currentMenu 指向 menu_Start 且 pointerMenu 正在选择
			pointerMenu = currentMenu;
		}
	}
	return currentMenu;
}

/**
 * @fn menu_t* carryOut_event(void)
 * @brief 执行选中的菜单的任务
 *
 * @return [menu_t*] 正在执行的菜单的指针
 */
menu_t* carryOut_event(void)
{
	enter_pointerMenu();
	if (currentMenu->eventCB != NULL)
	{
		currentMenu->eventCB();
	}
	return currentMenu;
}
