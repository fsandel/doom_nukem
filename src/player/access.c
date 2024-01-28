#include "stdlib.h"

#include "../memory/ft_malloc.h"

#include "player.h"

static t_player *storePlayer(t_player *player)
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

static void freePlayer(void *player)
{
  free(player);
}

t_player *initPlayer(void)
{
  t_player *player;

  player = ft_malloc(sizeof(t_player), freePlayer);
  if (!player)
    return NULL;

  storePlayer(player);
  return player;
}