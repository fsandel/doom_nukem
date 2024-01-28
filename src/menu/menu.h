#ifndef MENU_MENU_H
#define MENU_MENU_H

#include "menu_item.h"

#define MENU_SIZE 5

typedef struct t_menu
{
  char *name;
  t_menu_item items[MENU_SIZE];
  int size;
  int selected;
  mlx_texture_t *selected_texture;
} t_menu;

void drawMenu(t_menu *menu);
t_menu *getMainMenu();

#endif // MENU_MENU_H