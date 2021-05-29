NAME = cub3d
CC = gcc
INCS = -I. -Imlx -Ignl -Ilibft
LIBS = -Lmlx -lmlx -Lgnl -lgnl -Llibft -lft
# CFLAGS = -Wall -Wextra -Werror -Imlx
# @todo -fsanitize取る
CFLAGS = $(INCS) -fsanitize=address
CFILES = main.c calc.c ./cast/cast_floor.c ./cast/cast_wall.c ./cast/cast_sprite.c ./config/config.c ./config/handle_texture.c ./config/handle_floor_ceiling.c ./config/handle_map.c ./config/check_map.c ./config/init_position.c ./config/init_sprite_order.c
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
	cp $(MLX) .
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./gnl fclean
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./mlx clean
re: fclean all
.PHONY: all clean fclean re
