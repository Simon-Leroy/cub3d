/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alandel <alandel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:51:03 by alandel           #+#    #+#             */
/*   Updated: 2025/12/18 11:54:38 by alandel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// #include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_color;
	int		ceil_color;
	char	**map;
	int		map_w;
	int		map_h;
	int		player_x;
	int		player_y;
	char	dir;
}			t_data;

// init/build_map.c
int			build_map_from_list(t_list *map_lines, t_data *data);

// init/init.c
void		init_data(t_data *data);
void		free_data(t_data *data);
int			print_error(const char *msg);
void		free_map_list(t_list *lst);
int			init_map(char *line, t_list **map_lines, int *end_map);

// parsing/utils.c
int			is_empty_line(const char *s);
int			is_map_line(const char *s);
int			is_space(char c);
int			is_header_line(char *line);
int			flood_fill(char **m, t_data *data, int y, int x);

// parsing/utils2.c
int			check_closed_cell(char **dup, t_data *data, int i, int j);
int			is_border(t_data *data, int i, int j);
int			check_cell_player(t_data *data, int i, int j, int *count);
int			alloc_row(char **dst, int w);
void		fill_row(char *dst, char *src, int w);

// parsing/parse_arg.c
int			check_arg(char *av);
void		free_map(char **map);

// parsing/parse_colors.c
int			parse_color(char *line, int *color);

// parsing/parse_header.c
int			parse_header_line(char *line, t_data *data);
int			save_map(char *path_map, t_data *data);

// parsing/parse_map.c
int			valid_map(t_data *data);

// parsing/parse_textures.c
int			textures_already_used(t_data *d);
int			parse_texture(char *line, char **texture);

#endif
