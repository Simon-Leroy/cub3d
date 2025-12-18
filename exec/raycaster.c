/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:20:30 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	cast_ray(t_graph *graph, t_player *player, float pa)
{
	t_ray	ray;
	float	ra;
	float	dist;
	float	angle_step;
	int		r;

	angle_step = FOV / SCREEN_WIDTH;
	r = 0;
	while (r < SCREEN_WIDTH)
	{
		ra = pa - (FOV / 2.0f) + (r * angle_step);
		ra = normalise_angle(ra);
		init_ray(&ray, player, ra);
		cast_single_ray(graph, player, &ray);
		get_ray_impact(player, &ray, &dist);
		draw_ray_column(graph, &ray, r, dist);
		r++;
	}
}
