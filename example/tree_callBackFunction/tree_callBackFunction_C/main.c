/**
 * @file main.c
 * @encoding UTF-8
 * @author yewan
 * @brief �˵�ϵͳ
 * @version 0.1
 * @date 2022-11-30
 *
 */

#include "main.h"

menu_t menu_Start = {  // ��ʼ�˵�����ʼ���棩
    "menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // һ���˵�
    { "hello", 1, 0, 1, NULL, NULL, NULL, NULL },
    { "count", 1, 0, 2, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // �����˵�
    { "Hello World!", 2, 1, 1, NULL, NULL, NULL, print_Hello },
    { "Hello C!", 2, 1, 2, NULL, NULL, NULL, print_Hello_C }
};

int main()
{
    menu_t* tempMenu = NULL;
    menu_t* targetMenu = &menu_Start;

    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_OneLevel[1]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[1]);
    printf("==========================================\r\n");
    traversal_MenuSystem(&menu_Start);
    printf("==========================================\r\n");
    tempMenu = find_nextMenu(&menu_Start, targetMenu);
    if (tempMenu != NULL)
        printf("%d %d %d: %s\r\n", tempMenu->level, tempMenu->parVal, tempMenu->selfVal, tempMenu->name);
    else
        printf("not find it!\r\n");

    return 0;
}
