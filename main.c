#include "cub3d.h"


int main()
{
	t_graph	*graph;

	graph = malloc(sizeof(t_graph));
	if (!graph)
		return (1);
	graph->mlx = mlx_init();
	graph->win = mlx_new_window(graph->mlx, 280, 280, "CUB3D");
	mlx_loop(graph->mlx);

	return 0;
}
