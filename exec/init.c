/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:02:23 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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

/*
Fonction pour positionner le joueur sur la carte et le mettre
dans la bonne direction
*/
int	set_player(t_data *data, t_graph *graph, t_player *player)
{
	player->px = data->player_x * IMG_PX + player->radius;
	player->py = data->player_y * IMG_PX + player->radius;
	player->pa = P3 - 0.0001f;
	if (graph->dir == 'N')
		player->pa = P3 - 0.0001f;
	else if (graph->dir == 'S')
		player->pa = P2 - 0.0001f;
	else if (graph->dir == 'E')
		player->pa = 0;
	else if (graph->dir == 'W')
		player->pa = PI - 0.0001f;
	return (1);
}

/*
Initialisation des variables du joueur
*/
int	init_player(t_data *data, t_graph *graph, t_player *player)
{
	if (!graph || !player)
		return (0);
	graph->player = player;
	player->radius = 10;
	player->rotation_speed = ROTATION_SPEED;
	player->move_speed = MOVE_SPEED;
	player->is_looking_left = 0;
	player->is_looking_right = 0;
	player->is_moving_backward = 0;
	player->is_moving_forward = 0;
	player->is_moving_left = 0;
	player->is_moving_right = 0;
	if (!set_player(data, graph, player))
		return (0);
	return (1);
}
