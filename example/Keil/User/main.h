#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "delay.h"

#include "key.h"
#include "oled.h"
#include "screen.h"

#include "MyUART.h"
#include "MyTimer.h"

#include "menu.h"
#include "menu_event.h"

#define EA_OPN()		EA = 1
#define EA_CLS()		EA = 0

#endif /* __MAIN_H */
