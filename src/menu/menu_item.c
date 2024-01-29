#include "../window/window_access.h"
#include "menu_struct.h"
#include "../grafics/grafics_utils.h"

void drawMenuElement(t_menu_item item, int y)
{
  t_window *window = getWindow();
  int x = (window->mlx->width - item.texture->width) / 2;
  drawTextureToImage(item.texture, window->menu_layer, x, y);
}

void drawMenuBorder(t_menu *menu)
{
  t_window *window = getWindow();
  for (uint32_t i = 0; i < menu->selected_texture->height; i++)
  {
    for (uint32_t j = 0; j < menu->selected_texture->width; j++)
    {
      if (i < 5 || i > menu->selected_texture->height - 5 || j < 5 || j > menu->selected_texture->width - 5)
        mlx_put_pixel(window->menu_layer_active, 150 + j, i + menu->selected * 40 + 50, 0xff0000ff);
    }
  }
}

// void drawSelected(t_menu *)
// {
//   t_window *window = getWindow();
//   mlx_image_to_window(window->mlx, window->menu_layer_active, 0, 0);
//   mlx_image_to_window(window->mlx, window->menu_layer_active2, 0, 0);
// }
