/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:29 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:55:01 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

static size_t	line_len(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] && s[len] != '\n')
		len++;
	return (len);
}

static int	get_map_height(t_list *map_lines)
{
	int		height;
	t_list	*tmp;

	height = 0;
	tmp = map_lines;
	while (tmp)
	{
		height++;
		tmp = tmp->next;
	}
	if (height == 0)
		return (print_error("Error\nEmpty map\n"), 0);
	return (height);
}

static int	alloc_map_array(t_data *data, int height)
{
	data->map = ft_calloc(height + 1, sizeof(char *));
	if (!data->map)
		return (print_error("Error\nMalloc failed\n"), 0);
	data->map_h = height;
	data->map_w = 0;
	return (1);
}

static int	copy_line_to_map(t_data *data, int i, char *src)
{
	size_t	len;

	len = line_len(src);
	if (len > 500)
		return (print_error("Error\nMap too short/big width\n"), 0);
	data->map[i] = malloc(len + 1);
	if (!data->map[i])
	{
		print_error("Error\nMalloc failed\n");
		while (i > 0)
		{
			free(data->map[i - 1]);
			i--;
		}
		free(data->map);
		data->map = NULL;
		return (0);
	}
	ft_memcpy(data->map[i], src, len);
	data->map[i][len] = '\0';
	if ((int)len > data->map_w)
		data->map_w = (int)len;
	return (1);
}

int	build_map_from_list(t_list *map_lines, t_data *data)
{
	int		height;
	int		i;
	t_list	*tmp;

	height = get_map_height(map_lines);
	if (height == 0 || height > 500)
		return (print_error("Error\nMap too short/big height\n"), 0);
	if (!alloc_map_array(data, height))
		return (print_error("Error\nCannot build map from linked list\n"), 0);
	i = 0;
	tmp = map_lines;
	while (tmp)
	{
		if (!copy_line_to_map(data, i, (char *)tmp->content))
			return (0);
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
	return (1);
}
