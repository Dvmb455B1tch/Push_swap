# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025-05-04 12:00:00 by student           #+#    #+#              #
#    Updated: 2025-05-04 12:00:00 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap                 # Name of the executable

CC = cc                          # Compiler to use
CFLAGS = -Wall -Wextra -Werror   # Compilation flags for strict checking

SRCS = main.c \                  # List of source files
       stack_operations.c \
       stack_utils.c \
       operations_swap.c \
       operations_push.c \
       operations_rotate.c \
       operations_reverse_rotate.c \
       parse_arguments.c \
       utils.c \
       sort_three.c \
       sort_small.c \
       sort_large.c \
       sort.c

OBJS = $(SRCS:.c=.o)             # Object files derived from source files

all: $(NAME)                     # Default target builds the executable

$(NAME): $(OBJS)                 # Link rule for executable
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)  # Link object files into executable

%.o: %.c                         # Compilation rule for object files
	$(CC) $(CFLAGS) -c $< -o $@  # Compile source into object file

clean:                           # Clean target removes object files
	rm -f $(OBJS)                # Remove all object files

fclean: clean                    # Full clean removes objects and executable
	rm -f $(NAME)                # Remove the executable

re: fclean all                   # Rebuild everything from scratch

.PHONY: all clean fclean re      # Declare phony targets
