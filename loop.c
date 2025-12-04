#include "cub3d.h"

void	update_grid_position(t_graph *graph)
{
	graph->grid_x = (int)(graph->x / IMG_PX);
	graph->grid_y = (int)(graph->y / IMG_PX);
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
	if (key == X_RIGHT)
		graph->is_looking_right = 1;
	if (key == X_LEFT)
		graph->is_looking_left = 1;
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
	if (key == X_RIGHT)
		graph->is_looking_right = 0;
	if (key == X_LEFT)
		graph->is_looking_left = 0;
	return (0);
}

int	move_loop(t_graph *graph)
{
	int	moved;
	int	rotated;
	update_grid_position(graph);
	moved = handle_movement(graph);
	rotated = handle_rotation(graph);
	if (moved || rotated)
		redraw_display(graph);
/* 	{
		mlx_clear_window(graph->mlx, graph->win);
		display_minimap(graph);
		mlx_put_image_to_window(graph->mlx, graph->win, graph->square, graph->x - graph->player_radius, graph->y - graph->player_radius);
		draw_line(graph->mlx, graph->win, graph->x, graph->y, graph->x + graph->pdx, graph->y + graph->pdy, 0xFF0000);
	} */
	return (0);
}


