#include "menu.h"

#include <stdio.h>

// һ����˵��currentMenu �� pointerMenu ָ��Ĳ˵��ȼ���һ��
// ���ǣ����û�û��ѡ��˵�ʱ��currentMenu �� pointerMenu ָ��ͬһ���˵�
// ��������Ŀ����Ϊ�˷�ֹû��ͻ����ʾѡ���˵�ʱ���û����Խ���һ���˵�
menu_t* currentMenu = NULL;
menu_t* pointerMenu = NULL;

/**
 * @fn menu_t* screen_Show_subMenus(menu_t* parMenu)
 * @brief ��ʾ�˵�����һ���˵�
 *
 * @param [parMenu] ��Ҫ��ʾ�Ĳ˵��ĸ����˵�
 * @return [menu_t*] ������ʾ�Ĳ˵��ĸ����˵�ָ��
 */
menu_t* show_subMenus(menu_t* parMenu)
{
	uint8_t i = 0;
	uint8_t menu_Num = 0;
	menu_t* p = parMenu;

	if (p->nextLevel != NULL) {  // ��ǰ�˵����Ӽ��˵�
		p = p->nextLevel;
		// ��ʾһҳ�˵�
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
 * @brief ѡ��ǰһ���˵�
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ��ת֮��ı�ѡ�еĲ˵���ָ��
 */
menu_t* pointerMenu_JumpForward(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	// pointerMenu �� currentMenu �����쳣ʱ
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
 * @brief ѡ�к�һ���˵�
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ��ת֮��ı�ѡ�еĲ˵���ָ��
 */
menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	// pointerMenu �� currentMenu �����쳣ʱ
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
 * @brief ����ѡ�еĲ˵�
 *
 * @return [menu_t*] ����Ĳ˵���ָ��
 */
menu_t* enter_pointerMenu(void)
{
	currentMenu = pointerMenu;
	return currentMenu;
}

/**
 * @fn menu_t* back_SafeMenu(const menu_t_ptr menu_Start)
 * @brief ���ص���ȫ�Ĳ˵���ǰ���� currentMenu ���ڲ���ȫ�Ĳ˵�
 * @details ����ȫ�Ĳ˵�ָ���� [menu->nextLevel == NULL]
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ����� currentMenu ָ��Ĳ˵���ָ��
 */
menu_t* back_SafeMenu(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	if (currentMenu->nextLevel == NULL)  // currentMenu ָ�򲻰�ȫ�Ĳ˵�
	{
		tempMenu_ptr = find_parMenu(menu_Start, currentMenu);
		if (tempMenu_ptr != NULL) {
			currentMenu = tempMenu_ptr;
			pointerMenu = currentMenu;  // ����֮����Ҫ����ѡ��˵�
		}
	}
	return currentMenu;
}

/**
 * @fn menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start)
 * @brief ���ص���һ���˵�
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ����� currentMenu ָ��Ĳ˵���ָ��
 */
menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;

	if (pointerMenu->level > 0)  // ������һ���˵�������
	{
		tempMenu_ptr = find_parMenu(menu_Start, currentMenu);  // ������ʾ�Ĳ˵��� currentMenu ���Ӽ��˵�
		if (tempMenu_ptr != NULL) {
			currentMenu = tempMenu_ptr;
			pointerMenu = currentMenu;  // ����֮����Ҫ����ѡ��˵�
		}
		else if (pointerMenu->level == 1) {  // currentMenu ָ�� menu_Start �� pointerMenu ����ѡ��
			pointerMenu = currentMenu;
		}
	}
	return currentMenu;
}

/**
 * @fn menu_t* carryOut_event(void)
 * @brief ִ��ѡ�еĲ˵�������
 *
 * @return [menu_t*] ����ִ�еĲ˵���ָ��
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
