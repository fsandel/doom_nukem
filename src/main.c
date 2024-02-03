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
#include "vectors/vector_int.h"
#include "vectors/vector_float.h"
#include <GLFW/glfw3.h>

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
    {800, 100},
    {800, 500},
    {800, 800},
    {100, 800},
    // {300, 900},
    // {100, 500},
};

t_vector2_int points2[5] = {
    {800, 100},
    {1000, 100},
    {1000, 1000},
    {800, 800},
    {800, 500},

};

// t_vector2_int points[4] = {
//     {100, 100},
//     {700, 100},
//     {700, 700},
//     {100, 700},
// };

typedef enum e_wall_type
{
  WALL,
  DOOR,
} t_wall_type;

typedef struct s_room t_room;

typedef struct s_wall
{
  t_vector2_int pillar[2];
  t_wall_type type;
  t_room *rooms[2];
} t_wall;

typedef struct s_room
{
  t_wall *walls;
  int walls_count;
  int id;
} t_room;

typedef struct s_entity
{
  t_vector2_int pos;
  t_vector2_float direction;
  t_room *room;
} t_entity;

t_vector2_int calculateIntersectionPoint(t_room *room, t_vector2_int player, t_vector2_float direction);

t_vector2_int intersection(t_vector2_int player, t_vector2_float direction, t_vector2_int pillar1, t_vector2_int pillar2)
{
  float x2 = player.x;
  float y2 = player.y;
  float dx2 = direction.x;
  float dy2 = direction.y;

  float x1 = pillar1.x;
  float y1 = pillar1.y;
  float dx1 = pillar2.x - pillar1.x;
  float dy1 = pillar2.y - pillar1.y;

  float denominator = dx1 * dy2 - dy1 * dx2;
  if (denominator == 0)
  {
    return (t_vector2_int){-1, -1};
  }

  float t = ((x2 - x1) * dy2 - (y2 - y1) * dx2) / denominator;
  if (t < 0 || t > 1)
  {
    return (t_vector2_int){-1, -1};
  }
  int x = x1 + t * dx1;
  int y = y1 + t * dy1;

  return (t_vector2_int){x, y};
}

int getSign(float x)
{
  return (x > 0) - (x < 0);
}

bool isValidIntersection(t_vector2_int intersectionPoint, t_vector2_int pos, t_vector2_float dir)
{
  if (intersectionPoint.x == -1)
    return false;

  if (dir.x >= 0 && dir.y >= 0)
  {
    if (intersectionPoint.x < pos.x || intersectionPoint.y < pos.y)
      return false;
  }
  else if (dir.x >= 0 && dir.y < 0)
  {
    if (intersectionPoint.x < pos.x || intersectionPoint.y > pos.y)
      return false;
  }
  else if (dir.x < 0 && dir.y >= 0)
  {
    if (intersectionPoint.x > pos.x || intersectionPoint.y < pos.y)
      return false;
  }
  else if (dir.x < 0 && dir.y < 0)
  {
    if (intersectionPoint.x > pos.x || intersectionPoint.y > pos.y)
      return false;
  }
  return true;
}

t_vector2_int vectorDiff(t_vector2_int start, t_vector2_int end)
{
  return (t_vector2_int){end.x - start.x, end.y - start.y};
}

t_vector2_int vectorSum(t_vector2_int start, t_vector2_int end)
{
  return (t_vector2_int){end.x + start.x, end.y + start.y};
}

void turnPlayer(t_vector2_float *vector, float angle)
{
  turnVectorByAngleFloat(vector, angle);
  normalizeVectorFloat(vector);
}

float distance(t_vector2_int a, t_vector2_int b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void movePlayer(t_entity *player, t_vector2_float direction)
{
  t_vector2_int nextPos = vectorSum(player->pos, (t_vector2_int){direction.x * 10, direction.y * 10});
  int collissionBox = distance(player->pos, nextPos);

  t_vector2_int intersectionPoint = (t_vector2_int){-1, -1};
  t_room *room = player->room;

  for (int i = 0; i < room[0].walls_count; i++)
  {
    intersectionPoint = intersection(player->pos, direction, room[0].walls[i].pillar[0], room[0].walls[i].pillar[1]);
    if (intersectionPoint.x != -1 && isValidIntersection(intersectionPoint, player->pos, direction))
    {
      if (distance(player->pos, intersectionPoint) > collissionBox)
      {
        player->pos = nextPos;
      }
      else
      {
        if (room[0].walls[i].type == DOOR)
        {
          t_room *nextRoom = room[0].walls[i].rooms[1] == &(room[0]) ? room[0].walls[i].rooms[0] : room[0].walls[i].rooms[1];
          player->room = nextRoom;
          player->pos = nextPos;
        }
      }
      break;
    }
  }
}

void drawRoom(t_room room)
{
  for (int i = 0; i < room.walls_count; i++)
  {
    if (room.walls[i].type == WALL)
      drawLine(getWindow()->background_layer, room.walls[i].pillar[0], room.walls[i].pillar[1], 0xFF0000FF);
    else // if (room.walls[i].type == DOOR)
      drawLine(getWindow()->background_layer, room.walls[i].pillar[0], room.walls[i].pillar[1], 0x00FF00FF);
  }
}

void drawRooms(t_room *rooms)
{
  // int count = 2;
  // for (int i = 0; i < count; i++)
  // {
  //   drawRoom(rooms[i]);
  // }
  drawRoom(rooms[1]);
  drawRoom(rooms[0]);
}

void handlePlayerMovement(t_entity *player)
{
  mlx_t *mlx = getWindow()->mlx;

  if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
  {
    turnPlayer(&(player->direction), 0.1);
  }
  else if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
  {
    turnPlayer(&(player->direction), -0.1);
  }

  if (mlx_is_key_down(mlx, MLX_KEY_UP))
  {
    movePlayer(player, player->direction);
  }
  else if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
  {
    movePlayer(player, (t_vector2_float){-player->direction.x, -player->direction.y});
  }
}

t_room *createRooms()
{
  t_room *room = malloc(sizeof(t_room) * 2);
  if (!room)
    return NULL;

  room[0].walls_count = 5;
  room[0].id = 0;
  room[0].walls = malloc(sizeof(t_wall) * room[0].walls_count);
  if (!room[0].walls)
    return NULL;

  for (int i = 0; i < room[0].walls_count; i++)
  {
    room[0].walls[i].pillar[0] = points[i];
    room[0].walls[i].pillar[1] = points[(i + 1) % room[0].walls_count];
    room[0].walls[i].type = WALL;
  }
  room[0].walls[1].type = DOOR;
  room[0].walls[1].rooms[0] = &(room[0]);
  room[0].walls[1].rooms[1] = &(room[1]);

  room[1].walls_count = 5;
  room[1].id = 1;
  room[1].walls = malloc(sizeof(t_wall) * room[1].walls_count);
  if (!room[1].walls)
    return NULL;

  for (int i = 0; i < room[1].walls_count; i++)
  {
    room[1].walls[i].pillar[0] = points2[i];
    room[1].walls[i].pillar[1] = points2[(i + 1) % room[1].walls_count];
    room[1].walls[i].type = WALL;
  }
  room[1].walls[4].type = DOOR;
  room[1].walls[4].rooms[0] = &(room[1]);
  room[1].walls[4].rooms[1] = &(room[0]);

  return room;
}

t_vector2_int calculateIntersectionPoint(t_room *room, t_vector2_int player, t_vector2_float direction)
{
  t_vector2_int intersectionPoint = (t_vector2_int){-1, -1};
  for (int i = 0; i < room->walls_count; i++)
  {
    intersectionPoint = intersection(player, direction, room->walls[i].pillar[0], room->walls[i].pillar[1]);
    if (intersectionPoint.x != -1 && isValidIntersection(intersectionPoint, player, direction))
    {
      if (room->walls[i].type == DOOR)
      {
        t_room *nextRoom = room->walls[i].rooms[1] == room ? room->walls[i].rooms[0] : room->walls[i].rooms[1];
        intersectionPoint = calculateIntersectionPoint(nextRoom, (t_vector2_int){intersectionPoint.x + direction.x * 10, intersectionPoint.y + direction.y * 10}, direction);
      }
      break;
    }
  }

  return intersectionPoint;
}

typedef struct s_game
{
  t_entity *player;
  t_room *rooms;
} t_game;

void loop_hook(void *ptr)
{
  t_game *game = (t_game *)ptr;
  t_entity *player = game->player;

  clearImage(getWindow()->img);

  t_window *window = getWindow();

  // static t_vector2_int player = (t_vector2_int){300, 300};
  drawCircle(window->img, player->pos, 7, 0xFF0000FF);

  // static t_vector2_float direction = (t_vector2_float){0, -1};
  drawLine(window->img, player->pos, vectorSum(player->pos, (t_vector2_int){player->direction.x * 100, player->direction.y * 100}), 0xFF0000FF);

  handlePlayerMovement(player);

  int sidePoints = 100;
  float maxAngle = 0.5;
  float angle = maxAngle / sidePoints;
  for (int i = -sidePoints; i <= sidePoints; i++)
  {
    t_vector2_float directionLocal = player->direction;
    turnVectorByAngleFloat(&directionLocal, i * angle);
    t_vector2_int intersectionPoint = calculateIntersectionPoint(player->room, player->pos, directionLocal);
    if (intersectionPoint.x != -1 && isValidIntersection(intersectionPoint, player->pos, directionLocal))
    {
      drawCircle(window->img, intersectionPoint, 7, 0x00FF00FF);
    }
  }
  // t_vector2_int intersectionPoint = calculateIntersectionPoint(room, player, direction);
  // drawCircle(window->img, intersectionPoint, 7, 0x00FF00FF);
}

void titleFPS(void *)
{
  mlx_t *mlx = getWindow()->mlx;
  static char *title = NULL;
  title = ft_itoa(1 / mlx->delta_time);
  glfwSetWindowTitle(mlx->window, title);
  free(title);
}

void keyFunctionQuit(mlx_key_data_t keydata, void *)
{
  if (keydata.key == MLX_KEY_ESCAPE)
  {
    exit(0);
  }
}

t_game *createGame()
{
  t_game *game = malloc(sizeof(t_game));
  if (!game)
    return NULL;

  game->rooms = createRooms();
  if (!game->rooms)
    return NULL;

  game->player = malloc(sizeof(t_entity));
  if (!game->player)
    return NULL;

  game->player->pos = (t_vector2_int){300, 300};
  game->player->direction = (t_vector2_float){0, -1};
  game->player->room = &(game->rooms[0]);

  return game;
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
  t_game *game = createGame();
  drawRooms(game->rooms);
  mlx_loop_hook(window->mlx, &loop_hook, game);
  mlx_loop_hook(window->mlx, &titleFPS, NULL);
  mlx_key_hook(window->mlx, &key_function, NULL);
  mlx_loop(window->mlx);
  clearCollector();
  return 0;
}