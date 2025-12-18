/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:54 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:17:00 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_empty_line(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0' || s[i] == '\n');
}

int	is_map_line(const char *s)
{
	int	i;

	i = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '\0' || s[i] == '\n')
		return (0);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '0' && s[i] != '1' && !is_space(s[i]) && s[i] != 'N'
			&& s[i] != 'S' && s[i] != 'E' && s[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	is_header_line(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S'
			&& line[i + 1] == 'O') || (line[i] == 'W'
			&& line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'F')
		|| (line[i] == 'C'))
		return (1);
	return (0);
}

int	flood_fill(char **m, t_data *data, int y, int x)
{
	int	h;
	int	w;

	h = data->map_h;
	w = data->map_w;
	if (y < 0 || x < 0 || y >= h || x >= w)
		return (0);
	if (m[y][x] == '1' || m[y][x] == 'F')
		return (0);
	if (m[y][x] == '0')
		return (1);
	if (m[y][x] != ' ')
		return (0);
	m[y][x] = 'F';
	if (flood_fill(m, data, y - 1, x))
		return (1);
	if (flood_fill(m, data, y + 1, x))
		return (1);
	if (flood_fill(m, data, y, x - 1))
		return (1);
	if (flood_fill(m, data, y, x + 1))
		return (1);
	return (0);
}
