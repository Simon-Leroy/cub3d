/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:09 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:17:00 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static int	normalize_map(t_data *data)
{
	char	**rect;
	int		i;

	rect = ft_calloc(data->map_h + 1, sizeof(char *));
	if (!rect)
		return (print_error("Error\nMalloc failed\n"), 0);
	i = 0;
	while (i < data->map_h)
	{
		if (!alloc_row(&rect[i], data->map_w))
			return (free_map(rect), print_error("Error\nMalloc failed\n"), 0);
		fill_row(rect[i], data->map[i], data->map_w);
		i++;
	}
	rect[i] = NULL;
	free_map(data->map);
	data->map = rect;
	return (1);
}

static int	parse_player_and_chars(t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			if (!check_cell_player(data, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (print_error("Error\nMap must have exactly one player\n"), 0);
	return (1);
}

static char	**dup_map(char **map, int map_h)
{
	char	**duplicate_map;
	int		i;

	i = 0;
	duplicate_map = ft_calloc(map_h + 1, sizeof(char *));
	if (!duplicate_map)
		return (NULL);
	while (map[i])
	{
		duplicate_map[i] = ft_strdup(map[i]);
		if (!duplicate_map[i])
		{
			free_map(duplicate_map);
			return (NULL);
		}
		i++;
	}
	duplicate_map[i] = NULL;
	return (duplicate_map);
}

static int	is_closed_map(t_data *data)
{
	char	**dup;
	int		i;
	int		j;

	dup = dup_map(data->map, data->map_h);
	if (!dup)
		return (print_error("Error\nDup map does not work\n"), 0);
	i = 0;
	while (i < data->map_h)
	{
		j = 0;
		while (j < data->map_w)
		{
			if (!check_closed_cell(dup, data, i, j))
				return (free_map(dup), 0);
			j++;
		}
		i++;
	}
	free_map(dup);
	return (1);
}

int	valid_map(t_data *data)
{
	if (!normalize_map(data))
		return (0);
	if (!parse_player_and_chars(data))
		return (0);
	if (!is_closed_map(data))
		return (0);
	return (1);
}
