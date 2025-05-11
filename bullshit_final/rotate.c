#include "push_swap.h"
/**
 * Rotate a stack - top element becomes the bottom element
 */
void	rotate(t_node **stack)
{
	t_node	*temp;
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	temp = *stack;
	*stack = (*stack)->next;
	last = get_last_node(*stack);
	temp->next = NULL;
	last->next = temp;
}
/**
 * Rotate stack A
 */
void	ra(t_node **stack_a)
{
	rotate(stack_a);
	print_operation("ra");
}
/**
 * Rotate stack B
 */
void	rb(t_node **stack_b)
{
	rotate(stack_b);
	print_operation("rb");
}
/**
 * Rotate both stacks
 */
void	rr(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	print_operation("rr");
}
