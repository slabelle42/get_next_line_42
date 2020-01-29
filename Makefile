NAME = gnl

FLAG = -Wall -Wextra -Werror -D BUFFER_SIZE=32

MAIN = main.c

SRC =	get_next_line.c
SRC +=	get_next_line_utils.c

all: $(NAME)

$(NAME):
	@gcc $(FLAG) $(MAIN) $(SRC)
	@echo "Creating executable ... OK"

clean:
	@rm -f $(NAME)
	@echo "Cleaning ... OK"

fclean: clean

re: fclean all

.PHONY: all clean fclean re