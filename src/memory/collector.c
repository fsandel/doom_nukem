#include "libft.h"

#include "garbage.h"

t_list *storeCollector(t_list *list)
{
  static t_list *storedList = NULL;

  if (list)
    storedList = list;

  return storedList;
}

t_list *getCollector(void)
{
  return storeCollector(NULL);
}

void clearCollector(void)
{
  t_list *list = getCollector();

  ft_lstclear(&list, freeGarbage);
}

t_list *initCollector(void)
{
  t_list *list = storeCollector(ft_lstnew(NULL));

  if (!list)
  {
    ft_putendl_fd("Fatal: failed to initiate Collector", 2);
    exit(1);
  }

  return list;
}
