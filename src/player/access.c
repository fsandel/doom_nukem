#include "stdlib.h"

#include "player.h"

t_player *storePlayer(t_player *player)
{
  static t_player *storedPlayer = NULL;

  if (player != NULL)
    storedPlayer = player;

  return storedPlayer;
}

t_player *getPlayer(void)
{
  return storePlayer(NULL);
}

t_player *initPlayer(void)
{
  t_player *player;

  player = malloc(sizeof(t_player));
  if (!player)
    return NULL;

  storePlayer(player);
  return player;
}