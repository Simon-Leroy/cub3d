/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:14:16 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:17:00 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	check_closed_cell(char **dup, t_data *data, int i, int j)
{
	char	c;

	c = data->map[i][j];
	if (c == '0' && is_border(data, i, j))
		return (print_error("Error\nMap not closed '0'\n"), 0);
	if (c == ' ' && is_border(data, i, j))
	{
		if (flood_fill(dup, data, i, j))
			return (print_error("Error\nMap not closed ' '\n"), 0);
	}
	return (1);
}

int	is_border(t_data *data, int i, int j)
{
	if (i == 0 || j == 0)
		return (1);
	if (i == data->map_h - 1 || j == data->map_w - 1)
		return (1);
	return (0);
}

int	check_cell_player(t_data *data, int i, int j, int *count)
{
	char	c;

	c = data->map[i][j];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		*count = *count + 1;
		data->player_x = j + 0.5;
		data->player_y = i + 0.5;
		data->dir = c;
		data->map[i][j] = '0';
		return (1);
	}
	if (c != '0' && c != '1' && c != ' ')
		return (print_error("Error\nInvalid char in map\n"), 0);
	return (1);
}

int	alloc_row(char **dst, int w)
{
	*dst = malloc(w + 1);
	if (!*dst)
		return (0);
	return (1);
}

void	fill_row(char *dst, char *src, int w)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(src);
	while (j < w)
	{
		if (j < len)
			dst[j] = src[j];
		else
			dst[j] = ' ';
		j++;
	}
	dst[j] = '\0';
}
