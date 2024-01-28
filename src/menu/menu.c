#include "menu.h"
#include "menu_item.h"
#include "libft.h"
#include "../window/window_access.h"
#include "MLX42.h"
#include "stdio.h"
#include "../texture/ft_load_png.h"
#include "../memory/ft_malloc.h"

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

void drawTextureToImage(mlx_texture_t *texture, mlx_image_t *image, int x, int y)
{
  for (uint32_t i = 0; i < texture->height; i++)
  {
    for (uint32_t j = 0; j < texture->width; j++)
    {

      mlx_put_pixel(image, x + j, y + i, ((int *)texture->pixels)[i * texture->width + j]);
    }
  }
}

void drawMenuElement(t_menu_item item, int y)
{
  t_window *window = getWindow();
  int x = (window->mlx->width - item.texture->width) / 2;
  // mlx_texture_to_image(item.texture, window->menu_layer);
  drawTextureToImage(item.texture, window->menu_layer, x, y);
  printf("x: %d, y: %d\n", x, y);
  // mlx_image_to_window(window->mlx, img, x, y)
  // mlx_delete_image(window->mlx, img);
}

// void key_function(mlx_key_data_t keydata, void *)
// {
//   switch (keydata.key)
//   {
//   case MLX_KEY_ESCAPE:
//     exit(0);
//     break;
//   // case MLX_KEY_ENTER:
//   //   drawMenu(getMainMenu());
//   //   break;
//   case MLX_KEY_SPACE:
//     printf("UP\n");
//     break;

//   default:
//     break;
//   }
// }

void drawSelected(t_menu *)
{
  t_window *window = getWindow();
  mlx_image_to_window(window->mlx, window->menu_layer_active, 0, 0);
  mlx_image_to_window(window->mlx, window->menu_layer_active2, 0, 0);
}

void drawMenu(t_menu *menu)
{
  t_window *window = getWindow();
  for (int i = 0; i < menu->size; i++)
  {
    drawMenuElement(menu->items[i], i * 40 + 50);
    if (i == menu->selected)
    {
      drawTextureToImage(menu->selected_texture, window->menu_layer_active, 150, 50);
      drawTextureToImage(menu->selected_texture, window->menu_layer_active2, 150, 50);
      // drawTextureToImage(menu->items[2].texture, window->menu_layer_active2, 150, 50);
      printf("Drawing selected texture\n");
      for (uint32_t i = 0; i < menu->selected_texture->height; i++)
      {
        for (uint32_t j = 0; j < menu->selected_texture->width; j++)
        {
          if (i < 10 || i > menu->selected_texture->height - 10 || j < 10 || j > menu->selected_texture->width - 10)
            mlx_put_pixel(window->menu_layer_active, 150 + j, 50 + i, 0xff0000ff);
        }
      }
    }
  }
}

// void activateMainMenu(t_menu *menu)
// {
//   dr
// }