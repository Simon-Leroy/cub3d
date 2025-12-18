/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:32 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 08:50:22 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_list(t_type **list)
{
	t_type	*last;
	t_type	*clean_node;
	int		start;

	if (!list || !*list)
		return ;
	last = ft_lstlastt(*list);
	start = index_after_newline(last->content);
	clean_node = make_clean_node(last->content, start);
	free_listt(*list);
	*list = clean_node;
}

void	extract_line(t_type *list, char **line)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	generate_line(line, list);
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if ((list->content[i]) == '\n')
			{
				(*line)[j++] = list->content[i++];
				break ;
			}
			(*line)[j++] = list->content[i++];
		}
		list = list->next;
	}
	(*line)[j] = '\0';
}
