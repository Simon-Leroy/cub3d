/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:21:14 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 08:33:59 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_type
{
	char			*content;
	struct s_type	*next;
}					t_type;

int					ft_strlenn(char *str);
int					if_line(t_type *list);
t_type				*ft_lstlastt(t_type *list);
int					generate_line(char **line, t_type *list);
void				free_listt(t_type *list);
void				read_and_save(int fd, t_type **list);
void				add_to_list(t_type **list, char *buffer, int readed);
void				extract_line(t_type *list, char **line);
void				clean_list(t_type **list);
char				*get_next_line(int fd);

// utils.c
char				*finish_line(char *line, t_type **list);
void				free_and_null(t_type **list);
int					read_append(int fd, t_type **list);
int					index_after_newline(char *s);
t_type				*make_clean_node(char *src, int start);

// utils2.c
void				clean_list(t_type **list);

#endif
