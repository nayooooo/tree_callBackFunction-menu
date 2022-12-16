/**
 * @file main.c
 * @encoding UTF-8
 * @author yewan
 * @brief 菜单系统
 * @version 0.1
 * @date 2022-11-30
 *
 */

#include "main.h"

menu_t menu_Start = {  // 开始菜单（开始画面）
    "menu", 0, 0, 0, NULL, NULL, NULL, NULL
};
menu_t menu_OneLevel[] = {  // 一级菜单
    { "hello", 1, 0, 1, NULL, NULL, NULL, NULL },
    { "count", 1, 0, 2, NULL, NULL, NULL, NULL }
};
menu_t menu_TwoLevel[] = {  // 二级菜单
    { "Hello World!", 2, 1, 1, NULL, NULL, NULL, print_Hello },
    { "Hello C!", 2, 1, 2, NULL, NULL, NULL, print_Hello_C }
};

int main()
{
    uint8_t num = 0;
    menu_t* tempMenu = NULL;
    menu_t* menu = &menu_TwoLevel[0];

    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_OneLevel[1]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[1]);
    currentMenu = &menu_Start;
    pointerMenu = &menu_Start;

    printf("==========================================\r\n");
    show_subMenus(currentMenu);
    printf("==========================================\r\n");
    pointerMenu_JumpBack(&menu_Start);
    enter_pointerMenu();
    pointerMenu_JumpBack(&menu_Start);
    pointerMenu_JumpBack(&menu_Start);
    carryOut_event();

    return 0;
}
