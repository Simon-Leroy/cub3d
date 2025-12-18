/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:06 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:49:44 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	check_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (print_error("Error\nInvalid xpm file,expected atleast-> .xpm\n"),
			0);
	if (path[len - 1] != 'm' || path[len - 2] != 'p' || path[len - 3] != 'x'
		|| path[len - 4] != '.')
	{
		print_error("Error\nInvalid xpm file,expected atleast-> .xpm\n");
		return (0);
	}
	return (1);
}

static int	compare(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strcmp(a, b) == 0);
}

int	textures_already_used(t_data *d)
{
	if (compare(d->tex_no, d->tex_so) || compare(d->tex_no, d->tex_we)
		|| compare(d->tex_no, d->tex_ea) || compare(d->tex_so, d->tex_we)
		|| compare(d->tex_so, d->tex_ea) || compare(d->tex_we, d->tex_ea))
		return (1);
	return (0);
}

static int	check_open_texture(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error("Error\nCannot open texture\n"), 0);
	close(fd);
	return (1);
}

int	parse_texture(char *line, char **texture)
{
	char	*path;

	if (*texture)
		return (print_error("Error\nDuplicate texture identifier\n"), 0);
	path = ft_strtrim(line, " \t\n\v\f\r");
	if (!path)
		return (print_error("Error\nMalloc failed\n"), 0);
	if (path[0] == '\0')
		return (free(path), print_error("Error\nMissing texture path\n"), 0);
	if (!check_extension(path) || !check_open_texture(path))
		return (free(path), 0);
	*texture = ft_strdup(path);
	free(path);
	if (!*texture)
		return (print_error("Error\nMalloc failed\n"), 0);
	return (1);
}
