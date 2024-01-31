#include "stdio.h"
#include "libft.h"

#include "player/player.h"

#include "./memory/collector.h"
#include "./memory/ft_malloc.h"
#include "./window/window_access.h"
#include "menu/menu.h"
#include "./grafics/draw_forms.h"
#include "./grafics/grafics_utils.h"
#include "MLX42.h"
#include "math.h"
void key_function(mlx_key_data_t keydata, void *)
{
  switch (keydata.key)
  {
  case MLX_KEY_ESCAPE:
    exit(0);
    break;
  // case MLX_KEY_ENTER:
  //   drawMenu(getMainMenu());
  //   break;
  case MLX_KEY_SPACE:
    printf("UP\n");
    break;

  default:
    break;
  }
}

t_vector2_int points[5] = {
    {100, 100},
    {900, 450},
    {1200, 750},
    {300, 900},
    {50, 200},
};

// t_vector2_int points[4] = {
//     {100, 100},
//     {700, 100},
//     {700, 700},
//     {100, 700},
// };

t_vector2_int intersection(t_vector2_int player, t_vector2_int direction, t_vector2_int pillar1, t_vector2_int pillar2)
{
  float x1 = player.x;
  float y1 = player.y;
  float dx1 = direction.x;
  float dy1 = direction.y;

  float x2 = pillar1.x;
  float y2 = pillar1.y;
  float dx2 = pillar2.x - pillar1.x;
  float dy2 = pillar2.y - pillar1.y;

  float denominator = dx1 * dy2 - dy1 * dx2;
  if (denominator == 0)
  {
    // The lines are parallel or coincident
    return (t_vector2_int){-1, -1};
  }

  float t = ((x2 - x1) * dy2 - (y2 - y1) * dx2) / denominator;

  int x = x1 + t * dx1;
  int y = y1 + t * dy1;

  return (t_vector2_int){x, y};
}

t_vector2_int vectorDiff(t_vector2_int start, t_vector2_int end)
{
  return (t_vector2_int){end.x - start.x, end.y - start.y};
}

t_vector2_int vectorSum(t_vector2_int start, t_vector2_int end)
{
  return (t_vector2_int){end.x + start.x, end.y + start.y};
}

void turnVectorByAngle(t_vector2_int *vector, float angle)
{
  float x = vector->x;
  float y = vector->y;
  vector->x = x * cos(angle) - y * sin(angle);
  vector->y = x * sin(angle) + y * cos(angle);
}

void normalizeVector(t_vector2_int *vector)
{
  float length = sqrt(vector->x * vector->x + vector->y * vector->y);
  vector->x /= length;
  vector->y /= length;
}

void turnPlayer(t_vector2_int *vector)
{
  float angle = 0.1;
  printf("angle: %f\n", sin(angle));
  turnVectorByAngle(vector, angle);
  // normalizeVector(vector);
}

void loop_hook(void *)
{
  clearImage(getWindow()->img);

  t_window *window = getWindow();
  for (int i = 0; i < 4; i++)
  {
    drawLine(window->img, points[i], points[i + 1], 0x00FF00FF);
  }
  drawLine(window->img, points[4], points[0], 0x00FF00FF);
  // drawCircle(window->img, (t_vector2_int){300, 300}, 7, 0x00FF00FF);

  t_vector2_int player = (t_vector2_int){300, 300};
  drawCircle(window->img, player, 7, 0xFF0000FF);

  static t_vector2_int direction = (t_vector2_int){20, -50};
  drawLine(window->img, player, vectorSum(player, direction), 0xFF0000FF);
  if (mlx_is_key_down(getWindow()->mlx, MLX_KEY_SPACE))
  {
    turnPlayer(&direction);
  }

  t_vector2_int intersectionPoint = intersection(player, direction, points[0], points[1]);
  printf("intersectionPoint: %d, %d\n", intersectionPoint.x, intersectionPoint.y);
  drawCircle(window->img, intersectionPoint, 7, 0x00FF00FF);
}

int main()
{
  initCollector();
  t_player *player = initPlayer();
  if (!player)
    return (clearCollector(), 1);

  t_window *window = initWindow();
  if (!window)
    return (clearCollector(), 1);
  // activateMainMenu(getMainMenu());
  mlx_loop_hook(window->mlx, &loop_hook, NULL);
  mlx_loop(window->mlx);
  clearCollector();
  return 0;
}