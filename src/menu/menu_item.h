#ifndef MENU_MENU_ITEM_H
#define MENU_MENU_ITEM_H

#include "MLX42.h"
#include "menu.h"

#include "menu_struct.h"

void drawMenuElement(t_menu_item item, int y);
void drawMenuBorder(t_menu *menu);

#endif // MENU_MENU_ITEM_H