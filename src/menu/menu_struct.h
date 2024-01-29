#ifndef MENU_MENU_STRUCT_H
#define MENU_MENU_STRUCT_H

#define MENU_SIZE 5

#include "MLX42.h"

typedef struct s_menu_item
{
  char name[30];
  void (*action)(void);
  mlx_texture_t *texture;
} t_menu_item;


typedef struct t_menu
{
  char *name;
  t_menu_item items[MENU_SIZE];
  int size;
  int selected;
  mlx_texture_t *selected_texture;
} t_menu;



#endif // MENU_MENU_STRUCT_H
