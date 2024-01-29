#include "stdio.h"
#include "libft.h"

#include "player/player.h"

#include "./memory/collector.h"
#include "./memory/ft_malloc.h"
#include "./window/window_access.h"
#include "menu/menu.h"

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

int main()
{
  initCollector();
  t_player *player = initPlayer();
  if (!player)
    return (clearCollector(), 1);

  t_window *window = initWindow();
  if (!window)
    return (clearCollector(), 1);
  activateMainMenu(getMainMenu());
  mlx_loop(window->mlx);
  clearCollector();
  return 0;
}