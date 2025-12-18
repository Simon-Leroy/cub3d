/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_impact.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:56:22 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	apply_fish_eye_correction(t_player *player, t_ray *ray, float *dist)
{
	float	ca;

	ca = normalise_angle(player->pa - ray->ra);
	*dist *= cos(ca);
}

/*
Fonction appelée lorsque le mur le plus proche a été trouvé par la
routine horizontale.

1) Enregistre la distance horizontale (ray->dist_h) comme
distance finale (*dist).
2) Enregistre les coordonnées d'impact horizontales (ray->hx, ray->hy) comme
point de collision final (ray->hit_x, ray->hit_y).
3) Définit le type de collision à Horizontal (ray->side = 0).
4) Détermine la face cardinale touchée ('N' ou 'S') en fonction
de l'angle du rayon :
	-'N' si le rayon pointe vers le haut (angle entre 0 et PI)
	-'S' si le rayon pointe vers le bas (angle entre PI et 2*PI)
*/
void	handle_horizontal_hit(t_ray *ray, float *dist)
{
	*dist = ray->dist_h;
	ray->hit_x = ray->hx;
	ray->hit_y = ray->hy;
	ray->side = 0;
	if (ray->ra > 0 && ray->ra < PI)
		ray->wall_cardinal = 'N';
	else
		ray->wall_cardinal = 'S';
}

/*
Fonction appelée lorsque le mur le plus proche a été trouvé par la
routine verticale.

1) Enregistre la distance verticale (ray->dist_v) comme
distance finale (*dist).
2) Enregistre les coordonnées d'impact verticales (ray->vx, ray->vy)
comme point de collision final (ray->hit_x, ray->hit_y).
3) Définit le type de collision à Vertical (ray->side = 1).
4) Détermine la face cardinale touchée ('W' ou 'E') en fonction
de l'angle du rayon :
	-'W' si le rayon pointe vers la gauche (angle entre P2 et P3).
	-'E' si le rayon pointe vers la droite.
*/
void	handle_vertical_hit(t_ray *ray, float *dist)
{
	*dist = ray->dist_v;
	ray->hit_x = ray->vx;
	ray->hit_y = ray->vy;
	ray->side = 1;
	if (ray->ra > P2 && ray->ra < P3)
		ray->wall_cardinal = 'W';
	else
		ray->wall_cardinal = 'E';
}

/*
Fonction centrale qui compare les résultats des deux routines
(horizontale et verticale) pour trouver le mur le plus proche,
puis prépare la distance pour le rendu.

-Si ray->dist_h est plus courte, appelle handle_horizontal_hit,
sinon appelle handle_vertical_hit.
-Appelle apply_fish_eye_correction pour corriger *dist du fisheye.
La distance corrigée (*dist) est la valeur finale utilisée pour
projeter la hauteur du mur.
*/
void	get_ray_impact(t_player *player, t_ray *ray, float *dist)
{
	if (ray->dist_h < ray->dist_v)
		handle_horizontal_hit(ray, dist);
	else
		handle_vertical_hit(ray, dist);
	apply_fish_eye_correction(player, ray, dist);
}
