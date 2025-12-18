/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:24 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 08:34:20 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlenn(char *str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	if_line(t_type *list)
{
	int		i;
	t_type	*current;

	if (list == NULL)
		return (0);
	current = ft_lstlastt(list);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_type	*ft_lstlastt(t_type *list)
{
	t_type	*current;

	if (list == NULL)
		return (NULL);
	current = list;
	while (current->next)
		current = current->next;
	return (current);
}

int	generate_line(char **line, t_type *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			len++;
			if (list->content[i++] == '\n')
				break ;
		}
		list = list->next;
	}
	*line = malloc(len + 1);
	return (*line != NULL);
}

void	free_listt(t_type *list)
{
	t_type	*current;
	t_type	*next;

	current = list;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
