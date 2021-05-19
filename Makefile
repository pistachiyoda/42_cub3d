NAME = cub3d
CC = gcc
INCS = -I. -Imlx -Ignl -Ilibft
LIBS = -Lmlx -lmlx -Lgnl -lgnl -Llibft -lft
# CFLAGS = -Wall -Wextra -Werror -Imlx
CFLAGS = $(INCS)
CFILES = main.c calc.c ./config/config.c
OBJ = $(CFILES:.c=.o)
MLX = ./mlx/libmlx.dylib
GNL = ./gnl/libgnl.a
LIBFT = ./libft/libft.a

all: $(NAME)
$(NAME): $(OBJ) $(GNL) $(LIBFT) $(MLX)
	$(CC) -o $(NAME) $(CFLAGS) $(LIBS) -framework OpenGL -framework AppKit $(OBJ)
$(GNL):
	$(MAKE) -C ./gnl/
$(LIBFT):
	$(MAKE) -C ./libft/
$(MLX):
	$(MAKE) -C ./mlx/
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./gnl fclean
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./mlx clean
re: fclean all
.PHONY: all clean fclean re
