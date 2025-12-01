NAME = cub3d

SRCFILES = main.cpp

OBJFILES = $(SRCFILES:.cpp=.o)

CFLAGS = -Wall -Wextra -Werror -g3

MLXFLAGS = -Iminilibx -Lminilibx -lmlx -lXext -lX11 -lm

MLXPATH = minilibx

MLXLIB = $(MLXPATH)/libmlx_Linux.a

CC = cc

RM = rm -f

$(NAME): $(OBJFILES)
			$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJFILES) $(MLXLIB)

all: $(NAME)

clean:
			$(RM) $(OBJFILES)

fclean: clean
			$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
