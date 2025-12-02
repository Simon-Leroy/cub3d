/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:42:52 by sleroy            #+#    #+#             */
/*   Updated: 2024/12/12 23:07:14 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd)
{
	char	*buffer;
	char	*line;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0 && !check_line(line))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), free(buffer), NULL);
		buffer[bytes_read] = '\0';
		line = join_free(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*extract_line(char	*line)
{
	char	*next_line;
	int		len;
	int		i;

	len = 0;
	if (!line[len])
		return (NULL);
	while (line[len] != '\n' && line[len])
		len++;
	next_line = malloc(sizeof(char) + (len + 1 + (line[len] == '\n')));
	if (!next_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		next_line[i] = line[i];
		i++;
	}
	if (line[len] == '\n')
		next_line[len++] = '\n';
	next_line[len] = '\0';
	return (next_line);
}

char	*update_line(char	*line)
{
	char	*updated_line;
	int		len;
	int		new_len;
	int		i;
	int		bool;

	len = 0;
	while (line[len] != '\n' && line[len])
		len++;
	bool = (line[len] == '\n');
	new_len = ft_strlen(line + len + bool);
	updated_line = malloc(sizeof(char) * (new_len + 1));
	if (!updated_line)
		return (NULL);
	i = 0;
	while (i < new_len)
	{
		updated_line[i] = line[len + bool + i];
		i++;
	}
	updated_line[new_len] = '\0';
	free(line);
	return (updated_line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*next_line;
	char		*line_after;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	if (!stash)
	{
		stash = read_line(fd);
		if (!stash)
			return (NULL);
	}
	else
	{
		line_after = read_line(fd);
		if (!line_after)
			return (NULL);
		stash = join_free(stash, line_after);
		free(line_after);
	}
	if (!stash || *stash == '\0')
		return (free(stash), stash = NULL, NULL);
	next_line = extract_line(stash);
	stash = update_line(stash);
	return (next_line);
}
