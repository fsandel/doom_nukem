#ifndef WINDOW_ACCESS_H
#define WINDOW_ACCESS_H

#include "MLX42.h"

#define MENU_LAYER 1
typedef struct s_window
{
  mlx_t *mlx;
  mlx_image_t *menu_layer;
  mlx_image_t *menu_layer_active;
  mlx_image_t *img;
} t_window;

t_window *getWindow(void);
t_window *initWindow(void);

#endif // WINDOW_ACCESS_H
