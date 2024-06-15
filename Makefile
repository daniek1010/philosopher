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