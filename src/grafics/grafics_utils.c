#include "grafics_utils.h"
#include "MLX42.h"
#include "../ft_put.pixel.h"

void drawTextureToImage(mlx_texture_t *texture, mlx_image_t *image, int x, int y)
{
  for (uint32_t i = 0; i < texture->height; i++)
  {
    for (uint32_t j = 0; j < texture->width; j++)
    {
      ft_put_pixel(image, x + j, y + i, ((int *)texture->pixels)[i * texture->width + j]);
    }
  }
}

void clearImage(mlx_image_t *image)
{
  ft_bzero(image->pixels, image->width * image->height * 4);
}