/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:53:47 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

float	get_ntan(float ra)
{
	if (ra == PI)
		return (0);
	if (ra == 0 || ra == P2)
		return (0);
	return (-tan(ra));
}

void	init_vertical_ray(t_ray *r, t_player *p)
{
	float	n_tan;

	r->dof = 0;
	if (r->ra == PI || r->ra == 2 * PI)
	{
		r->dof = DOF;
		return ;
	}
	n_tan = get_ntan(r->ra);
	if (r->ra > P2 && r->ra < P3)
	{
		r->rx = ((int)(p->px / IMG_PX) * IMG_PX) - 0.0001f;
		r->ry = (p->px - r->rx) * n_tan + p->py;
		r->xo = -IMG_PX;
		r->yo = -r->xo * n_tan;
	}
	else
	{
		r->rx = ((int)(p->px / IMG_PX) * IMG_PX) + IMG_PX;
		r->ry = (p->px - r->rx) * n_tan + p->py;
		r->xo = IMG_PX;
		r->yo = -r->xo * n_tan;
	}
}

void	hit_v_wall(t_ray *r, t_graph *graph, t_player *p)
{
	while (r->dof < DOF)
	{
		r->mx = (int)(r->rx / IMG_PX);
		r->my = (int)(r->ry / IMG_PX);
		if (r->mx < 0 || r->my < 0
			|| r->mx >= graph->width || r->my >= graph->height)
			break ;
		if (graph->map[r->my][r->mx] == '1')
		{
			r->vx = r->rx;
			r->vy = r->ry;
			r->dist_v = dist(p->px, p->py, r->vx, r->vy);
			r->dof = DOF;
		}
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof++;
		}
	}
}
