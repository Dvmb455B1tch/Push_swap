#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>  /* For write function */
# include <stdlib.h>  /* For malloc, free functions */

/* Node structure for the stack */
typedef struct s_node
{
	int				value;  /* Value of the node */
	int				index;  /* Index of the node in sorted order */
	int				pos;    /* Current position in stack */
	int				target_pos;  /* Target position in other stack */
	int				cost_a;  /* Cost to move in stack A */
	int				cost_b;  /* Cost to move in stack B */
	struct s_node	*next;  /* Pointer to next node */
}	t_node;

/* Function prototypes */

/* Stack operations */
t_node	*ft_stack_new(int value);  /* Create new node */
void	ft_stack_add_back(t_node **stack, t_node *new_node);  /* Add node to end */
t_node	*ft_stack_last(t_node *stack);  /* Get last node */
int		ft_stack_size(t_node *stack);  /* Get stack size */
void	ft_stack_clear(t_node **stack);  /* Free stack */

/* Operations on stacks */
void	sa(t_node **stack_a);  /* Swap first two elements of stack A */
void	sb(t_node **stack_b);  /* Swap first two elements of stack B */
void	ss(t_node **stack_a, t_node **stack_b);  /* sa and sb at once */
void	pa(t_node **stack_a, t_node **stack_b);  /* Push from B to A */
void	pb(t_node **stack_a, t_node **stack_b);  /* Push from A to B */
void	ra(t_node **stack_a);  /* Rotate stack A up */
void	rb(t_node **stack_b);  /* Rotate stack B up */
void	rr(t_node **stack_a, t_node **stack_b);  /* ra and rb at once */
void	rra(t_node **stack_a);  /* Rotate stack A down */
void	rrb(t_node **stack_b);  /* Rotate stack B down */
void	rrr(t_node **stack_a, t_node **stack_b);  /* rra and rrb at once */

/* Parsing and validation */
int		ft_parse_args(int argc, char **argv, t_node **stack_a);  /* Parse args */
int		ft_check_duplicates(t_node *stack);  /* Check for duplicates */
int		ft_is_sorted(t_node *stack);  /* Check if stack is sorted */

/* Sorting algorithms */
void	ft_sort(t_node **stack_a, t_node **stack_b);  /* Main sort function */
void	ft_sort_three(t_node **stack_a);  /* Sort three elements */
void	ft_assign_index(t_node *stack_a, int size);  /* Assign index for sorting */

/* Cost calculation */
void	ft_calculate_cost(t_node *stack_a, t_node *stack_b);  /* Calc move costs */
void	ft_find_cheapest(t_node *stack_b, int *cheapest_index);  /* Find best move */
void	ft_execute_cheapest(t_node **stack_a, t_node **stack_b);  /* Execute move */

/* Position and target calculation */
void	ft_assign_position(t_node *stack);  /* Assign current positions */
int		ft_get_target_position(t_node *stack_a, int index_b, int target, int pos);
void	ft_assign_target_position(t_node *stack_a, t_node *stack_b);
int	ft_find_smallest_index(t_node *stack);

/* Utility functions */
int		ft_atoi(const char *str);  /* Convert string to int */
void	ft_putstr_fd(char *str, int fd);  /* Output string to fd */
int		ft_abs(int n);  /* Get absolute value */
int		ft_min(int a, int b);  /* Get minimum of two values */
int		ft_max(int a, int b);  /* Get maximum of two values */

#endif


