<<<<<<< HEAD
NAME = philo

CC = gcc

CFLAGS = -Wextra -Werror -Wall -I.

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJECTS): %.o : %.c
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
=======
NAME = philosopher
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
>>>>>>> 88c42de (format)
