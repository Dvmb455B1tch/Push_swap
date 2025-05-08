NAME = push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  print_operations.c \
	  stack.c \
	  cost.c \
	  position.c \
	  sort.c \
	  validation.c \
	  utils.c \
	  movements.c \
	  swap.c \
	  push.c \
	  rotate.c \
	  reverse_rotate.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
