NAME = Cub3d

SRCFILES =	libft/gnl/get_next_line_utils.c \
			libft/gnl/get_next_line.c \
			exec/map_grid.c \
			exec/camera.c \
			exec/movement.c \
			exec/check_move.c \
			exec/utils.c \
			exec/horizontal_rays.c \
			exec/vertical_rays.c \
			exec/ray_impact.c \
			exec/ray_init_cast.c \
			exec/ray_projection_draw.c \
			exec/raycaster.c \
			exec/textures.c \
			exec/render.c \
			exec/loop.c \
			exec/exit.c \
			exec/init.c \
			exec/time.c \
			exec/main.c \
			parsing/parse_arg.c \
			parsing/save_map.c \
			parsing/parse_colors.c \
			parsing/parse_textures.c \
			parsing/utils.c \
			parsing/utils2.c \
			init/init.c \
			init/build_map.c \
			parsing/parse_map.c

OBJDIR = obj
OBJFILES = $(SRCFILES:%.c=$(OBJDIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g3 -O3 -ffast-math

MLXPATH = minilibx
LIBFT_DIR = libft

MLXFLAGS = -I$(MLXPATH) -L$(MLXPATH) -lXext -lX11 -lm
LIBFT_FLAGS = -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft

MLXLIB = $(MLXPATH)/libmlx_Linux.a

CC = cc
RM = rm -f

$(NAME): $(OBJFILES)
	make -C $(LIBFT_DIR)
	make -C $(MLXPATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJFILES) $(MLXLIB) $(MLXFLAGS) $(LIBFT_FLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJFILES)
	make -C $(LIBFT_DIR) clean
	make -C $(MLXPATH) clean

fclean: clean
	$(RM) $(NAME)
	rm -rf $(OBJDIR)

re: fclean all

.PHONY: clean fclean all re
