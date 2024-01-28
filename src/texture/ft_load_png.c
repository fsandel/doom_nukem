#include "MLX42.h"

mlx_texture_t *ft_load_texture(char *path)
{
  return mlx_load_png(path);
}