#include "stdlib.h"

#include "../memory/ft_malloc.h"

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

  player = ft_malloc(sizeof(t_player), free);
  if (!player)
    return NULL;

  storePlayer(player);
  return player;
}