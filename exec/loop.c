/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:59:57 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour suivre la position du joueur dans la grille
de la map.
Appelée à chaque boucle de la mlx
 */
void	update_grid_position(t_player *player)
{
	player->grid_x = (int)(player->px / IMG_PX);
	player->grid_y = (int)(player->py / IMG_PX);
}

/*
Fonction pour détecter quand une touche de mouvement,
de caméra, ou d'exit est pressée
*/
int	key_press_hook(int key, t_graph *graph)
{
	t_player	*player;

	player = graph->player;
	if (key == X_ESC)
		exit_game(graph);
	if (key == W_KEY)
		player->is_moving_forward = 1;
	if (key == S_KEY)
		player->is_moving_backward = 1;
	if (key == A_KEY)
		player->is_moving_left = 1;
	if (key == D_KEY)
		player->is_moving_right = 1;
	if (key == X_RIGHT)
		player->is_looking_right = 1;
	if (key == X_LEFT)
		player->is_looking_left = 1;
	return (0);
}

/*
Fonction pour détecter quand une touche de mouvement,
de caméra est relachée
*/
int	key_release_hook(int key, t_graph *graph)
{
	t_player	*player;

	player = graph->player;
	if (key == W_KEY)
		player->is_moving_forward = 0;
	if (key == S_KEY)
		player->is_moving_backward = 0;
	if (key == A_KEY)
		player->is_moving_left = 0;
	if (key == D_KEY)
		player->is_moving_right = 0;
	if (key == X_RIGHT)
		player->is_looking_right = 0;
	if (key == X_LEFT)
		player->is_looking_left = 0;
	return (0);
}

/*
Boucle principale de la mlx

VARIABLES :
-int moved et rotated récupèrent l'info de si une touche de déplacement
ou de rotation a été pressée
-static long last_time récupère le dernier timestamp d'affichage d'une
frame. On utilise static pour que la valeur se conserve entre chaque
itération
-long current_time pour avoir le timestamp de la frame qui va être affichée
-float delta : le delta entre deux frames, exprimé en secondes

CORPS DE LA FONCTION :
On commence par initialiser last_time : une variable static est initialisée
à 0 par défaut, dans la première boucle on lui donne la valeur de current_time,
sinon current_time - last_time = current_time - 0 = très grand nombre, on
return 0 après initialisation donc la première frame est ignorée
Le delta est ensuite calculé normalement

On fixe le delta maximal à 50ms, sinon en cas de machine lente ou de freeze,
on pourrait avoir des effets de téléportation et mauvaise gestion des
collisions

On update ensuite la valeur des coordonnées du joueur dans la grille et on voit
s'il y a eu un mouvement ou une roation -> si oui on render la frame
Donc pas de nouvelle frame s'il n'y a pas de mouvement pour éviter des actions
et calculs inutiles
 */
int	move_loop(t_graph *graph)
{
	int			moved;
	int			rotated;
	static long	last_time;
	long		current_time;
	float		delta;

	current_time = get_time_ms();
	if (last_time == 0)
	{
		last_time = current_time;
		return (0);
	}
	delta = (current_time - last_time) / 1000.0f;
	last_time = current_time;
	if (delta > 0.05f)
		delta = 0.05f;
	update_grid_position(graph->player);
	moved = handle_movement(graph, graph->player, delta);
	rotated = handle_rotation(graph->player, delta);
	if (moved || rotated)
		render_frame(graph);
	return (0);
}
