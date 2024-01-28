#include "stdio.h"
#include "libft.h"

#include "player/player.h"

#include "./memory/collector.h"
#include "./memory/ft_malloc.h"

void f1()
{
  t_player *player = getPlayer();

  player->nb = 1;
}

void f2()
{
  t_player *player = getPlayer();

  player->nb = 2;
}

void f3()
{
  t_player *player = getPlayer();

  printf("nb: %d\n", player->nb);
}

int main()
{
  initCollector();
  t_player *player = initPlayer();
  if (!player)
    return 1;
  char *test = ft_malloc(1, free);
  (void)test;
  clearCollector();
  return 0;
}