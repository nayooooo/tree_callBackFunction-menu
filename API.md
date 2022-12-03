# 整体描述 #

    project
    |
    ||menu
    ||
    |||menu.c
    |||menu.h
    |||menu_type.h
    |||menu_configMicro.h
    |||menu_link.c
    |||menu_link.h
    ||
    ||user
    ||
    |||menu_event.c
    |||menu_event.h

# 变量类型 #
名称 | 类型
:-: | :-:
menu_t | 单个菜单
menu_t_ptr | 单个菜单的指针（一般用于指向菜单系统的指针）

# API名称、参数、返回值类型及功能 #

名称 | 参数 | 返回值类型 | 功能
:-: | :-: | :-: | :-:
traversal_Menu | menu_t_ptr | void | 遍历菜单系统
find_Menu | menu_t_ptr & menu_t* | menu_t* | 查找指定的菜单
find_parMenu | menu_t_ptr & menu_t* | menu_t* | 查找所指定的菜单的父级菜单
insert_Menu | menu_t_ptr & menu_t* | menu_t_ptr | 向指定的菜单系统中插入一个菜单（插入菜单之前应存在父级菜单）
delete_Menu | menu_t_ptr & menu_t* | menu_t_ptr | 从指定的菜单系统中删除一个菜单
