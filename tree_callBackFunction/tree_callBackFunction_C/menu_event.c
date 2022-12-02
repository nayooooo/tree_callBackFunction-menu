#include "menu_event.h"

menuEventState print_Hello(menu_t* menu)
{
	printf("Hello World!\r\n");

	return MENU_EVENT_OK;
}

menuEventState print_Hello_C(menu_t* menu)
{
	printf("Hello C!\r\n");

	return MENU_EVENT_OK;
}
