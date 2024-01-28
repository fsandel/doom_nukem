
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

  window->mlx = mlx_init(400, 400, "doom-nukem", true);
  storeWindow(window);
  return window;
}