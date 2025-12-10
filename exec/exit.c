#include "cub3d.h"

void	destroy_textures(t_graph *graph)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (graph->tex[i].img)
		{
			mlx_destroy_image(graph->mlx, graph->tex[i].img);
			graph->tex[i].img = NULL;
		}
		i++;
	}
}

void	free_texture_paths(t_graph *graph)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (graph->tex_path[i])
			free(graph->tex_path[i]);
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	exit_game(t_graph *graph)
{
	destroy_textures(graph);
	free_texture_paths(graph);
	free_map(graph->map);
	mlx_destroy_image(graph->mlx, graph->img.img_ptr);
	mlx_destroy_window(graph->mlx, graph->win);
	mlx_destroy_display(graph->mlx);
	free(graph->mlx);
	free(graph->player);
	free(graph);
	exit(0);
}
