#ifndef __MENU_TYPE_H
#define __MENU_TYPE_H

#include <stdint.h>
#include "menu_configMicro.h"

#define MENU_NAME_LENGHT			(20)

/*============================================
	variable typedef
============================================*/

typedef enum {
	MENU_EVENT_OK = 0,
	MENU_EVENT_ERR
}menuEventState;

/* menu level typedef */
typedef uint8_t menu_Level_t;

/* menu value typedef */
typedef uint8_t menu_Val_t;

/* menu struct */
/* only start menu's level, parVal, selfVal can be set 0 */
typedef struct menu_t {
	// infor of menu
	uint8_t name[MENU_NAME_LENGHT];
	// contact
	menu_Level_t level;						// menu level
	menu_Val_t parVal;						// parent menu value
	menu_Val_t selfVal;						// self menu value
	struct menu_t* prev;
	struct menu_t* next;
	struct menu_t* nextLevel;
	// event processing
	menuEventState(*eventCB)(struct menu_t*);		// event task
}menu_t, * menu_P_t;

#endif /* __MENU_TYPE_H */
