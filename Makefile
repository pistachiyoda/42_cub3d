NAME = main
CC = gcc
# CFLAGS = -Wall -Wextra -Werror -Imlx
CFLAGS = -Imlx
CFILES = main.c
OBJ = $(CFILES:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(OBJ)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
