NAME=get_next_line.o
DEPS=libft/libft.a
LIBFT_DIR=..
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I $(INCLUDES) -Ofast
CFILES=get_next_line.c

$(NAME): $(CFILES)
	@$(CC) $(CFLAGS) $^ -o $@

$(REL_DEPS):
	@make -C $(dir $@)

all: $(NAME);

clean:
	@rm -rf *.o

fclean:: clean;

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)
