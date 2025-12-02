/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:40:38 by sleroy            #+#    #+#             */
/*   Updated: 2025/04/09 11:20:29 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

void	ft_bzero(void *s, size_t n);

int		check_line(char *str);
size_t	ft_strlen(const char *str);

char	*ft_strjoin(const char *s1, const char *s2);
char	*join_free(char *line, char *buffer);
char	*update_line(char	*line);
char	*extract_line(char	*line);
char	*get_next_line(int fd);

#endif
