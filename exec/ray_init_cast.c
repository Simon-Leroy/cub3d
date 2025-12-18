/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:56:16 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	init_ray(t_ray *ray, t_player *player, float ra)
{
	ray->ra = ra;
	ray->dist_h = 1000000;
	ray->hx = player->px;
	ray->hy = player->py;
	ray->dist_v = 1000000;
	ray->vx = player->px;
	ray->vy = player->py;
}

/*
Calcul des intersections horizontales et verticales
*/
void	cast_single_ray(t_graph *graph, t_player *player, t_ray *ray)
{
	init_horizontal_ray(ray, player);
	hit_h_wall(ray, graph, player);
	init_vertical_ray(ray, player);
	hit_v_wall(ray, graph, player);
}
