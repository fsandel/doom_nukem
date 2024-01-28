#include "stdio.h"

#include "player/player.h"

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
  t_player *player = initPlayer();
  if (!player)
    return 1;

  f1();
  f2();
  f3();
  return 0;
}