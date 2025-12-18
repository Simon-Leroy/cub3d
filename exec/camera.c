/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:09:16 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction qui recalcule le vecteur direction à partir
de l'angle de vue du joueur
(dir_x, dir_y) = vecteur unitaire de direction
 */
void	update_direction_vectors(t_player *player)
{
	player->dir_x = cos(player->pa);
	player->dir_y = sin(player->pa);
}

/*
Si la touche pour regarder à gauche est pressée, on soustrait
des radians (multiplié par le delta entre deux frames pour garder
une vitesse constante) pour modifier l'angle de vue.
Si l'angle devient négatif, on a fait un tour complet donc on rajoute
2 PI pour revenir au début du cercle.

Le vecteur de direction est recalculé à la fin de la rotation

On soustrait plutôt qu'on ajoute, car le repère de l'écran est inversé
comparé à un repère mathématique normal : axe Y va vers le bas en positif
sur l'écran
 */
int	look_left(t_player *player, float delta)
{
	if (!player->is_looking_left)
		return (0);
	player->pa -= player->rotation_speed * delta;
	if (player->pa < 0)
		player->pa += 2 * PI;
	update_direction_vectors(player);
	return (1);
}

/*
Pareil que pour la rotation de caméra à gauche mais inversé
 */
int	look_right(t_player *player, float delta)
{
	if (!player->is_looking_right)
		return (0);
	player->pa += player->rotation_speed * delta;
	if (player->pa > 2 * PI)
		player->pa -= 2 * PI;
	update_direction_vectors(player);
	return (1);
}

/*
Booléen pour savoir s'il y a eu rotation que ce soit gauche ou
droite et déclencher le rendu d'une frame s'il y a eu rotation
*/
int	handle_rotation(t_player *player, float delta)
{
	int	moved;

	moved = 0;
	moved += look_left(player, delta);
	moved += look_right(player, delta);
	return (moved > 0);
}
