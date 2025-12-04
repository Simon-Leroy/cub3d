#include "cub3d.h"

int check_move_left(t_graph *graph, double move_speed)
{
	int		next_left_cell;
	int		next_left_top_cell;
	int		next_left_bottom_cell;
	double	next_x;

	next_x = graph->x - move_speed;
	next_left_cell = (int)((next_x - graph->player_radius) / IMG_PX);
	next_left_top_cell = (int)((graph->y - graph->player_radius) / IMG_PX);
	next_left_bottom_cell = (int)((graph->y + graph->player_radius) / IMG_PX);
	if (graph->map[next_left_top_cell][next_left_cell] == '1')
			return (0);
	if (graph->map[next_left_bottom_cell][next_left_cell] == '1')
			return (0);
	return (1);
}

int check_move_right(t_graph *graph, double move_speed)
{
	int		next_right_cell;
	int		next_right_top_cell;
	int		next_right_bottom_cell;
	double	next_x;

	next_x = graph->x + move_speed;
	next_right_cell = (int)((next_x + graph->player_radius)/ IMG_PX);
	next_right_top_cell = (int)((graph->y - graph->player_radius) / IMG_PX);
	next_right_bottom_cell = (int)((graph->y + graph->player_radius) / IMG_PX);
	if (graph->map[next_right_top_cell][next_right_cell] == '1')
		return (0);
	if (graph->map[next_right_bottom_cell][next_right_cell] == '1')
		return (0);
	return (1);
}

int check_move_up(t_graph *graph, double move_speed)
{
	int		next_up_cell;
	int		next_up_right_cell;
	int		next_up_left_cell;
	double	next_y;

	next_y = graph->y - move_speed;
	next_up_cell = (int)((next_y - graph->player_radius) / IMG_PX);
	next_up_right_cell = (int)((graph->x + graph->player_radius) / IMG_PX);
	next_up_left_cell = (int)((graph->x - graph->player_radius) / IMG_PX);
	if (graph->map[next_up_cell][next_up_right_cell] == '1')
			return (0);
	if (graph->map[next_up_cell][next_up_left_cell] == '1')
			return (0);
	return (1);
}

int check_move_down(t_graph *graph, double move_speed)
{
	int		next_down_cell;
	int		next_down_right_cell;
	int		next_down_left_cell;
	double	next_y;

	next_y = graph->y + move_speed;
	next_down_cell = (int)((next_y + graph->player_radius) / IMG_PX);
	next_down_left_cell = (int)((graph->x - graph->player_radius) / IMG_PX);
	next_down_right_cell = (int)((graph->x + graph->player_radius) / IMG_PX);
	if (graph->map[next_down_cell][next_down_right_cell] == '1')
			return (0);
	if (graph->map[next_down_cell][next_down_left_cell] == '1')
			return (0);
	return (1);
}
