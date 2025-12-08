#include "cub3d.h"

// initialisation du rayon pour un angle donné
void init_ray(t_ray *ray, t_player *player, float ra)
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

// calcul de la distance corrigée et de la couleur
void	get_ray_impact(t_player *player, t_ray *ray, float *dist, int *color)
{
	float	ca;
	if (ray->distH < ray->distV)
	{
		*dist = ray->distH;
		*color = 0xB03119;
	}
	if (ray->distV < ray->distH)
	{
		*dist = ray->distV;
		*color = 0xFF2900;
	}
	ca = normalise_angle(player->pa - ray->ra);
	*dist *= cos(ca); // correction fish-eye
}

// dessin d’une colonne verticale
void draw_ray_column(t_graph *graph, int r, float dist, int color)
{
	float	lineH;
	float	y_depart;
	float	y_fin;
	int	col_width;
	int	x_colonne;

	lineH = (IMG_PX * HEIGHT) / dist;
	if (lineH > HEIGHT)
		lineH = HEIGHT;
	y_depart = (HEIGHT / 2.0f) - (lineH / 2.0f);
	y_fin = y_depart + lineH;
	col_width = WIDTH / 60;
	x_colonne = r * col_width;
	for (int x = 0; x < col_width; x++)
		draw_line(graph->mlx, graph->win, x_colonne + x, y_depart, x_colonne + x, y_fin, color);
}

// boucle principale de raycasting
void cast_ray(t_graph *graph, t_player *player, float pa)
{

	t_ray	ray;
	float	ra;
	float	dist;
	int		color;

	ra = pa - DR * 30;
	ra = normalise_angle(ra);
	for (int r = 0; r < 60; r++)
	{
		init_ray(&ray, player, ra);
		cast_single_ray(graph, player, &ray);
		get_ray_impact(player, &ray, &dist, &color);
		draw_ray_column(graph, r, dist, color);
		ra += DR;
		ra = normalise_angle(ra);
	}
}

#include "cub3d.h"

// Dessine les rayons sur la minimap
void draw_rays_minimap(t_graph *graph)
{
	t_ray ray;
	float ra;
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
}

