NAME=get_next_line.o
DEPS=libft/libft.a
LIBFT_DIR=..
INCLUDES=$(LIBFT_DIR)/includes
REL_DEPS=$(DEPS:%=$(LIBFT_DIR)/%)
CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -I $(INCLUDES) -Ofast
CFILES=get_next_line.c

OBJ=$(CFILES:%.c=build/%.o)

$(NAME): $(REL_DEPS) $(OBJ);

$(REL_DEPS):
	@make -C $(dir $@)

build/%.o: %.c
	@mkdir -p build
	@$(CC) $(CFLAGS) $< -o $@

all: $(NAME);

clean fclean re::
	@for file in $(dir $(REL_DEPS)) ; do $(MAKE) -C $$file $@ ; done

clean::
	@rm -rf build/

fclean::
	@rm -rf $(NAME)

re:: fclean all

.PHONY: clean fclean re all $(REL_DEPS)
