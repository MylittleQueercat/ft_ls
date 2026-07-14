NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_string.c ft_memory.c ft_output.c ft_number.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c include/libft.h
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
