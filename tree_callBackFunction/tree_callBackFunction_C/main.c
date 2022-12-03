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
    menu_t* q = NULL;
    menu_t menu_Temp = {
        .level = 2,
        .parVal = 1,
        .selfVal = 1
    };

    insert_Menu(&menu_Start, &menu_OneLevel[0]);
    insert_Menu(&menu_Start, &menu_OneLevel[1]);
    insert_Menu(&menu_Start, &menu_TwoLevel[0]);
    insert_Menu(&menu_Start, &menu_TwoLevel[1]);
    printf("==========================================\r\n");
    traversal_Menu(&menu_Start);
    printf("==========================================\r\n");
    q = find_parMenu(&menu_Start, &menu_Temp);
    if (q != NULL) {
        printf("%d %d %d name: %s\r\n", q->level, q->parVal, q->selfVal, q->name);
        if(q->eventCB != NULL) q->eventCB(q);
    }
    else printf("not find!\a\r\n");
    delete_Menu(&menu_Start, &menu_Temp);
    printf("==========================================\r\n");
    traversal_Menu(&menu_Start);
    printf("==========================================\r\n");

    return 0;
}
