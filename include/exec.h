/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleroy <sleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:50:47 by alandel           #+#    #+#             */
/*   Updated: 2026/01/06 14:30:44 by sleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/gnl/get_next_line.h"
# include "../minilibx/mlx.h"
# include "./parsing.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define X_LEFT 65361
# define X_RIGHT 65363
# define X_ESC 65307

# define IMG_PX 32

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720

# define PI M_PI
# define P2 M_PI_2
# define P3 4.71238898038468985769

# define DR 0.0174533 // 1 degré en radians

# define FOV 1.04719755119659774615
# define MOVE_SPEED 100
# define ROTATION_SPEED 2

# define DOF 100

typedef struct s_player
{
	float		px;
	float		py;
	int			grid_x;
	int			grid_y;
	float		pa;
	float		dir_x;
	float		dir_y;
	float		move_speed;
	float		rotation_speed;
	int			radius;
	int			is_moving_forward;
	int			is_moving_backward;
	int			is_moving_left;
	int			is_moving_right;
	int			is_looking_right;
	int			is_looking_left;
}				t_player;

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_tex;

/*
-dof = depth of field = compteur des cases vérifiées
-ra = angle du rayon
-rx, ry = coordonnées d'intersection du rayon avec la grille
-xo, yo = x/y offset = distance parcourue par le rayon pour atteindre
la prochaine case
-mx, my = indice entier des coordonnées du rayon dans la grille
-hx, hy = coordonnées du point d'impact trouvées par hit_h_wall
-dist_h = distance entre le joueur et le point d'impact horizontal
-vx, vy = pareil mais avec hit_v_wall
-dist_v = distance entre le joueur et le point d'impact vertical
-hit_x, hit_y = distance finale trouvée pour le point d'impact
le plus proche
-side = indique si le mur le plus proche a été touché par une intersection
horizontale ou verticale
-wall_cardinal = indique la face cardinale touchée
-proj_dist = distance finale du mur corrigée du fish eye
-line_height = hauteur de la colonne du mur à dessiner sur l'écran
plus la distance est courte, plus le mur est grand
-draw_start = coordonnée Y en pixel où le dessin du mur
doit commencer
-draw_end = coordonnée Y en pixel où le dessin du mur s'arrête
-wall_x_coord = coordonnée X fractionnaire (entre 0 et 1) du point
d'impact sur la surface du mur -> détermine la colonne de pixels à
prélever dans la texture
-tex_col = la colonne de pixels de la texture à utiliser, obtenue
à partir de wall_x_coord
-current_tex = texture à afficher sur le mur, en fonction de wall_cardinal
 */
typedef struct s_ray
{
	float		dof;
	float		ra;
	float		rx;
	float		ry;
	float		xo;
	float		yo;
	int			mx;
	int			my;
	float		hx;
	float		hy;
	float		vx;
	float		vy;
	float		hit_x;
	float		hit_y;
	float		dist_h;
	float		dist_v;
	int			side;
	int			wall_cardinal;
	float		proj_dist;
	float		line_height;
	float		draw_start;
	float		draw_end;
	float		wall_x_coord;
	int			tex_col;
	t_tex		*current_tex;
}				t_ray;

/*
Structure pour dessiner tous les pixels hors écran puis les afficher
d'un seul coup

-*img_ptr : pointeur vers l'image, pour l'afficher ou la détruire
-*data_addr : pointeur vers le buffer de pixels où sont stockées toutes
les couleurs de tous les pixels de l'image affichée
-bits_per_pixel : bits utilisés pour représenter la couleur des pixels
-line_len : nombre d'octets utilisés une ligne horizontale complète
-endian : indique l'ordre dans lequel les octets sont stockés pour un
même pixel
 */
typedef struct s_img
{
	void		*img_ptr;
	char		*data_addr;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_graph
{
	void		*mlx;
	void		*win;
	int			floor_color;
	int			ceil_color;
	char		**map;
	t_tex		tex[4];
	char		*tex_path[4];
	t_player	*player;
	t_img		img;
	int			height;
	int			width;
	char		dir;
}				t_graph;

//					==== PARSING ====

//					==== MOVEMENT AND CAMERA ====

// check_move.c

int				check_move_x(t_graph *graph, t_player *player, float dx);
int				check_move_y(t_graph *graph, t_player *player, float dy);

// movement.c & camera.c

int				handle_movement(t_graph *graph, t_player *player, float delta);
int				handle_rotation(t_player *player, float delta);
void			update_direction_vectors(t_player *player);

//					==== GAME LOOP ====

// loop.c

int				key_press_hook(int key, t_graph *graph);
int				key_release_hook(int key, t_graph *graph);
int				move_loop(t_graph *graph);

//					==== RAYCASTING ====

// ray_init_cast.c

void			init_ray(t_ray *ray, t_player *player, float ra);
void			cast_single_ray(t_graph *graph, t_player *player, t_ray *ray);

// horizontal/vertical_rays.c

void			init_horizontal_ray(t_ray *ray, t_player *player);
void			hit_h_wall(t_ray *ray, t_graph *graph, t_player *player);
void			init_vertical_ray(t_ray *ray, t_player *player);
void			hit_v_wall(t_ray *ray, t_graph *graph, t_player *player);

// ray_impact.c

void			get_ray_impact(t_player *player, t_ray *ray, float *dist);

// ray_projection_draw.c

void			draw_ray_column(t_graph *graph, t_ray *ray, int r, float dist);

// raycaster.c

void			cast_ray(t_graph *graph, t_player *player, float ra);

//					==== RENDERING ====

// textures.c

int				get_pixel_tex(t_tex *tex, int x, int y);
int				load_all_textures(t_graph *graph);

// render.c

void			init_image(t_graph *graph);
int				render_frame(t_graph *graph);
void			ft_pixel_put(t_img *img, int x, int y, int color);

//				==== INIT & EXIT ====

// init.c

int				init_player(t_data *data, t_graph *graph, t_player *player);

// exit.c

void			destroy_textures(t_graph *graph);
int				exit_game(t_graph *graph);

//				==== UTILS ====

// utils.c

float			normalise_angle(float angle);
float			dist(float ax, float ay, float bx, float by);
int				write_error(char *str);

// time.c

long			get_time_ms(void);

void			draw_rays(t_graph *graph);
void			draw_rays_minimap(t_graph *graph);

#endif
