#include "../vectors/vector_int.h"
#include "MLX42.h"
#include "math.h"
#include "stdlib.h"
#include "../ft_put.pixel.h"

void drawCircle(mlx_image_t *img, t_vector2_int position, int radius, int color)
{
  int radius2 = radius * radius;
  for (int y = -radius; y <= radius; y++)
  {
    int y2 = y * y;
    for (int x = -radius; x <= radius; x++)
    {
      if (x * x + y2 <= radius2)
      {
        ft_put_pixel(img, position.x + x, position.y + y, color);
      }
    }
  }
}

void drawSquare(mlx_image_t *img, t_vector2_int position, int size, int color)
{
  for (int y = 0; y < size; y++)
  {
    for (int x = 0; x < size; x++)
    {
      ft_put_pixel(img, position.x + x, position.y + y, color);
    }
  }
}

void drawRectangle(mlx_image_t *img, t_vector2_int position, int width, int height, int color)
{
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      ft_put_pixel(img, position.x + x, position.y + y, color);
    }
  }
}

void drawLine(mlx_image_t *img, t_vector2_int start, t_vector2_int end, int color)
{
  int dx = end.x - start.x;
  int dy = end.y - start.y;
  int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
  float xInc = dx / (float)steps;
  float yInc = dy / (float)steps;
  float x = start.x;
  float y = start.y;
  for (int i = 0; i <= steps; i++)
  {
    ft_put_pixel(img, x, y, color);
    x += xInc;
    y += yInc;
  }
}
