#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>       /* For malloc, free */
# include <unistd.h>       /* For write */
# include <limits.h>       /* For INT_MIN, INT_MAX */

/* Node structure for the stack implementation */
typedef struct s_stack
{
	int				value;  /* Integer value stored in the node */
	int				index;  /* Index for sorting algorithm */
	struct s_stack	*next;  /* Pointer to the next node */
}	t_stack;

/* Functions for stack manipulation */
t_stack	*create_node(int value);                /* Creates a new node with given value */
void	push_front(t_stack **stack, t_stack *new);  /* Adds a node to the front of stack */
t_stack	*pop_front(t_stack **stack);           /* Pops the first node from stack */
void	free_stack(t_stack **stack);            /* Frees all nodes in the stack */
int	stack_size(t_stack *stack);            /* Returns the number of nodes in stack */
int	stack_is_sorted(t_stack *stack);       /* Checks if stack is sorted */
int	get_min_value(t_stack *stack);         /* Gets minimum value in stack */
int	get_max_value(t_stack *stack);         /* Gets maximum value in stack */
int	get_index_in_stack(t_stack *stack, int value); /* Gets index of value in stack */

/* Stack operations (push_swap instructions) */
void	sa(t_stack **stack_a, int print);       /* Swap a - swap the first 2 elements */
void	sb(t_stack **stack_b, int print);       /* Swap b - swap the first 2 elements */
void	ss(t_stack **stack_a, t_stack **stack_b, int print); /* Swap a & b */
void	pa(t_stack **stack_a, t_stack **stack_b, int print); /* Push a - push top of b to a */
void	pb(t_stack **stack_a, t_stack **stack_b, int print); /* Push b - push top of a to b */
void	ra(t_stack **stack_a, int print);       /* Rotate a - shift up all elements by 1 */
void	rb(t_stack **stack_b, int print);       /* Rotate b - shift up all elements by 1 */
void	rr(t_stack **stack_a, t_stack **stack_b, int print); /* Rotate a & b */
void	rra(t_stack **stack_a, int print);      /* Reverse rotate a - shift down by 1 */
void	rrb(t_stack **stack_b, int print);      /* Reverse rotate b - shift down by 1 */
void	rrr(t_stack **stack_a, t_stack **stack_b, int print); /* Reverse rotate a & b */

/* Input parsing and error handling */
int	is_number(char *str);                  /* Checks if string is a valid number */
int	is_duplicate(t_stack *stack, int value); /* Checks for duplicate values */
void	parse_arguments(int argc, char **argv, t_stack **stack_a); /* Parses args */
void	error_exit(t_stack **stack_a, t_stack **stack_b); /* Error handling */

/* Sorting algorithms */
void	sort_three(t_stack **stack_a);          /* Sorts a stack of 3 elements */
void	sort_small(t_stack **stack_a, t_stack **stack_b); /* Sorts stack of <= 5 elements */
void	sort_large(t_stack **stack_a, t_stack **stack_b); /* Sorts large stacks */
void	sort_stacks(t_stack **stack_a, t_stack **stack_b); /* Main sorting function */

/* Index assignment for optimization */
void	assign_indexes(t_stack **stack);        /* Assigns indexes to stack elements */

/* Utility functions */
void	ft_putstr_fd(char *s, int fd);          /* Outputs string to file descriptor */
long	ft_atol(const char *str);               /* String to long conversion */

#endif
