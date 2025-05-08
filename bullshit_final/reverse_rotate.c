#include "push_swap.h"
/**
 * Reverse rotate a stack - bottom element becomes the top element
 */
void	reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*second_last;

	if (!*stack || !(*stack)->next)
		return ;
	last = get_last_node(*stack);
	second_last = get_second_last_node(*stack);
	last->next = *stack;
	*stack = last;
	second_last->next = NULL;
}

/**
 * Reverse rotate stack A
 */
void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);
	print_operation("rra");
}

/**
 * Reverse rotate stack B
 */
void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);
	print_operation("rrb");
}

/**
 * Reverse rotate both stacks
 */
void	rrr(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	print_operation("rrr");
}
