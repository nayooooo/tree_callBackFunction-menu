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
