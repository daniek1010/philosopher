NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
# CFLAGS = -I.
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

.PHONY: all clean fclean re
.SILENT:
