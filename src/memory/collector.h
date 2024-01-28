#ifndef MEMORY_COLLECTOR_H
#define MEMORY_COLLECTOR_H

#include "libft.h"

typedef struct s_collector
{
  t_list *list;
} t_collector;

t_collector *getCollector(void);
void initCollector(void);
void clearCollector(void);

#endif // MEMORY_COLLECTOR_H
