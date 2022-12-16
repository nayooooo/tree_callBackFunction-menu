#include "menu_event.h"

#include <stdio.h>

menuEventState print_Hello(void)
{
	printf("Hello World!\r\n");

	return MENU_EVENT_OK;
}

menuEventState print_Hello_C(void)
{
	printf("Hello C!\r\n");

	return MENU_EVENT_OK;
}
