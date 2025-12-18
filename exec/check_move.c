/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:53:08 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour checker si le mouvement horizontal est possible ou non

next_x est la prochaine coordonnée x du joueur
map_x_left = colonne où se trouve le bord gauche du joueur
map_x_right = colonne où se trouve le bord droit du joueur
map_y_top = ligne où se trouve le bord supérieur du joueur
map_y_bottom = ligne où se trouve le bord inférieur du joueur

On teste chacune des cases et on renvoie 0 si l'une d'elles
est un mur, 1 si le prochain mouvement horizontal est valide
Principe de Axis Aligned Bounding Box (AABB)

On dissocie le mouvement horizontal du mouvement vertical pour
pouvoir gérer les glissements sur un mur (et pas se stopper net
quand on avance face à un mur avec un angle de biais)
 */
int	check_move_x(t_graph *graph, t_player *player, float dx)
{
	float	next_x;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_x = player->px + dx;
	map_x_left = (int)((next_x - player->radius) / IMG_PX);
	map_x_right = (int)((next_x + player->radius) / IMG_PX);
	map_y_top = (int)((player->py - player->radius) / IMG_PX);
	map_y_bottom = (int)((player->py + player->radius) / IMG_PX);
	if (graph->map[map_y_top][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_top][map_x_right] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_right] == '1')
		return (0);
	return (1);
}

/*
Pareil que pour check_move_x mais avec le mouvement vertical
*/
int	check_move_y(t_graph *graph, t_player *player, float dy)
{
	float	next_y;
	int		map_x_left;
	int		map_x_right;
	int		map_y_top;
	int		map_y_bottom;

	next_y = player->py + dy;
	map_x_left = (int)((player->px - player->radius) / IMG_PX);
	map_x_right = (int)((player->px + player->radius) / IMG_PX);
	map_y_top = (int)((next_y - player->radius) / IMG_PX);
	map_y_bottom = (int)((next_y + player->radius) / IMG_PX);
	if (graph->map[map_y_top][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_left] == '1')
		return (0);
	if (graph->map[map_y_top][map_x_right] == '1')
		return (0);
	if (graph->map[map_y_bottom][map_x_right] == '1')
		return (0);
	return (1);
}
