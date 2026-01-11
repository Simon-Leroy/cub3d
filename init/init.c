/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:33 by alandel           #+#    #+#             */
/*   Updated: 2026/01/11 20:23:39 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	init_data(t_data *data)
{
	data->tex_no = NULL;
	data->tex_so = NULL;
	data->tex_we = NULL;
	data->tex_ea = NULL;
	data->floor_color = -1;
	data->ceil_color = -1;
	data->map = NULL;
	data->map_w = 0;
	data->map_h = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->dir = 'N';
}

void	free_data(t_data *data)
{
	int	i;

	if (data->tex_no)
		free(data->tex_no);
	if (data->tex_so)
		free(data->tex_so);
	if (data->tex_we)
		free(data->tex_we);
	if (data->tex_ea)
		free(data->tex_ea);
	if (data->floor_color != 0)
		data->floor_color = 0;
	if (data->ceil_color != 0)
		data->ceil_color = 0;
	if (data->map)
	{
		i = 0;
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
}

int	print_error(const char *msg)
{
	get_next_line(-1);
	if (write(2, msg, ft_strlen(msg)))
		return (1);
	return (0);
}

void	free_map_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}

int	init_map(char *line, t_list **map_lines, int *end_map)
{
	if (is_empty_line(line))
	{
		if (*end_map == 0)
			*end_map = 1;
		free(line);
		return (1);
	}
	if (*end_map != 0)
	{
		print_error("Error\nWrong line detected inside map\n");
		free(line);
		return (0);
	}
	if (!is_map_line(line))
	{
		print_error("Error\nInvalid line inside map\n");
		free(line);
		return (0);
	}
	ft_lstadd_back(map_lines, ft_lstnew(line));
	return (1);
}
