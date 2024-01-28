#ifndef MEMORY_GARBAGE_H
#define MEMORY_GARBAGE_H

typedef struct s_garbage
{
  void *obj;
  void (*freeGarbage)(void *ptr);
} t_garbage;

void freeGarbage(void *garbage);

#endif