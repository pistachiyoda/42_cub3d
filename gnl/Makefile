NAME = libgnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
CFILES = get_next_line.c get_next_line_utils.c
OBJ = $(CFILES:.c=.o)
all: $(NAME)
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
main: $(NAME)
	$(CC) -o a.out -D BUFFER_SIZE=5 $(NAME) main.c
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re