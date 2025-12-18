/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:02 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:30:13 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	parse_header_line(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O'
		&& is_space((unsigned char)line[i + 2]))
		return (parse_texture(line + i + 2, &data->tex_no));
	if (line[i] == 'S' && line[i + 1] == 'O'
		&& is_space((unsigned char)line[i + 2]))
		return (parse_texture(line + i + 2, &data->tex_so));
	if (line[i] == 'W' && line[i + 1] == 'E'
		&& is_space((unsigned char)line[i + 2]))
		return (parse_texture(line + i + 2, &data->tex_we));
	if (line[i] == 'E' && line[i + 1] == 'A'
		&& is_space((unsigned char)line[i + 2]))
		return (parse_texture(line + i + 2, &data->tex_ea));
	if (line[i] == 'F' && is_space((unsigned char)line[i + 1]))
		return (parse_color(line + i + 1, &data->floor_color));
	if (line[i] == 'C' && is_space((unsigned char)line[i + 1]))
		return (parse_color(line + i + 1, &data->ceil_color));
	return (print_error("Error\nInvalid identifier in header\n"), 0);
}

static int	init_header(char *line, t_list **map_lines, t_data *data,
		int *in_map)
{
	if (is_empty_line(line))
	{
		free(line);
		return (1);
	}
	if (is_header_line(line))
	{
		if (!parse_header_line(line, data))
		{
			free(line);
			return (0);
		}
		free(line);
		return (1);
	}
	if (is_map_line(line))
	{
		*in_map = 1;
		ft_lstadd_back(map_lines, ft_lstnew(line));
		return (1);
	}
	free(line);
	print_error("Error\nErreur dans header\n");
	return (0);
}

static int	valid_header_n_map(t_list *map_lines, t_data *data)
{
	if (!map_lines)
		return (print_error("Error\nMissing map\n"), 0);
	if (!data->tex_no || !data->tex_so || !data->tex_we || !data->tex_ea)
		return (print_error("Error\nMissing textures\n"), 0);
	if (textures_already_used(data))
		return (print_error("Error\nSame textures used\n"), 0);
	if (data->floor_color == -1 || data->ceil_color == -1)
		return (print_error("Error\nMissing colors\n"), 0);
	return (1);
}

static int	read_and_store(int fd, t_list **map_lines, t_data *data)
{
	char	*line;
	int		in_map;
	int		end_map;

	in_map = 0;
	end_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!in_map)
		{
			if (!init_header(line, map_lines, data, &in_map))
				return (0);
		}
		else if (!init_map(line, map_lines, &end_map))
			return (0);
	}
	return (1);
}

int	save_map(char *path_map, t_data *data)
{
	int		fd;
	t_list	*map_lines;

	map_lines = NULL;
	fd = open(path_map, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nCannot open file\n"), 0);
	if (!read_and_store(fd, &map_lines, data))
		return (free_map_list(map_lines), close(fd), 0);
	close(fd);
	if (!valid_header_n_map(map_lines, data))
		return (free_map_list(map_lines), 0);
	if (!build_map_from_list(map_lines, data))
		return (free_map_list(map_lines), 0);
	free_map_list(map_lines);
	return (1);
}
