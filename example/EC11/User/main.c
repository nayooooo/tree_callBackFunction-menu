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
	�ⲿ��������
=========================================================*/

/* ��ʱ��2��ʱʱ�� */
extern uint32_t sec;

/*=========================================================
	�˵�ϵͳ
=========================================================*/

menu_t menu_Start = {  // ��ʼ�˵�����ʼ���棩
	"menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // һ���˵�
	{ "screen", 1, 0, 1, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // �����˵�
	{ "freq", 2, 1, 1, NULL, NULL, NULL, NULL }
};
menu_t menu_ThreeLevel[] = {  // �����˵�
	{ "show freq", 3, 1, 1, NULL, NULL, NULL, screen_Show_Freq },
	{ "set freq", 3, 1, 2, NULL, NULL, NULL, screen_Set_Freq }
};

/*=========================================================
	EC11 �ص�����ָ��
=========================================================*/

Main_CB_State (*EC11_CW_Event)(void);
Main_CB_State (*EC11_CCW_Event)(void);

/*=========================================================
	�ص���������
=========================================================*/

/* EC11 ���ܻص� */
Main_CB_State EC11_CW_MenuSwitch_CB(void);
Main_CB_State EC11_CCW_MenuSwitch_CB(void);

/*=========================================================
	������
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
		// ˢ����Ļ
		if(OLED_Event_Flag & OLED_Update_Event) {
			OLED_Event_Flag &= ~OLED_Update_Event;
			OLED_Refresh_Gram();
		}
		
		// EC11 �¼�
		if(EC11_Rotate_Times[0]) {
			EC11_CW_Event();
			EC11_Rotate_Times[0]--;
		}
		if(EC11_Rotate_Times[1]) {
			EC11_CCW_Event();
			EC11_Rotate_Times[1]--;
		}
		
		// �����¼�
		if(Key_Scan(KEY_SCAN_SINGLE) == KEY0_PRES) {
			if(currentMenu->nextLevel != NULL) {  // currentMenu ��������ͼ��˵�
				enter_pointerMenu();  // ����ѡ��Ĳ˵�
				if(pointerMenu->eventCB != NULL) {  // �ò˵��й��ܺ���
					carryOut_event();
				}else screen_Show_subMenus(currentMenu);
			} else {  // currentMenu ������ͼ��˵�
				back_SafeMenu(&menu_Start);
				EC11_CW_Event = EC11_CW_MenuSwitch_CB;
				EC11_CCW_Event = EC11_CCW_MenuSwitch_CB;
				screen_Show_subMenus(currentMenu);
			}
		}
	}
}

/*=========================================================
	EC11 ���ܻص�
=========================================================*/

// EC11_CW

/**
 * @fn Main_CB_State EC11_CW_MenuSwitch_CB(void)
 * @brief EC11˳ʱ����ת�л��˵�����
 *
 * @return [Main_CB_State] �������н���Ƿ���ȷ
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
 * @brief EC11��ʱ����ת�л��˵�����
 *
 * @return [Main_CB_State] �������н���Ƿ���ȷ
 */
Main_CB_State EC11_CCW_MenuSwitch_CB(void)
{
	pointerMenu_JumpBack(&menu_Start);
	screen_Show_PointerMenu();
	return MAIN_CB_OK;
}









