#ifndef WINDOW_ACCESS_H
#define WINDOW_ACCESS_H

#include "MLX42.h"

typedef struct s_window
{
  mlx_t *mlx;
} t_window;

t_window *getWindow(void);
t_window *initWindow(void);

#endif // WINDOW_ACCESS_H
