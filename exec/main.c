/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:32:50 by sleroy            #+#    #+#             */
/*   Updated: 2026/01/11 20:21:24 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"
#include "../include/parsing.h"

void	data_in_graph(t_data *data, t_graph *graph)
{
	graph->tex_path[0] = data->tex_so;
	graph->tex_path[1] = data->tex_no;
	graph->tex_path[2] = data->tex_ea;
	graph->tex_path[3] = data->tex_we;
	graph->map = data->map;
	graph->ceil_color = data->ceil_color;
	graph->floor_color = data->floor_color;
	graph->width = data->map_w;
	graph->height = data->map_h;
	graph->dir = data->dir;
}

int	check_all(t_data *data, char **av)
{
	if (!check_arg(av[1]))
		return (0);
	if (!save_map(av[1], data))
		return (0);
	if (!valid_map(data))
		return (0);
	return (1);
}

int	init_exec(t_data *data, t_graph *graph, t_player *player)
{
	graph->mlx = mlx_init();
	if (!graph->mlx)
		return (write_error("Error\nmlx_init() failed\n"), 0);
	data_in_graph(data, graph);
	init_image(graph);
	init_player(data, graph, player);
	if (!load_all_textures(graph))
		return (destroy_textures(graph), 0);
	graph->win = mlx_new_window(graph->mlx,
			SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!graph->win)
		return (destroy_textures(graph), 0);
	graph->player = player;
	return (1);
}

int	main(int argc, char **av)
{
	t_graph		*graph;
	t_player	*player;
	t_data		data;

	if (argc != 2)
		return (write_error("Error\nMissing map file argument\n"), 1);
	init_data(&data);
	if (!check_all(&data, av))
		return (free_data(&data), 1);
	graph = ft_calloc(1, sizeof(t_graph));
	if (!graph)
		return (write_error("Error calloc graph\n"), 1);
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (write_error("Error calloc player\n"), 1);
	if (!init_exec(&data, graph, player))
		return (exit_game(graph), 1);
	mlx_hook(graph->win, 2, 1L << 0, key_press_hook, graph);
	mlx_hook(graph->win, 3, 1L << 1, key_release_hook, graph);
	mlx_loop_hook(graph->mlx, move_loop, graph);
	mlx_hook(graph->win, 17, 0, exit_game, graph);
	update_direction_vectors(player);
	render_frame(graph);
	mlx_loop(graph->mlx);
	return (0);
}
