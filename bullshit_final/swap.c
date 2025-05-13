#include "push_swap.h"
/**
 * Swap the top two elements of a stack
 */
void	swap(t_node *stack)
{
	int	temp;

	if (!stack || !stack->next)
		return ;
	temp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = temp;
	
	temp = stack->index;
	stack->index = stack->next->index;
	stack->next->index = temp;
}

/**
 * Swap the top two elements of stack A
 */
void	sa(t_node **stack_a)
{
	swap(*stack_a);
	print_operation("sa");
}
/**
 * Swap the top two elements of stack B
 */
void	sb(t_node **stack_b)
{
	swap(*stack_b);
	print_operation("sb");
}
/**
 * Swap the top two elements of both stacks
 */
void	ss(t_node **stack_a, t_node **stack_b)
{
	swap(*stack_a);
	swap(*stack_b);
	print_operation("ss");
}
