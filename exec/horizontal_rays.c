/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:03:30 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour récuper l'inverse de la tangente de l'angle
du rayon

tan = opposé / adjacent
ou adjacent = opposé / tan
       |\
       | \
opposé |  \ hypotenuse
       |__C\
	  adjacent

Pour trouver l'intersection des rayons avec les surfaces horizontales,
on a besoin de trouver l'incrément r->xo = l'incrément horizontal = longueur
du côté adjacent entre chaque ligne de la grille (l'incrément vertical
vaut IMG_PX)

D'où le calcul de a_tan qu'on multipliera ensuite par r->yo pour
obtenir r->xo (r->xo = r->yo * tan(r->ra))

Si ra == PI / 2 ou 3 * PI / 2, tan(ra) = 0 donc division
par 0 qu'il faut empêcher
 */
float	get_atan(float ra)
{
	if (ra == P2 || ra == P3)
		return (0);
	return (-1.0f / tan(ra));
}

/*
Fonction qui initialise les coordonnées de départ du rayon

-r->dof compte le nombre de cases que le rayon a traversé

Si ra == PI / 2 ou 3 * PI / 2, le rayon est parfaitement vertical
donc il n'y a pas d'offset horizontal et r->xo vaut 0, pour trouver
les intersections, il n'y a donc qu'à ajouter IMG_PX

Sinon, on calcule a_tan et on a deux cas :
1) r->ra > PI donc rayon dirigé vers le haut
r->ry est initialisé sur la ligne horizontale directement au dessus du joueur
r->rx


*/
void	init_horizontal_ray(t_ray *r, t_player *p)
{
	float	a_tan;

	r->dof = 0;
	if (r->ra == P2 || r->ra == P3)
	{
		r->dof = DOF;
		return ;
	}
	a_tan = get_atan(r->ra);
	if (r->ra > PI)
	{
		r->ry = ((int)(p->py / IMG_PX) * IMG_PX) - 0.0001f;
		r->rx = (p->py - r->ry) * a_tan + p->px;
		r->yo = -IMG_PX;
		r->xo = -r->yo * a_tan;
	}
	else
	{
		r->ry = ((int)(p->py / IMG_PX) * IMG_PX) + IMG_PX;
		r->rx = (p->py - r->ry) * a_tan + p->px;
		r->yo = IMG_PX;
		r->xo = -r->yo * a_tan;
	}
}

/*
Boucle pour trouver l'intersection horizontale
Tant qu'on a pas atteint la limite de cases parcourues ou un mur,
on continue de chercher une intersection. On saute de ligne
horizontale en ligne horizontale

On calcule la position en entier dans la grille du rayon.
-Si on est hors limite de la map, on arrête la boucle
-Si on est dans la map est que l'intersection est un mur,
on initialise hx et hy qui sont les coordonnées de l'intersection
horizontale avec le mur et on calcule la distance entre le joueur
et ce point d'intersection
-Sinon on ajoute les offset x et y, on va tester les cases
qui suivent, on incrémente le compteur de cases parcourues
 */
void	hit_h_wall(t_ray *r, t_graph *graph, t_player *p)
{
	while (r->dof < DOF)
	{
		r->mx = (int)r->rx / IMG_PX;
		r->my = (int)r->ry / IMG_PX;
		if (r->mx < 0 || r->my < 0
			|| r->mx >= graph->width || r->my >= graph->height)
			break ;
		if (r->mx >= 0 && r->my >= 0 && r->mx < graph->width
			&& r->my < graph->height && graph->map[r->my][r->mx] == '1')
		{
			r->hx = r->rx;
			r->hy = r->ry;
			r->dist_h = dist(p->px, p->py, r->hx, r->hy);
			break ;
		}
		else
		{
			r->rx += r->xo;
			r->ry += r->yo;
			r->dof++;
		}
	}
}
