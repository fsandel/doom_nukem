
#include "stdlib.h"
#include "stdio.h"

#include "MLX42.h"

#include "../memory/ft_malloc.h"
#include "./window_access.h"

static t_window *storeWindow(t_window *window)
{
  static t_window *storedWindow = NULL;

  if (window != NULL)
    storedWindow = window;

  return storedWindow;
}

t_window *getWindow(void)
{
  return storeWindow(NULL);
}

static void freeWindow(void *w)
{
  t_window *window = (t_window *)w;
  mlx_terminate(window->mlx);
  free(window);
}

t_window *initWindow(void)
{
  t_window *window;

  window = ft_malloc(sizeof(t_window), freeWindow);
  if (!window)
    return NULL;

  window->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "doom-nukem", true);

  window->background_layer = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx_image_to_window(window->mlx, window->background_layer, 0, 0);
  mlx_set_instance_depth(window->background_layer->instances, BACKGROUND_LAYER);

  window->menu_layer = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx_image_to_window(window->mlx, window->menu_layer, 0, 0);
  mlx_set_instance_depth(window->menu_layer->instances, MENU_LAYER);

  window->menu_layer_active = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx_image_to_window(window->mlx, window->menu_layer_active, 0, 0);
  mlx_set_instance_depth(window->menu_layer_active->instances, MENU_LAYER + 1);

  window->img = mlx_new_image(window->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx_image_to_window(window->mlx, window->img, 0, 0);
  mlx_set_instance_depth(window->img->instances, MENU_LAYER + 2);

  storeWindow(window);
  return window;
}