#ifndef __MENU_H
#define __MENU_H

#include "menu_type.h"
#include "menu_configMicro.h"
#include "menu_link.h"

/* 当前菜单的指针 */
extern menu_t* currentMenu;
/* 正指向的菜单的指针 */
extern menu_t* pointerMenu;

menu_t* show_subMenus(menu_t* parMenu);
menu_t* pointerMenu_JumpForward(const menu_t_ptr menu_Start);
menu_t* pointerMenu_JumpBack(const menu_t_ptr menu_Start);
menu_t* enter_pointerMenu(void);
menu_t* back_SafeMenu(const menu_t_ptr menu_Start);
menu_t* back_PrevLevelMenu(const menu_t_ptr menu_Start);
menu_t* carryOut_event(void);

#endif /* __MENU_H */
