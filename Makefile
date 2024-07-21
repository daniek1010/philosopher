NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
SRCS = $(wildcard *.c)
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

$(OBJ): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind_leaks: re
	valgrind --leak-check=full ./$(NAME) 7 800 200 200 5

valgrind_race: re
	valgrind --tool=helgrind ./$(NAME) 8 800 200 200 5

.PHONY: all clean fclean re
.SILENT:
