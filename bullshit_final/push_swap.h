#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	int				index;
	int				position;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_node	*next;
}	t_node;

/* Stack operations */
t_node	*new_node(int value);
void	add_node_back(t_node **stack, t_node *new);
t_node	*get_last_node(t_node *stack);
t_node	*get_second_last_node(t_node *stack);
int		stack_size(t_node *stack);
void	free_stack(t_node **stack);
int		is_sorted(t_node *stack);
void	free_and_exit(t_node **stack_a, t_node **stack_b);

/* Swap operations */
void	swap(t_node *stack);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
void	ss(t_node **stack_a, t_node **stack_b);

/* Push operations */
void	push(t_node **src, t_node **dest);
void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);

/* Rotate operations */
void	rotate(t_node **stack);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);

/* Reverse rotate operations */
void	reverse_rotate(t_node **stack);
void	rra(t_node **stack_a);
void	rrb(t_node **stack_b);
void	rrr(t_node **stack_a, t_node **stack_b);

/* Position and cost functions */
void	set_position(t_node **stack);
int		get_lowest_index_position(t_node **stack);
void	set_target_position(t_node **stack_a, t_node **stack_b);
void	calculate_cost(t_node **stack_a, t_node **stack_b);
void	execute_cheapest_move(t_node **stack_a, t_node **stack_b);

/* Movement execution */
void	move_both_stacks(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b);
void	move_stack_a(t_node **stack_a, int *cost);
void	move_stack_b(t_node **stack_b, int *cost);
void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b);

/* Sorting algorithms */
void	sort_three(t_node **stack);
void	sort(t_node **stack_a, t_node **stack_b);
void	shift_stack(t_node **stack_a);

/* Parsing and validation */
int		check_input(int ac, char **av);
int		is_number(char *str);
int		has_duplicates(char **av);
int		is_zero(char *str);
t_node	*parse_input(int ac, char **av);
void	assign_index(t_node *stack_a, int size);

/* Helper functions */
void	print_operation(char *op);
int		absolute_value(int nb);
long	ft_atoi(const char *str);
int		is_digit(char c);
int		is_sign(char c);
int		str_compare(const char *s1, const char *s2);

#endif
