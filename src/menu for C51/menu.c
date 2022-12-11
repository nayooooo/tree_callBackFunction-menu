/**
 * @file menu.c
 * @detail menu system
 * @author yewan
 * @encoding GB2312
 */

#include "menu.h"

#include "screen.h"

// һ����˵��currentMenu �� pointerMenu ָ��Ĳ˵��ȼ���һ��
menu_t* currentMenu = NULL;
menu_t* pointerMenu = NULL;

/**
 * @fn menu_t* screen_Show_subMenus(menu_t* parMenu)
 * @brief ��һ���˵�����һ���˵���ʾ����Ļ��
 *
 * @param [parMenu] ��Ҫ��ʾ�Ĳ˵��ĸ����˵�
 * @return [menu_t*] ������ʾ�Ĳ˵��ĸ����˵�ָ��
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
 * @brief ����Ļ��ͻ����ʾ��ǰѡ�еĲ˵�
 *
 * @return [menu_t*] ��ǰѡ�еĲ˵���ָ��
 */
menu_t* screen_Show_PointerMenu(void)
{
	uint8_t i = 0;
	// get_Screen_ResRatio_totalRow() ���ڻ�ȡ��Ļ�������
	uint8_t num = get_Screen_ResRatio_totalRow() / MENU_INFOR_HIGHT;  // һ����Ļ������ɲ˵���
	menu_t* p = pointerMenu;
	
	// ���ѡ�еĲ˵��ڵ�ǰ�˵����е���ţ�0��Ϊ��һ���˵�
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
 * @brief ѡ��ǰһ���˵�
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ��ת֮��ı�ѡ�еĲ˵���ָ��
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
 * @brief ѡ�к�һ���˵�
 *
 * @param [menu_Start] menu system's pointer
 * @return [menu_t*] ��ת֮��ı�ѡ�еĲ˵���ָ��
 */
menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start)
{
	menu_t* tempMenu_ptr = NULL;
	
	tempMenu_ptr = find_nextMenu(menu_Start, pointerMenu);
	if(tempMenu_ptr != NULL) pointerMenu = tempMenu_ptr;
	screen_Show_PointerMenu();
	
	return pointerMenu;
}









