#include "menu_event.h"

#include "screen.h"

menuEventState OLED_Show_Hello_World(void)
{
	OLED_Show_Hello_Type1();
	OLED_Refresh_Gram();
	
	return MENU_EVENT_OK;
}

menuEventState OLED_Show_Hello_C51(void)
{
	OLED_Show_Hello_Type2();
	OLED_Refresh_Gram();
	
	return MENU_EVENT_OK;
}









