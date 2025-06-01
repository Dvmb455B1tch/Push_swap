# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 14:48:53 by riramana          #+#    #+#              #
#    Updated: 2025/05/13 14:56:58 by riramana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
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
      reverse_rotate.c \
      stack_utils.c \
      input.c

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
