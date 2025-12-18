/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:35:21 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:55:49 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parsing.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	check_arg(char *av)
{
	int		fd;
	size_t	len;

	fd = 0;
	if (!av)
		return (print_error("Error\nMissing map file argument\n"), 0);
	len = ft_strlen(av);
	if (len < 5)
		return (print_error("Error\nInvalid file name -> n.cub\n"), 0);
	if (av[len - 1] != 'b' || av[len - 2] != 'u' || av[len - 3] != 'c'
		|| av[len - 4] != '.')
		return (print_error("Error\nInvalid extension-> .cub\n"), 0);
	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (print_error("Error\nCannot open file\n"), 0);
	close(fd);
	return (1);
}
