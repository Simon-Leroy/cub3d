/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:32 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 08:36:37 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_and_save(int fd, t_type **list)
{
	int	status;

	status = 1;
	while (!if_line(*list) && status == 1)
	{
		status = read_append(fd, list);
		if (status == -1)
		{
			free_and_null(list);
			return ;
		}
	}
}

static t_type	*new_node_from_buf(char *buffer, int readed)
{
	t_type	*node;
	int		i;

	node = malloc(sizeof(t_type));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->content = malloc(readed + 1);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	i = 0;
	while (i < readed)
	{
		node->content[i] = buffer[i];
		i++;
	}
	node->content[i] = '\0';
	return (node);
}

static void	append_node(t_type **list, t_type *node)
{
	t_type	*last;

	if (!*list)
	{
		*list = node;
		return ;
	}
	last = ft_lstlastt(*list);
	last->next = node;
}

void	add_to_list(t_type **list, char *buffer, int readed)
{
	t_type	*node;

	node = new_node_from_buf(buffer, readed);
	if (!node)
		return ;
	append_node(list, node);
}

char	*get_next_line(int fd)
{
	static t_type	*list;
	char			*line;

	if (fd == -1)
	{
		free_and_null(&list);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read_and_save(fd, &list);
	if (!list)
		return (NULL);
	extract_line(list, &line);
	return (finish_line(line, &list));
}

/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("f.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}*/
