NAME = ft_ls
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBFT_SRC = libft/ft_string.c libft/ft_memory.c libft/ft_output.c \
			libft/ft_number.c
SRC = src/main.c src/args.c src/operands.c src/list.c src/entry.c src/sort.c \
	  src/stat_time.c \
	  src/display.c src/columns.c src/widths.c src/name_cache.c src/device.c \
	  src/identity.c \
	  src/long.c \
	  src/mode.c \
	  src/path.c src/error.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT): $(LIBFT_SRC) libft/include/libft.h libft/Makefile
	$(MAKE) -C libft

src/%.o: src/%.c include/ft_ls.h libft/include/libft.h
	$(CC) $(CFLAGS) -Iinclude -Ilibft/include -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
