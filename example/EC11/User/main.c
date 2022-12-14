/**
 * @file main.c
 * @author yewan
 * @encoding GB2312
 */

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
	{ "freq", 2, 1, 1, NULL, NULL, NULL, NULL }
};
menu_t menu_ThreeLevel[] = {  // 三级菜单
	{ "show freq", 3, 1, 1, NULL, NULL, NULL, screen_Show_Freq },
	{ "set freq", 3, 1, 2, NULL, NULL, NULL, screen_Set_Freq }
};

/*=========================================================
	EC11 回调函数指针
=========================================================*/

Main_CB_State (*EC11_CW_Event)(void);
Main_CB_State (*EC11_CCW_Event)(void);

/*=========================================================
	回调函数声明
=========================================================*/

/* EC11 功能回调 */
Main_CB_State EC11_CW_MenuSwitch_CB(void);
Main_CB_State EC11_CCW_MenuSwitch_CB(void);

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
	pointerMenu = &menu_Start;
	
	EA_OPN();
}

void main()
{
	Screen_ResRatio_t* Screen_Infor = NULL;
	
	EC11_CW_Event = EC11_CW_MenuSwitch_CB;
	EC11_CCW_Event = EC11_CCW_MenuSwitch_CB;
	
	System_Init();
	
	Screen_Infor = Screen_ResRatio_Init(
						SCREEN_COL_MAX, SCREEN_ROW_MAX,
						SCREEN_PIXEL_WIDTH_DEFAULT, SCREEN_PIXEL_HIGHT_DEFAULT,
						SCREEN_PIXELS_TOTAL_COL_DEFAULT, SCREEN_PIXELS_TOTAL_ROW_DEFAULT
					);
	
	screen_Show_subMenus(currentMenu);
	
	while(1)
	{
		// 刷新屏幕
		if(OLED_Event_Flag & OLED_Update_Event) {
			OLED_Event_Flag &= ~OLED_Update_Event;
			OLED_Refresh_Gram();
		}
		
		// EC11 事件
		if(EC11_Rotate_Times[0]) {
			EC11_CW_Event();
			EC11_Rotate_Times[0]--;
		}
		if(EC11_Rotate_Times[1]) {
			EC11_CCW_Event();
			EC11_Rotate_Times[1]--;
		}
		
		// 按键事件
		if(Key_Scan(KEY_SCAN_SINGLE) == KEY0_PRES) {
			if(currentMenu->nextLevel != NULL) {  // currentMenu 不处在最低级菜单
				enter_pointerMenu();  // 进入选择的菜单
				if(pointerMenu->eventCB != NULL) {  // 该菜单有功能函数
					carryOut_event();
				}else screen_Show_subMenus(currentMenu);
			} else {  // currentMenu 处在最低级菜单
				back_SafeMenu(&menu_Start);
				EC11_CW_Event = EC11_CW_MenuSwitch_CB;
				EC11_CCW_Event = EC11_CCW_MenuSwitch_CB;
				screen_Show_subMenus(currentMenu);
			}
		}
	}
}

/*=========================================================
	EC11 功能回调
=========================================================*/

// EC11_CW

/**
 * @fn Main_CB_State EC11_CW_MenuSwitch_CB(void)
 * @brief EC11顺时针旋转切换菜单功能
 *
 * @return [Main_CB_State] 函数运行结果是否正确
 */
Main_CB_State EC11_CW_MenuSwitch_CB(void)
{
	pointerMenu_JumpForward(&menu_Start);
	screen_Show_PointerMenu();
	return MAIN_CB_OK;
}

// EC11_CCW

/**
 * @fn Main_CCB_State EC11_CW_MenuSwitch_CB(void)
 * @brief EC11逆时针旋转切换菜单功能
 *
 * @return [Main_CB_State] 函数运行结果是否正确
 */
Main_CB_State EC11_CCW_MenuSwitch_CB(void)
{
	pointerMenu_JumpBack(&menu_Start);
	screen_Show_PointerMenu();
	return MAIN_CB_OK;
}









