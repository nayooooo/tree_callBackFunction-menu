#include "screen.h"

#include <stdlib.h>
#include <math.h>

#include "delay.h"

OLED_Event_Flag_Typedef OLED_Event_Flag = OLED_No_Event;

void OLED_Show_Hello_Type1(void)
{
	OLED_Fill(0, 56, 128 - 1, 56 + 8, CLEAR);
	OLED_ShowString(0, 56, (u8*)"Hello World!", 8, FILL);
}

void OLED_Show_Hello_Type2(void)
{
	OLED_Fill(0, 56, 128 - 1, 56 + 8, CLEAR);
	OLED_ShowString(0, 56, (u8*)"Hello C51!", 8, FILL);
}

void OLED_Show_Menu_Infor(menu_t* menu)
{
	OLED_ShowString(0, 0, (uint8_t*)"target menu: ", 8, FILL);
	OLED_Fill(16, 8, 127, 16, CLEAR);
	OLED_ShowString(16, 8, menu->name, 8, FILL);
	OLED_ShowString(0, 16, (uint8_t*)"level: ", 8, FILL);
	OLED_ShowNums(80, 16, menu->level, 8, FILL);
	OLED_ShowString(0, 24, (uint8_t*)"parVal: ", 8, FILL);
	OLED_ShowNums(80, 24, menu->parVal, 8, FILL);
	OLED_ShowString(0, 32, (uint8_t*)"selfVal: ", 8, FILL);
	OLED_ShowNums(80, 32, menu->selfVal, 8, FILL);
}









