#include "stdlib.h"

#include "libft.h"

#include "garbage.h"
#include "collector.h"

static t_collector *storeCollector(t_collector *c)
{
  static t_collector *collector = NULL;

  if (c)
  {
    collector = c;
    collector->list = NULL;
  }

  return collector;
}

t_collector *getCollector(void)
{
  return storeCollector(NULL);
}

void clearCollector(void)
{
  t_collector *collector = getCollector();

  ft_lstclear(&collector->list, freeGarbage);
  free(collector);
}

void initCollector(void)
{
  if (!storeCollector(malloc(sizeof(t_collector))))
  {
    ft_putendl_fd("Fatal: failed to initiate Collector", 2);
    exit(1);
  }
}
