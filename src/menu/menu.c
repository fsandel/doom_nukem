#include "menu.h"
#include "menu_item.h"
#include "libft.h"
#include "../window/window_access.h"
#include "MLX42.h"
#include "stdio.h"
#include "../texture/ft_load_png.h"
#include "../memory/ft_malloc.h"
#include "../grafics/grafics_utils.h"
#include "./menu_item.h"

void testFunction()
{
  printf("Test function\n");
}

t_menu_item generateMenuItem(char *name, void (*action)(), char *texture)
{
  t_menu_item item;

  ft_strlcpy(item.name, name, 20);
  item.action = action;
  item.texture = ft_load_texture(texture);
  if (!item.texture)
    printf("Error loading texture\n");
  return item;
}

t_menu *getMainMenu()
{
  static t_menu *menu = NULL;
  if (menu)
    return menu;
  menu = ft_malloc(sizeof(t_menu), free);
  menu->name = "Main Menu";
  menu->items[0] = generateMenuItem("New Game", testFunction, "src/menu/menu_textures/play.png");
  menu->items[1] = generateMenuItem("Level Editor", testFunction, "src/menu/menu_textures/leveledit.png");
  menu->items[2] = generateMenuItem("Settings", testFunction, "src/menu/menu_textures/settings.png");
  menu->items[3] = generateMenuItem("Exit", testFunction, "src/menu/menu_textures/exit.png");
  menu->size = 4;
  menu->selected = 0;
  menu->selected_texture = ft_load_texture("src/menu/menu_textures/active.png");
  return menu;
}

void menuKeyFunction(mlx_key_data_t keydata, void *param)
{
  t_menu *menu = (t_menu *)param;
  if (keydata.action != MLX_PRESS)
    return;
  switch (keydata.key)
  {
  case MLX_KEY_UP:
    menu->selected = (menu->selected - 1) % menu->size;
    if (menu->selected < 0)
      menu->selected = menu->size - 1;
    drawMenu(menu);
    break;
  case MLX_KEY_DOWN:
    menu->selected = (menu->selected + 1) % menu->size;
    drawMenu(menu);
    break;
  case MLX_KEY_ENTER:
    menu->items[menu->selected].action();
    break;
  case MLX_KEY_ESCAPE:
    exit(0);
    break;
  default:
    break;
  }
}

void drawMenu(t_menu *menu)
{
  printf("Drawing menu\n");
  clearImage(getWindow()->menu_layer);
  clearImage(getWindow()->menu_layer_active);
  for (int element = 0; element < menu->size; element++)
  {
    drawMenuElement(menu->items[element], element * 40 + 50);
    if (element == menu->selected)
      drawMenuBorder(menu);
  }
}

void activateMainMenu(t_menu *menu)
{
  mlx_key_hook(getWindow()->mlx, menuKeyFunction, menu);
  drawMenu(menu);
}