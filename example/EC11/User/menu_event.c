#include "menu_event.h"

#include "screen.h"

/* EC11 回调函数指针(main.c) */
extern Main_CB_State (*EC11_CW_Event)(void);
extern Main_CB_State (*EC11_CCW_Event)(void);

menuEventState screen_Show_Freq(void) reentrant
{
	OLED_Clear();
	OLED_Show_Freq();
	return MENU_EVENT_OK;
}

menuEventState screen_Set_Freq(void) reentrant
{
	EC11_CW_Event = (Main_CB_State(*)(void))OLED_Add_Freq;
	EC11_CCW_Event = (Main_CB_State(*)(void))OLED_Sub_Freq;
	OLED_Clear();
	OLED_Show_Freq();
	OLED_ShowString(0, 16, (u8*)"set freq: ", 8, FILL);
	OLED_ShowString(0, 24, (u8*)"(will disappear...)", 8, FILL);
	return MENU_EVENT_OK;
}









