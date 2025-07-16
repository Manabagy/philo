NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = src/main.c src/utils.c src/parse.c src/philo.c src/check_life.c src/dinner.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re