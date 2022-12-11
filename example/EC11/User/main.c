#include "main.h"

#include "bmp.h"

#include <stdlib.h>

#ifdef NULL
char address_is_null _at_ (0x0000);
#else
#define NULL		((void*)0)
#endif /* NULL */

/*=========================================================
	外部变量声明
=========================================================*/

/* 定时器2计时时间 */
extern uint32_t sec;

/*=========================================================
	菜单系统
=========================================================*/

menu_t menu_Start = {  // 开始菜单（开始画面）
	"menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // 一级菜单
	{ "screen", 1, 0, 1, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // 二级菜单
	{ "screen freq", 2, 1, 1, NULL, NULL, NULL, NULL }
};
menu_t menu_ThreeLevel[] = {  // 三级菜单
	{ "screen show freq", 3, 1, 1, NULL, NULL, NULL, screen_Show_Freq },
	{ "screen set freq", 3, 1, 2, NULL, NULL, NULL, screen_Set_Freq }
};

/*=========================================================
	主函数
=========================================================*/

void System_Init(void)
{
	My_UART_Init();
	My_Timer_Init();
	LED_Init();
	Key_Init();
	EC11_Init();
	OLED_Init();
	
	OLED_Screen_Freq = 30;  // 30Hz
	
    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_ThreeLevel[0]);
    insert_Menu(&menu_Start, &menu_ThreeLevel[1]);
	currentMenu = &menu_Start;
	pointerMenu = &menu_OneLevel[0];
	
	EA_OPN();
}

void main()
{
	Screen_ResRatio_t* Screen_Infor = NULL;
	
	System_Init();
	
	Screen_Infor = Screen_ResRatio_Init(
						SCREEN_COL_MAX, SCREEN_ROW_MAX,
						SCREEN_PIXEL_WIDTH_DEFAULT, SCREEN_PIXEL_HIGHT_DEFAULT,
						SCREEN_PIXELS_TOTAL_COL_DEFAULT, SCREEN_PIXELS_TOTAL_ROW_DEFAULT
					);
	
	screen_Show_subMenus(currentMenu);
	
	while(1)
	{
		if(OLED_Event_Flag & OLED_Update_Event) {
			OLED_Event_Flag &= ~OLED_Update_Event;
			OLED_Refresh_Gram();
		}
		if(EC11_Rotate_Times[0]) {
			pointerMenu_JumpForward(&menu_Start);
			EC11_Rotate_Times[0]--;
		}
		if(EC11_Rotate_Times[1]) {
			pointerMenu_JumpBack(&menu_Start);
			EC11_Rotate_Times[1]--;
		}
		if(Key_Scan(KEY_SCAN_SINGLE) == KEY0_PRES) {
			if(pointerMenu->nextLevel != NULL) {
				currentMenu = pointerMenu;
				pointerMenu = pointerMenu->nextLevel;
			}
			screen_Show_subMenus(currentMenu);
		}
	}
}









