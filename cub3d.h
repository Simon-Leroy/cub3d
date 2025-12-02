#ifndef CUB3D_H
#define CUB3D_H


# include "minilibx/mlx.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100

# define IMG_PX 32

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
	void	*square;
	void	*wall;
	size_t	height;
	size_t	width;
	char	**map;
	int		x;
	int		y;
	int	is_moving_forward;
	int	is_moving_backward;
	int	is_moving_left;
	int	is_moving_right;
}	t_graph;

int	exit_game(t_graph *graph);
char	**create_map_grid(char *map_name);

#endif
