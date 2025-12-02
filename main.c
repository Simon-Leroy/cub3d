#include "cub3d.h"

void	display_minimap(t_graph *graph)
{
	int	x;
	int	y;

	y = 0;
	while (graph->map[y])
	{
		x = 0;
		while (graph->map[y][x])
		{
			if (graph->map[y][x] == '1')
				mlx_put_image_to_window(graph->mlx, graph->win, graph->wall, x * IMG_PX, y * IMG_PX);
			x++;
		}
		y++;
	}
}

void	move(int direction, t_graph *graph)
{
	if (direction == W_KEY)
		graph->y -= 5;
	if (direction == S_KEY)
		graph->y += 5;
	if (direction == A_KEY)
		graph->x -= 5;
	if (direction == D_KEY)
		graph->x += 5;
}

int	key_press_hook(int key, t_graph *graph)
{
	if (key == W_KEY)
		graph->is_moving_forward = 1;
	if (key == S_KEY)
		graph->is_moving_backward = 1;
	if (key == A_KEY)
		graph->is_moving_left = 1;
	if (key == D_KEY)
		graph->is_moving_right = 1;
	return (0);
}

int	key_release_hook(int key, t_graph *graph)
{
	if (key == W_KEY)
		graph->is_moving_forward = 0;
	if (key == S_KEY)
		graph->is_moving_backward = 0;
	if (key == A_KEY)
		graph->is_moving_left = 0;
	if (key == D_KEY)
		graph->is_moving_right = 0;
	return (0);
}

int	move_loop(t_graph *graph)
{
	int	moved = 0;

	if (graph->is_moving_forward)
	{
		graph->y -= 1;
		moved = 1;
	}
	if (graph->is_moving_backward)
	{
		graph->y += 1;
		moved = 1;
	}
	if (graph->is_moving_left)
	{
		graph->x -= 1;
		moved = 1;
	}
	if (graph->is_moving_right)
	{
		graph->x += 1;
		moved = 1;
	}
	if (moved)
	{
		mlx_clear_window(graph->mlx, graph->win);
		display_minimap(graph);
		mlx_put_image_to_window(graph->mlx, graph->win, graph->square, graph->x, graph->y);
	}
	return (0);
}

int key_hook(int key, t_graph *graph)
{
	move(key, graph);
	mlx_clear_window(graph->mlx, graph->win);
	display_minimap(graph);
	mlx_put_image_to_window(graph->mlx, graph->win, graph->square, graph->x, graph->y);
	return (0);
}

int main()
{
	t_graph	*graph;
	int		size;

	size = 32;
	graph = malloc(sizeof(t_graph));
	if (!graph)
		return (1);
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, 15 * IMG_PX, 8 * IMG_PX, "CUB3D");
	graph->square = mlx_xpm_file_to_image(graph->mlx, "assets/square.xpm", &size, &size);
	graph->wall = mlx_xpm_file_to_image(graph->mlx, "assets/walls.xpm", &size, &size);
	graph->map = create_map_grid("map.cub");
	mlx_hook(graph->win, 2, 1L<<0, key_press_hook, graph);
	mlx_hook(graph->win, 3, 1L<<1, key_release_hook, graph);
	mlx_loop_hook(graph->mlx, move_loop, graph);
	mlx_hook(graph->win, 17, 0, exit_game, graph);
	mlx_loop(graph->mlx);

	return 0;
}

/* int main()
{
	char *map_name = "map.cub";
	char **map;

	map = create_map_grid(map_name);
	int i = 0;
	int j;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
	}
} */
