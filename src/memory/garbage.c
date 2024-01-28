#include "stdlib.h"

#include "garbage.h"

void freeGarbage(void *garbage)
{
  t_garbage *gb = (t_garbage *)garbage;
  if (!garbage)
    return;
  gb->freeGarbage(gb->obj);
  free(garbage);
}