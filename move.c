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

/*
Fonction utilisée pour le mlx_hook_loop

int moved -> indique si le joueur est en mouvement et s'il faut réactualiser les différents affichages
double move_speed -> le nombre de pixels ajoutés ou déduits de la position du joueur pour le faire bouger
sur la map
calculate_grid_position -> indique les coordonnées de la case où se trouve le joueur (dans la grille, pas en pixels)

On checke les différents mouvements en fonction de la touche qui est pressée
Les fonctions check_move_up/down/etc servent à repérer les murs et empêcher le joueur d'avancer en cas de collision

Pour la gestion de la caméra, pa correspond à l'angle du joueur en radians
-a 0 (radians), le joueur regarde à droite (vecteur de vision parallèle à l'axe des x)
-a pi, le joueur regarde à gauche
-a pi / 2, le joueur regarde tout en haut,
-a 3 pi / 2, le joueur regarde tout en bas
(voir cercle trigonométrique)
Si le joueur regarde vers la droite, on soustrait à l'angle, sinon on ajoute (cf le cercle trigo)
 */




int	move_loop(t_graph *graph)
{
	int	moved;
	int	rotated;
	update_grid_position(graph);
	moved = handle_movement(graph);
	rotated = handle_rotation(graph);
	if (moved || rotated)
	{
		mlx_clear_window(graph->mlx, graph->win);
		display_minimap(graph);
		mlx_put_image_to_window(graph->mlx, graph->win, graph->square, graph->x - graph->player_radius, graph->y - graph->player_radius);
		draw_line(graph->mlx, graph->win, graph->x, graph->y, graph->x + graph->pdx, graph->y + graph->pdy, 0xFF0000);
	}
	return (0);
}


