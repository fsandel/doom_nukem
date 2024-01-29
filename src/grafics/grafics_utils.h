#ifndef GRAFICS_GRAFICS_UTILS_H
#define GRAFICS_GRAFICS_UTILS_H

#include "MLX42.h"
#include "libft.h"

void drawTextureToImage(mlx_texture_t *texture, mlx_image_t *image, int x, int y);
void clearImage(mlx_image_t *image);

#endif // GRAFICS_GRAFICS_UTILS_H
