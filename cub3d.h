#ifndef CUB3D_H
#define CUB3D_H


#include "minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_cell
{
	int		x;
	int		y;
	char	type;
}	t_cell;

typedef struct graph
{
	void	*mlx;
	void	*win;
}	t_graph;

#endif
