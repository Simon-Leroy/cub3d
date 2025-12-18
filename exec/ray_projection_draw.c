/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_projection_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:56:10 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour calculer et initialiser les dimensions du mur à dessiner
à l'écran.
-proj_dist = dist entre le joueur et le mur
-line_height = taille du mur à l'image -> inversement proportionnelle
à la distance, plus la distance est longue plus le mur est petit
-draw_start = hauteur où on commence à dessiner le mur à l'écran.
SCREEN_HEIGHT / 2 -> milieu de l'écran on soustrait la moitié de la taille
du mur pour que le mur soit bien centré
-draw_end = hauteur où on arrête de dessiner le mur donc draw_start + taille
*/
void	calculate_wall_dimensions(t_ray *ray, float dist)
{
	ray->proj_dist = dist;
	ray->line_height = (SCREEN_HEIGHT / ray->proj_dist) * IMG_PX;
	ray->draw_start = (SCREEN_HEIGHT / 2.0f) - (ray->line_height / 2.0f);
	ray->draw_end = ray->draw_start + ray->line_height;
}

/*
Fonction d'initialisation de la texture du rayon en fonction du mur que le
joueur regarde
*/
void	select_texture(t_graph *graph, t_ray *ray)
{
	if (ray->wall_cardinal == 'N')
		ray->current_tex = &graph->tex[0];
	else if (ray->wall_cardinal == 'S')
		ray->current_tex = &graph->tex[1];
	else if (ray->wall_cardinal == 'E')
		ray->current_tex = &graph->tex[2];
	else
		ray->current_tex = &graph->tex[3];
}

void	calculate_texture_hit_position(t_ray *ray)
{
	float	wall_x_temp;

	if (ray->side == 0)
		wall_x_temp = ray->hit_x / IMG_PX - floor(ray->hit_x / IMG_PX);
	else
		wall_x_temp = ray->hit_y / IMG_PX - floor(ray->hit_y / IMG_PX);
	ray->wall_x_coord = wall_x_temp;
	if (ray->current_tex)
		ray->tex_col = (int)(ray->wall_x_coord * ray->current_tex->width);
	else
		ray->tex_col = 0;
}

/*
Fonction pour dessiner la colonne de pixels visée par un rayon.

-On commence par initialiser la texture qui sera utilisée pour le dessin
de la colonne
-Boucle qui va parcourir toute la largeur de l'écran pour dessiner toutes
les colonnes (1 pixel de largeur = 1 colonne)
-Si y < draw_start : c'est le plafond, on met la couleur précisée
-Si draw_start < y < draw_end : on dessine la texture
	-tex_pos donne la position verticale du pixel que l'on cherche sur
	la texture (exprimée en % de hauteur de la texture)
	-on multiplie donc par la hauteur de la texture pour avoir l'indice
	réel du pixel de la texture que l'on va dessiner à l'écran
	--> permet d'étirer ou de compresser la texture uniformément quelle
	que soit la hauteur du mur
-Sinon c'est le sol donc couleur du sol
*/
void	draw_pixel_column(t_graph *graph, t_ray *ray, int x_colonne)
{
	t_tex	*tex;
	int		y;
	int		tex_y;
	float	tex_pos;
	int		color;

	tex = ray->current_tex;
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < ray->draw_start)
			ft_pixel_put(&graph->img, x_colonne, y, graph->ceil_color);
		else if (y < ray->draw_end)
		{
			tex_pos = (float)(y - ray->draw_start) / ray->line_height;
			tex_y = (int)(tex_pos * tex->height);
			color = get_pixel_tex(tex, ray->tex_col, tex_y);
			ft_pixel_put(&graph->img, x_colonne, y, color);
		}
		else
			ft_pixel_put(&graph->img, x_colonne, y, graph->floor_color);
		y++;
	}
}

void	draw_ray_column(t_graph *graph, t_ray *ray, int r, float dist)
{
	int	x_column;

	select_texture(graph, ray);
	calculate_texture_hit_position(ray);
	calculate_wall_dimensions(ray, dist);
	x_column = r;
	draw_pixel_column(graph, ray, x_column);
}
