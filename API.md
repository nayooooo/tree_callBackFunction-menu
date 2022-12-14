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

# 重要变量说明 #

名称 | 类型 | 模块中的位置 | 作用 | 说明
:-: | :-: | :-: | :-: |:-:
currentMenu | menu_t* | menu.c | 指向当前页面所在的父级菜单 | 需要在使用menu.c中的API之前将其初始化为合适的值
pointerMenu | menu_t* | menu.c | 指向当前选中的菜单 | 需要在使用menu.c中的API之前将其初始化为合适的值

# API名称、参数、返回值类型及功能 #

menu_link

名称 | 参数 | 返回值类型 | 功能 | 说明
:-: | :-: | :-: | :-: | :-:
traversal_MenuSystem | menu_t_ptr | void | 遍历菜单系统 | -
traversal_subMenus | menu_t* | void | 搜索父级菜单下一级的子级菜单 | -
show_subMenus_nextLevel | menu_t* | menu_t* | 向交互界面显示父级菜单下的子级菜单 | -
find_Menu | menu_t_ptr & menu_t* | menu_t* | 查找指定的菜单 | -
find_parMenu | menu_t_ptr & menu_t* | menu_t* | 查找所指定的菜单的父级菜单 | -
find_prevMenu | menu_t_ptr & menu_t* | menu_t* | 查找同一父级菜单下的同一等级菜单中，所给menu_t*的前一个菜单 | -
find_nextMenu | menu_t_ptr & menu_t* | menu_t* | 查找同一父级菜单下的同一等级菜单中，所给menu_t*的后一个菜单 | -
count_CurrentMenu_NextLevelMenu_Num | menu_t_ptr | uint8_t | 计算同一级菜单相同父级菜单的子级菜单数 | -
count_SameLevel_PrevMenu_Num | menu_t* | uint8_t | 计算同一级菜单相同父级菜单下，[menu_t*]前方的菜单数 | -
insert_Menu | menu_t_ptr & menu_t* | menu_t_ptr | 向指定的菜单系统中插入一个菜单（插入菜单之前应存在父级菜单） | -
delete_Menu | menu_t_ptr & menu_t* | menu_t_ptr | 从指定的菜单系统中删除一个菜单 | -

menu at C51

名称 | 参数 | 返回值类型 | 功能 | 说明
:-: | :-: | :-: | :-: | :-:
screen_Show_subMenus | menu_t* | menu_t* | 将一个菜单的下一级菜单显示到屏幕上 | 使用前应先初始化屏幕及屏幕参数
screen_Show_PointerMenu | void | menu_t* | 在屏幕中突出显示当前选中的菜单 | 使用前应先初始化屏幕及屏幕参数
pointerMenu_JumpForward | menu_t_ptr | menu_t* | 选中前一个菜单 | 使用前应先初始化屏幕及屏幕参数
pointerMenu_JumpBack | menu_t_ptr | menu_t* | 选中后一个菜单 | 使用前应先初始化屏幕及屏幕参数
enter_pointerMenu | void | menu_t* | 进入选中的菜单 | -
back_SafeMenu | menu_t_ptr | menu_t* | 返回到安全的菜单，前提是 currentMenu 处在不安全的菜单 | 不安全的菜单指的是 [menu->nextLevel == NULL]
carryOut_event | void | menu_t* | 执行选中的菜单的任务 | -
