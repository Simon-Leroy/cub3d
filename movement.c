#include "cub3d.h"

int	move_forward(t_graph *graph)
{
	if (!graph->is_moving_forward)
		return (0);
	if (!check_move_up(graph, graph->move_speed))
		return (0);
	graph->y -= graph->move_speed;
	return (1);
}

int	move_backward(t_graph *graph)
{
	if (!graph->is_moving_backward)
		return (0);
	if (!check_move_down(graph, graph->move_speed))
		return (0);
	graph->y += graph->move_speed;
	return (1);
}

int	move_left(t_graph *graph)
{
	if (!graph->is_moving_left)
		return (0);
	if (!check_move_left(graph, graph->move_speed))
		return (0);
	graph->x -= graph->move_speed;
	return (1);
}

int	move_right(t_graph *graph)
{
	if (!graph->is_moving_right)
		return (0);
	if (!check_move_right(graph, graph->move_speed))
		return (0);
	graph->x += graph->move_speed;
	return (1);
}

int	handle_movement(t_graph *graph)
{
	int moved;

	moved = 0;
	moved += move_forward(graph);
	moved += move_backward(graph);
	moved += move_left(graph);
	moved += move_right(graph);
	return (moved > 0);
}
