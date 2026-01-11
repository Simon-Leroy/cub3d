/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 14:11:00 by sleroy            #+#    #+#             */
/*   Updated: 2025/12/18 11:11:54 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

/*
On load une texture
mlx_xpm_file_to_image : ouvre le fichier en path, crée une image mlx,
renseigne la taille de l'image dans *width et dans *height

mlx_get_data_addr renvoie l'adresse de début du buffer
où sont stockés les pixels de la texture
*/

int	load_texture(void *mlx, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	return (1);
}

/*
Fonction pour charger les 4 textures des murs dans la mlx
*/
int	load_all_textures(t_graph *graph)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!load_texture(graph->mlx, &graph->tex[i], graph->tex_path[i]))
		{
			write_error("Error loading texture ");
			write_error(graph->tex_path[i]);
			write_error("\n");
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Fonction pour récupérer la couleur du pixel en coordonnées (x, y)
de la texture

-Si hors des dimensions de la texture -> return 0
-Sinon on récupère l'adresse du début du buffer de pixels avec tex->addr
puis on ajoute y * tex->line_len qui va à la ligne y de la texture
et x * (tex->bpp / 8) qui va à la bonne colonne.
tex->bpp / 8 permet le nombre d'octets par pixel (bpp = bits per pixel)

En général 32 bits par pixel donc 4 octets et 1 octet par couleur + octet
optionnel ou vide

On utilise un char car l'unité minimale d'adressage (char = 1 octet), et
pointer vers un bloc de mémoire brut se fait avec un char *
*/
int	get_pixel_tex(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}
