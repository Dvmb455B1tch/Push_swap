NAME = push_swap                 # Name of the executable

CC = cc                          # Compiler to use
CFLAGS = -Wall -Wextra -Werror   # Compilation flags for strict checking

SRCS = main.c \
       stack_ops.c \
       stack_utils.c \
       ops_swap.c \
       ops_push.c \
       ops_rotate.c \
       ops_reverse_rotate.c \
       parse_args.c \
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
