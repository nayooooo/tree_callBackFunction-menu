/**
 * @file menu_link.h
 * @detail menu system's link methode
 * @author yewan
 * @encoding GB2312
 */

#ifndef __MENU_LINK_H
#define __MENU_LINK_H

#include "menu.h"
#include "menu_type.h"
#include "menu_configMicro.h"

void traversal_MenuSystem(const menu_t_ptr menu_Start) reentrant;
void traversal_subMenus(const menu_t* const parMenu);
menu_t* show_subMenus_nextLevel(const menu_t* const parMenu);
menu_t* find_Menu(const menu_t_ptr menu_Start, const menu_t* const menu_Target) reentrant;
menu_t* find_parMenu(const menu_t_ptr menu_Start, const menu_t* const subMenu) reentrant;
menu_t* find_prevMenu(const menu_t_ptr menu_Start, const menu_t* const menu) reentrant;
menu_t* find_nextMenu(const menu_t_ptr menu_Start, const menu_t* const menu) reentrant;
uint8_t count_NextLevelMenu_Num(const menu_t_ptr menu_Start);
uint8_t count_SameLevel_PrevMenu_Num(const menu_t* const menu);
menu_t_ptr insert_Menu(const menu_t_ptr menu_Start, menu_t* const menu_Insert);
menu_t_ptr delete_Menu(const menu_t_ptr menu_Start, menu_t* const menu_Delete);

#endif /* __MENU_LINK_H */









