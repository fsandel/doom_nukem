#ifndef MENU_MENU_ITEM_H
#define MENU_MENU_ITEM_H

#include "MLX42.h"

typedef struct s_menu_item
{
  char name[30];
  void (*action)(void);
  mlx_texture_t *texture;
} t_menu_item;

#endif // MENU_MENU_ITEM_H