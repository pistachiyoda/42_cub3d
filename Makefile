NAME = cub3d
CC = gcc
COMMON_LIBS = -lmlx -Lgnl -lgnl -Llibft -lft
ifeq ($(shell uname), Darwin)
	INCS = -I. -Iminilibx-mac -Ignl -Ilibft
	MLX = ./minilibx-mac/libmlx.dylib
	LIBS = -Lminilibx-mac $(COMMON_LIBS)
	API = -framework OpenGL -framework AppKit
	MLX_PASS = ./minilibx-mac/
else
	INCS = -I. -Iminilibx-linux -Ignl -Ilibft
	MLX = ./minilibx-linux/libmlx.a
	LIBS = -Lminilibx-linux $(COMMON_LIBS)
	API = -lXext -lX11 -lm
	MLX_PASS = ./minilibx-linux/
endif
# @todo -fsanitize取る
CFLAGS = -Wall -Wextra -Werror $(INCS) -fsanitize=address
CFILES = main.c calc.c\
		./cast/cast_floor.c ./cast/cast_wall.c ./cast/dda.c\
		./config/config.c ./config/free.c\
		./config/handle_texture.c ./config/handle_floor_ceiling.c\
		./config/handle_map.c ./config/check_map.c ./config/init_position.c\
		./key/key_update.c ./key/key_move.c ./key/key_rotate.c
OBJ = $(CFILES:.c=.o)
GNL = ./gnl/libgnl.a
LIBFT = ./libft/libft.a
HEAD = cub3d.h

all: $(NAME)
$(NAME): $(OBJ) $(GNL) $(LIBFT) $(MLX)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LIBS) $(API)
$(GNL):
	$(MAKE) -C ./gnl/
$(LIBFT):
	$(MAKE) -C ./libft/
$(MLX):
	$(MAKE) -C $(MLX_PASS)
	cp $(MLX) .
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./gnl fclean
	$(MAKE) -C ./libft fclean
	$(MAKE) -C $(MLX_PASS) clean
re: fclean all
.PHONY: all clean fclean re

