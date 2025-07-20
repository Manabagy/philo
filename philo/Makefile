NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-pthread -g3

SRC = main.c utils.c parse.c philo.c check_life.c dinner.c
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