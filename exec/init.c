#include "cub3d.h"

int	is_cardinal(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	get_player_position(t_graph *graph, t_player *player)
{
	int	i;
	int	j;

	j = 0;
	while (graph->map[j])
	{
		i = 0;
		while (graph->map[j][i])
		{
			if (is_cardinal(graph->map[j][i]))
			{
				player->grid_x = i;
				player->grid_y = j;
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

int	set_player(t_graph *graph, t_player *player)
{
	if (get_player_position(graph, player))
	{
		player->px = player->grid_x * IMG_PX + player->radius;
		player->py = player->grid_y * IMG_PX + player->radius;
		if (graph->map[player->grid_y][player->grid_x] == 'N')
			player->pa = P3 - 0.0001f;
		else if (graph->map[player->grid_y][player->grid_x] == 'S')
			player->pa = P2 - 0.0001f;
		else if (graph->map[player->grid_y][player->grid_x] == 'E')
			player->pa = 0;
		else if (graph->map[player->grid_y][player->grid_x] == 'W')
			player->pa = PI - 0.0001f;
		return (1);
	}
	return (0);
}
