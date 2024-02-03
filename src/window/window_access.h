#ifndef WINDOW_ACCESS_H
#define WINDOW_ACCESS_H

#include "MLX42.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1200

typedef enum e_img_layer
{
  BACKGROUND_LAYER,
  IMG_LAYER,

  MENU_LAYER,
  MENU_LAYER_ACTIVE,

} t_img_layer;

typedef struct s_window
{
  mlx_t *mlx;
  mlx_image_t *background_layer;
  mlx_image_t *img;
  mlx_image_t *menu_layer;
  mlx_image_t *menu_layer_active;
} t_window;

t_window *getWindow(void);
t_window *initWindow(void);

#endif // WINDOW_ACCESS_H
