/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:09:37 by sleroy            #+#    #+#             */
/*   Updated: 2026/01/06 14:11:27 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
Fonction pour détruire toutes les textures qui ont été préalablement
chargées dans la mlx : vérification de chargement avant de détruire
 */
void	destroy_textures(t_graph *graph)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (graph->tex[i].img)
		{
			mlx_destroy_image(graph->mlx, graph->tex[i].img);
			graph->tex[i].img = NULL;
		}
		i++;
	}
}

/*
Fonction pour libérer la mémoire de tous les chemins d'accès vers
les textures
 */
void	free_texture_paths(t_graph *graph)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (graph->tex_path[i])
			free(graph->tex_path[i]);
		i++;
	}
}

/*
Fonction pour libérer la mémoire allouée pour la map
*/
// void	free_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i])
// 		free(map[i++]);
// 	free(map);
// }

/*
Fonction qui libère la mémoire et détruit la mlx à la fin
du programme ou en cas d'échec du programme
*/
int	exit_game(t_graph *graph)
{
	destroy_textures(graph);
	free_texture_paths(graph);
	if (graph->map)
		free_map(graph->map);
	if (graph->player)
		free(graph->player);
	if (graph->img.img_ptr)
		mlx_destroy_image(graph->mlx, graph->img.img_ptr);
	if (graph->win)
		mlx_destroy_window(graph->mlx, graph->win);
	if (graph->mlx)
	{
		mlx_destroy_display(graph->mlx);
		free(graph->mlx);
	}
	if (graph)
		free(graph);
	exit(0);
}
