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

#define MENU_INFOR_SIZE				(8)							/* ��OLED����ʾ�˵���Ϣ�������С */
#define MENU_INFOR_WIDTH			(MENU_INFOR_SIZE)			/* ��OLED����ʾ�˵���Ϣ�������� */
#define MENU_INFOR_HIGHT			(MENU_INFOR_SIZE)			/* ��OLED����ʾ�˵���Ϣ������߶� */
#define MENU_INFOR_COL				(0)							/* ��OLED����ʾ�˵���Ϣ��������ʼ������ */
#define MENU_INFOR_ROW				(0)							/* ��OLED����ʾ�˵���Ϣ��������ʼ������ */

#define POINTERMENU_SPACE			(1)							/* ͻ����ʾѡ�еĲ˵����õı�ʶ���ַ��� */

#define SUBMENUS_MAX_DIGITAL		(2)							/* ÿ�������˵���һ�����Ӽ��˵���Ŀ��λ�����ֵ */

/* ��ǰ�˵���ָ�� */
extern menu_t* currentMenu;
/* ��ָ��Ĳ˵���ָ�� */
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









