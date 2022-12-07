#include "main.h"

#ifdef NULL
	 char address_is_null _at_ (0x0000);
#else
	#define NULL		((void*)0)
#endif /* NULL */

/*=========================================================
	�˵�ϵͳ
=========================================================*/

menu_t menu_Start = {  // ��ʼ�˵�����ʼ���棩
	"menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // һ���˵�
	{ "hello", 1, 0, 1, NULL, NULL, NULL, NULL },
	{ "count", 1, 0, 2, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // �����˵�
	{ "Hello World!", 2, 1, 1, NULL, NULL, NULL, OLED_Show_Hello_World },
	{ "Hello C51!", 2, 1, 2, NULL, NULL, NULL, OLED_Show_Hello_C51 }
};

/*=========================================================
	������
=========================================================*/

void System_Init(void)
{
	My_USART_Init();
	key_Init();
	OLED_Init();
	
	MyTimer_Init();
	
    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_OneLevel[1]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[1]);
	
	EA_OPN();  // �������ж�
}

void main()
{
	System_Init();
	
	while(1)
	{
		;
	}
}









