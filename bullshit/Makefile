NAME = push_swap
SRC = main.c \
      swap.c \
      push.c \
      rotate.c \
      reverse_rotate.c \
      stack_utils.c \
      sort.c \
      position.c \
      cost.c \
      utils.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
