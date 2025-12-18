/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:32 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 08:36:16 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*finish_line(char *line, t_type **list)
{
	if (!line)
	{
		free_and_null(list);
		return (NULL);
	}
	clean_list(list);
	if (line[0] != '\0')
		return (line);
	free_and_null(list);
	free(line);
	return (NULL);
}

void	free_and_null(t_type **list)
{
	free_listt(*list);
	*list = NULL;
}

int	read_append(int fd, t_type **list)
{
	char	*buffer;
	int		readed;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	readed = (int)read(fd, buffer, BUFFER_SIZE);
	if (readed <= 0)
	{
		free(buffer);
		if (readed == -1 || *list == NULL)
			free_and_null(list);
		return (0);
	}
	buffer[readed] = '\0';
	add_to_list(list, buffer, readed);
	free(buffer);
	return (1);
}

int	index_after_newline(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

t_type	*make_clean_node(char *src, int start)
{
	t_type	*node;
	int		len;
	int		j;

	node = malloc(sizeof(t_type));
	if (!node)
		return (NULL);
	node->next = NULL;
	len = ft_strlenn(src) - start;
	node->content = malloc(len + 1);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	j = 0;
	while (src[start])
		node->content[j++] = src[start++];
	node->content[j] = '\0';
	return (node);
}
