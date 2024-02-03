#include "MLX42.h"

void ft_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
  if (x < img->width && y < img->height)
    mlx_put_pixel(img, x, y, color);
}