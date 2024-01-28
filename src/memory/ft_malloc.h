#ifndef MEMORY_FT_MALLOC_H
#define MEMORY_FT_MALLOC_H

#include "stddef.h"

void *ft_malloc(size_t size, void (*freeFunc)(void *));

#endif //MEMORT_FT_MALLOC_H