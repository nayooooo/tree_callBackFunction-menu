#include "menu_link.h"

#include <stdio.h>

/**
 * @fn void traversal_Menu(const menu_P_t menu_Start)
 * @brief traversal the menu system
 *
 * @param [menu_Start] subtree's pointer
 * @return None
 */
void traversal_Menu(const menu_P_t menu_Start)
{
	menu_t* p = menu_Start;

	if (p == NULL) return;
	else printf("%d %d %d name: %s\r\n", p->level, p->parVal, p->selfVal, p->name);

	if (p->nextLevel != NULL) traversal_Menu(p->nextLevel);
	if (p->next != NULL) traversal_Menu(p->next);
}

/**
 * @fn menu_t* find_Menu(const menu_P_t menu_Start, const menu_t* const menu_Target)
 * @brief find the position of a menu in the current menu system
 * @details
 *	1. we just know the target menu's three param
 *	2. the all "level" menus is belong to "level - 1" menus
 *
 * @param [menu_Start] subtree's pointer
 * @param [menu_Target] target menu, only use it's three param
 * @return menu_t* target menu's address
 */
menu_t* find_Menu(const menu_P_t menu_Start, const menu_t* const menu_Target)
{
	menu_t* p = menu_Start;
	menu_t* q = NULL;

	if (p == NULL) return NULL;
	if (p->level > menu_Target->level) return NULL;

	if ((p->level == menu_Target->level)
		&& (p->selfVal == menu_Target->selfVal))
	{
		return p;
	}

	if (p->nextLevel != NULL) q = find_Menu(p->nextLevel, menu_Target);
	if (q != NULL) return q;
	if (p->next != NULL) q = find_Menu(p->next, menu_Target);
	return q;
}

/**
 * @fn menu_t* find_parMenu(const menu_P_t menu_Start, const menu_t* const subMenu)
 * @brief find the position of a menu's parMenu in the current menu system
 * @details
 *	1. we just know the target menu's three param
 *	2. the all "level" menus is belong to "level - 1" menus
 *
 * @param [menu_Start] subtree's pointer
 * @param [subMenu] target menu, only use it's three param
 * @return menu_t* target menu's address
 */
menu_t* find_parMenu(const menu_P_t menu_Start, const menu_t* const subMenu)
{
	menu_t* p = menu_Start;
	menu_t* q = NULL;

	if (p == NULL) return NULL;
	if (p->level > subMenu->level - 1) return NULL;

	if ((subMenu->level > 0)
		&& (p->level == subMenu->level - 1)
		&& (p->selfVal == subMenu->parVal))
	{
		return p;
	}

	if (p->nextLevel != NULL) q = find_parMenu(p->nextLevel, subMenu);
	if (q != NULL) return q;
	if (p->next != NULL) q = find_parMenu(p->next, subMenu);
	return q;
}

/**
 * @fn menu_t* insert_Menu(const menu_P_t menu_Start, const menu_t* const menu_Insert)
 * @brief insert a menu into menu system
 *
 * @param [menu_Start] subtree's pointer
 * @param [menu_Insert] menu witch will be inserted
 * @return [menu_t*] menu system's pointer
 */
menu_t* insert_Menu(const menu_P_t menu_Start, menu_t* const menu_Insert)
{
	menu_t p;
	menu_t* q = NULL;
	p.level = menu_Insert->level - 1;
	p.selfVal = menu_Insert->parVal;

	q = find_Menu(menu_Start, &p);
	if (q != NULL) {  // find it prev menu
		if (q->nextLevel == NULL) {  // parMenu do not have subMenu
			q->nextLevel = menu_Insert;
			menu_Insert->prev = q;
		}
		else {
			q = q->nextLevel;
			while (q->selfVal <= menu_Insert->selfVal) {
				if (q->next != NULL) q = q->next;
				else break;
			}
			if (menu_Insert->selfVal < q->selfVal) {  // ahead q
				if (q->prev->level < menu_Insert->level)  // only one menu belong to the parMenu
					q->prev->nextLevel = menu_Insert;
				else
					q->prev->next = menu_Insert;
				menu_Insert->prev = q->prev;
				q->prev = menu_Insert;
				menu_Insert->next = q;
			}
			else {  // rear q, and the parMenu has only one menu
				q->next = menu_Insert;
				menu_Insert->prev = q;
			}
		}
	}
	else printf("can't connect it to system, by not find it's prev menu!\r\n");

	return menu_Start;
}

/**
 * @fn menu_t* delete_Menu(const menu_P_t menu_Start, menu_t* const menu_Delete)
 * @brief delete a menu into menu system
 *
 * @param [menu_Start] subtree's pointer
 * @param [menu_Delete] menu witch will be deleted
 * @return [menu_t*] menu system's pointer
 */
menu_t* delete_Menu(const menu_P_t menu_Start, menu_t* const menu_Delete)
{
	menu_t* q = NULL;

	q = find_Menu(menu_Start, menu_Delete);
	if ((q != NULL) && (q != menu_Start)) {  // find it and it not start menu
		if (q->next == NULL) {  // at the end of parMenu's subMenus
			if (q->prev->level < q->level)  // at the head of parMenu's subMenus
				q->prev->nextLevel = NULL;
			else
				q->prev->next = NULL;
			q->prev = NULL;
		}
		else {
			if (q->prev->level < q->level)  // at the head of parMenu's subMenus
				q->prev->nextLevel = q->next;
			else
				q->prev->next = q->next;
			q->next->prev = q->prev;
			q->prev = NULL;
			q->next = NULL;
		}
	}
	else if(q == menu_Start) printf("can't delete, by error menu_Delete param!\r\n");
	else printf("can't delete, by not find it!\r\n");

	return menu_Start;
}
