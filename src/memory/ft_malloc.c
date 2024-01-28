#include "stdlib.h"

#include "libft.h"

#include "garbage.h"
#include "collector.h"

void *ft_malloc(size_t size, void (*freeFunc)(void *))
{
  t_list *collector = getCollector();
  void *ptr = malloc(size);
  if (!ptr)
    return NULL;

  t_garbage *gb = malloc(sizeof(t_garbage));
  gb->obj = ptr;
  gb->freeGarbage = freeFunc;

  ft_lstadd_back(&collector, ft_lstnew(gb));
  return ptr;
}