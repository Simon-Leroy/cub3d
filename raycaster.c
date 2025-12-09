#include "cub3d.h"

// initialisation du rayon pour un angle donné
void init_ray(t_ray *ray, t_player *player, double ra)
{
	ray->ra = ra;
	ray->distH = 1000000;
	ray->hx = player->px;
	ray->hy = player->py;
	ray->distV = 1000000;
	ray->vx = player->px;
	ray->vy = player->py;
}

// calcul des intersections horizontales et verticales
void cast_single_ray(t_graph *graph, t_player *player, t_ray *ray)
{
	init_horizontal_ray(ray, player);
	hit_h_wall(ray, graph, player);
	init_vertical_ray(ray, player);
	hit_v_wall(ray, graph, player);
}

/*
Le raycasting se fait en deux temps et récupère deux distances : la surface horizontale
touchée par le rayon et la surface verticale
Cette fonction détermine le point d'impact le plus proche parmi les deux surfaces
*/
void	get_ray_impact(t_player *player, t_ray *ray, double *dist, int *color)
{
	double	ca;
	if (ray->distH < ray->distV)
	{
		*dist = ray->distH;
		*color = 0xB03119;
		ray->hit_x = ray->hx;
		ray->hit_y = ray->hy;
		ray->side = 0;
		if (ray->ra > 0 && ray->ra < PI)
			ray->wall_cardinal = 'N';
		else
			ray->wall_cardinal = 'S';
	}
	else
	{
		*dist = ray->distV;
		*color = 0xFF2900;
		ray->hit_x = ray->vx;
		ray->hit_y = ray->vy;
		ray->side = 1;
		if (ray->ra > P2 && ray->ra < P3)
			ray->wall_cardinal = 'W';
		else
			ray->wall_cardinal = 'E';
	}
	ca = normalise_angle(player->pa - ray->ra);
	*dist *= cos(ca); // correction fish-eye
}
/*
Fonction pour dessiner l'environnement colonne par colonne
dans img.

-r correspond à l'indice du rayon ou indice de la colonne de pixels à
dessiner à l'écran
-dist correspond à la distance calculée lors du raycasting et corrigée
du fish eye
-lineH : hauteur en pixel du mur à dessiner à l'écran. Plus il est loin
plus lineH est petit
-y_start : pixel à partir duquel on commence à dessiner le mur (en partant du
haut du canvas mlx) -> HEIGHT / 2 = moitié du canvas on soustrait lineH / 2
donc le mur occupera autant de pixels en dessous et au dessus du milieu du canvas
(il est centré)
-y_end : fin du dessin du mur

3 boucles pour mettre dans img les pixels :
-du plafond d'abord donc de 0 au haut du mur
-du mur entre y_start et y_end
-du sol entre y_end et le bas du canvas (donc HEIGHT)
 */
void draw_ray_column(t_graph *graph, t_ray *ray, int r, double dist, int color)
{
	double	lineH;
	double	y_start;
	double	y_end;
	int		y;
	int		x_colonne = r;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	wall_x;
	t_tex	*tex;

	if (ray->wall_cardinal == 'N')
		tex = &graph->tex[0];
	else if (ray->wall_cardinal == 'S')
		tex = &graph->tex[1];
	else if (ray->wall_cardinal == 'E')
		tex = &graph->tex[2];
	else
		tex = &graph->tex[3];
	lineH = (IMG_PX * HEIGHT) / dist;
	y_start = (HEIGHT / 2.0f) - (lineH / 2.0f);
	y_end = y_start + lineH;

/* 	wall_x : extrait la partie décimale de la position d'impact du rayon sur le mur
	ray->hit_x  / IMG_PX convertit la coordonnée d'impact en cases de textures (41.27 par exemple)
	- floor(ray->hit_x / IMG_PX) -> enlève la partie entière -> wall_x = 0.27
	Donc le rayon touche le mur à 27% du mur
	On multiplie par la largeur de la texture et on sait dans quelle colonne de la texture
	on doit aller prélever le pixel à imprimer = texture sampling
	*/
	if (ray->side == 0)
		wall_x = ray->hit_x / IMG_PX - floor(ray->hit_x / IMG_PX);
	else
		wall_x = ray->hit_y / IMG_PX - floor(ray->hit_y / IMG_PX);
	tex_x = (int)(wall_x * tex->width);
	y = 0;
	while (y < y_start)
	{
		ft_pixel_put(&graph->img, x_colonne, y, 0x27D3F5);
		y++;
	}
	while (y < y_end)
	{
		tex_pos = (double)(y - y_start) / lineH;
		tex_y = (int)(tex_pos * tex->height);
		color = get_pixel_tex(tex, tex_x, tex_y);
		ft_pixel_put(&graph->img, x_colonne, y, color);
		y++;
	}
	while (y < HEIGHT)
	{
		ft_pixel_put(&graph->img, x_colonne, y, 0x8A6737);
		y++;
	}
}


void cast_ray(t_graph *graph, t_player *player, double pa)
{
	t_ray	ray;
	double	ra;
	double	dist;
	int		color;
	double	angle_step;

	angle_step = FOV / WIDTH;
	for (int r = 0; r < WIDTH; r++)
	{
		ra = pa - (FOV / 2.0f) + (r * angle_step);
		ra = normalise_angle(ra);
		init_ray(&ray, player, ra);
		cast_single_ray(graph, player, &ray);
		get_ray_impact(player, &ray, &dist, &color);
		draw_ray_column(graph, &ray, r, dist, color);
	}
}
/*
// Dessine les rayons sur la minimap
void draw_rays_minimap(t_graph *graph)
{
	t_ray ray;
	double ra;
	int r;
	int color;

	// Angle de départ pour le premier rayon
	ra = graph->player->pa - DR * 30;
	ra = normalise_angle(ra);
	r = 0;
	while (r < 60)
	{
		init_ray(&ray, graph->player, ra);
		cast_single_ray(graph, graph->player, &ray);

		// On choisit le point d'impact le plus proche
		if (ray.distH < ray.distV)
		{
			color = 0x00FF00; // vert pour impact horizontal
			draw_line(graph->mlx, graph->win,
					graph->player->px,
					graph->player->py,
					ray.hx,
					ray.hy,
					color);
		}
		else
		{
			color = 0x0000FF; // bleu pour impact vertical
			draw_line(graph->mlx, graph->win,
					graph->player->px,
					graph->player->py,
					ray.vx,
					ray.vy,
					color);
		}
		// Passe au rayon suivant
		ra += DR;
		ra = normalise_angle(ra);
		r++;
	}
} */

