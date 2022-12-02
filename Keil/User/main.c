#include "main.h"

#ifdef NULL
	 char address_is_null _at_ (0x0000);
#else
	#define NULL		((void*)0)
#endif /* NULL */

menu_t menu_Start = {  // 开始菜单（开始画面）
	"menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // 一级菜单
	{ "hello", 1, 0, 1, NULL, NULL, NULL, NULL },
	{ "count", 1, 0, 2, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // 二级菜单
	{ "Hello World!", 2, 1, 1, NULL, NULL, NULL, OLED_Show_Hello_World },
	{ "Hello C51!", 2, 1, 2, NULL, NULL, NULL, OLED_Show_Hello_C51 }
};

void System_Init(void)
{
	My_USART_Init();
	key_Init();
	OLED_Init();
	
	MyTimer_Init();
	
	EA_OPN();  // 开启总中断
}

void main()
{
	menu_t* q = &menu_OneLevel[0];
	menu_t* mark = &menu_OneLevel[0];
	menu_t menu_Temp;
	menu_Temp.level = 2;
	menu_Temp.selfVal = 2;
	
	System_Init();
	
    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_OneLevel[1]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[1]);
	
	q = find_Menu(&menu_Start, &menu_Temp);
	if(q != NULL) {
		OLED_Show_Menu_Infor(q); OLED_Refresh_Gram();
		q->eventCB(q);
	} else {
		OLED_Fill(0, 56, 128 - 1, 56 + 8, CLEAR);
		OLED_ShowString(0, 58, (u8*)"not find!", 8, FILL);
		OLED_Refresh_Gram();
	}
	
	while(1)
	{
		;
	}
}









