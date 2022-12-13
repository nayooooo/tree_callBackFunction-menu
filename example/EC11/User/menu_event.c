#include "menu_event.h"

#include "screen.h"

menuEventState screen_Show_Freq(void) reentrant
{
	OLED_Clear();
	OLED_Show_Freq();
	return MENU_EVENT_OK;
}

menuEventState screen_Set_Freq(void) reentrant
{
	OLED_Show_Hello();
	return MENU_EVENT_OK;
}









