#ifndef __MENU_LINK_H
#define __MENU_LINK_H

#include "menu.h"
#include "menu_type.h"
#include "menu_configMicro.h"

void traversal_Menu(const menu_P_t menu_Start);
menu_t* find_Menu(const menu_P_t menu_Start, const menu_t* const menu_Target);
menu_t* find_parMenu(const menu_P_t menu_Start, const menu_t* const subMenu);
menu_t* insert_Menu(const menu_P_t menu_Start, menu_t* const menu_Insert);
menu_t* delete_Menu(const menu_P_t menu_Start, menu_t* const menu_Delete);

#endif /* __MENU_LINK_H */
