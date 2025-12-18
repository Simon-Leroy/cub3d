/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:10:05 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour avancer

-On vérifie le booléen de mouvement en avant
-On calcule les distances horizontale et verticale que feraient
le joueur en avançant
-On fait le check des mouvements verticaux et horizontaux et on
modifie la position du joueur en conséquence s'il peut effectuer
les mouvements
-On set moved sur 1 si un mouvement a été fait pour que le rendering
de la frame soit déclenché
*/
int	move_forward(t_graph *graph, t_player *player, float delta)
{
	float	dx;
	float	dy;
	int		moved;

	if (!player->is_moving_forward)
		return (0);
	dx = player->dir_x * player->move_speed * delta;
	dy = player->dir_y * player->move_speed * delta;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

/*
Même système que pour move_forward, juste les signes de dx et dy qui changent
 */
int	move_backward(t_graph *graph, t_player *player, float delta)
{
	float	dx;
	float	dy;
	int		moved;

	if (!player->is_moving_backward)
		return (0);
	dx = -player->dir_x * player->move_speed * delta;
	dy = -player->dir_y * player->move_speed * delta;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

/*
Pareil
*/
int	move_left(t_graph *graph, t_player *player, float delta)
{
	float	dx;
	float	dy;
	int		moved;

	if (!player->is_moving_left)
		return (0);
	dx = player->dir_y * player->move_speed * delta;
	dy = -player->dir_x * player->move_speed * delta;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

/*
Pareil
*/
int	move_right(t_graph *graph, t_player *player, float delta)
{
	float	dx;
	float	dy;
	int		moved;

	if (!player->is_moving_right)
		return (0);
	dx = -player->dir_y * player->move_speed * delta;
	dy = player->dir_x * player->move_speed * delta;
	moved = 0;
	if (check_move_x(graph, player, dx))
	{
		player->px += dx;
		moved = 1;
	}
	if (check_move_y(graph, player, dy))
	{
		player->py += dy;
		moved = 1;
	}
	return (moved);
}

/*
Fonction de centralisation des check des mouvements qui est utilisé
pour savoir s'il faut faire le render et afficher une nouvelle frame
ou non
*/
int	handle_movement(t_graph *graph, t_player *player, float delta)
{
	int	moved;

	moved = 0;
	moved += move_forward(graph, player, delta);
	moved += move_backward(graph, player, delta);
	moved += move_left(graph, player, delta);
	moved += move_right(graph, player, delta);
	return (moved > 0);
}
