/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:55:38 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
mlx_new_image alloue une image en mémoire de dimension
WIDTH et HEIGHT
*/
void	init_image(t_graph *graph)
{
	if (!graph->mlx)
		return ;
	graph->img.img_ptr = mlx_new_image(graph->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!graph->img.img_ptr)
		return ;
	graph->img.data_addr = mlx_get_data_addr(
			graph->img.img_ptr,
			&graph->img.bits_per_pixel,
			&graph->img.line_len,
			&graph->img.endian);
}

/*
Fonction pour dessiner un pixel à la position (x, y) dans l'image
mlx
On s'assure que x et y sont bien dans l'image
On utilise un char * (car un char = 1 octet)
img->data_addr = adresse du début du buffer de pixels
+ y * img->line_len -> avance à la ligne y
+ x * (img->bits_per_pixel / 8) -> atteint le pixel x de la ligne y
*(unsigned int*)dst = color -> écrit la couleur dans ce pixel
 */
void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = img->data_addr
			+ (y * img->line_len + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
Fonction de render
cast_ray fait le raycasting et met les pixels dans une image
puis on affiche cette image avec mlx_put_image_to_window

Fonction appelée à chaque fois que le joueur appuie sur une touche
de mouvement, donc se déplace ou déplace la caméra
 */
int	render_frame(t_graph *graph)
{
	cast_ray(graph, graph->player, graph->player->pa);
	mlx_put_image_to_window(graph->mlx, graph->win, graph->img.img_ptr, 0, 0);
	return (0);
}
