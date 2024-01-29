#ifndef GRAFICS_DRAW_FORMS_H
#define GRAFICS_DRAW_FORMS_H

#include "MLX42.h"
#include "../vectors/vector_int.h"

void drawCircle(mlx_image_t *img, t_vector2_int position, int radius, int color);
void drawSquare(mlx_image_t *img, t_vector2_int position, int size, int color);
void drawRectangle(mlx_image_t *img, t_vector2_int position, int width, int height, int color);
void drawLine(mlx_image_t *img, t_vector2_int start, t_vector2_int end, int color);

#endif //GRAFICS_DRAW_FORMS_H