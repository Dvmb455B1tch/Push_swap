#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>      /* For write, etc */
# include <stdlib.h>      /* For malloc, free */

/*
Structure for each element in the stack
*/
typedef struct s_stack
{
	int	value;		/* Actual value */
	int	index;		/* Sorted index */
	int	pos;       	/* Position in stack */
	struct s_stack	*next;	/* Pointer to next node */
}t_stack;

/* ---------- operations.c ---------- */

void	sa(t_stack **a);                /* Swap top two elements of a */
void	sb(t_stack **b);                /* Swap top two elements of b */
void	ss(t_stack **a, t_stack **b);   /* sa and sb at the same time */

void	pa(t_stack **a, t_stack **b);   /* Push from b to a */
void	pb(t_stack **a, t_stack **b);   /* Push from a to b */

void	ra(t_stack **a);                /* Rotate a up */
void	rb(t_stack **b);                /* Rotate b up */
void	rr(t_stack **a, t_stack **b);   /* ra and rb at the same time */

void	rra(t_stack **a);               /* Reverse rotate a */
void	rrb(t_stack **b);               /* Reverse rotate b */
void	rrr(t_stack **a, t_stack **b);  /* rra and rrb at the same time */

/* ---------- parse.c ---------- */

void	build_stack(t_stack **a, int argc, char **argv); /* Validate and build initial stack */
int	is_number(const char *str);                     /* Check if string is number */
int	has_duplicates(t_stack *stack, int value);      /* Check for duplicate values */
long	ft_atol(const char *str);                        /* String to long conversion */
void	append_node(t_stack **stack, int value);         /* Add new node to end of stack */

/* ---------- sort.c ---------- */

void	turk_sort(t_stack **a, t_stack **b);             /* Main sorting logic */
void	sort_three(t_stack **a);                         /* Special case: 3 numbers */
void	index_stack(t_stack *a);                         /* Assign sorted index to each node */
void	push_max_to_a(t_stack **a, t_stack **b);         /* Push max value from b to a */



/* ---------- utils.c ---------- */

void	error_exit(void);                                /* Print error and exit */
int	is_sorted(t_stack *stack);                      /* Check if stack is sorted */
int	stack_size(t_stack *stack);                     /* Count size of a stack */
void	free_stack(t_stack **stack);                     /* Free stack memory */

/* ---------- stack_utils.c ---------- */

t_stack	*get_last_node(t_stack *stack);                 /* Return last node in stack */
t_stack	*get_max_node(t_stack *stack);                  /* Return node with highest index */
void	update_positions(t_stack *stack);                /* Refresh .pos field for each node */

#endif

