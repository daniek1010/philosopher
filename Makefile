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
	@echo "\033[1;33m\nChecking for memory leaks with valgrind...\033[0m"
	valgrind --leak-check=full ./$(NAME) 5 800 200 200 6

valgrind_race: re
	@echo "\033[1;33m\nChecking for race conditions with valgrind...\033[0m"
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 5

.PHONY: all clean fclean re
.SILENT:
