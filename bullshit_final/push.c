#include "push_swap.h"
/**
 * Push the top element from src stack to dest stack
 */
void	push(t_node **src, t_node **dest)
{
	t_node	*temp;

	if (!*src)
		return ;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}
/**
 * Push the top element from stack B to stack A
 */
void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);
	print_operation("pa");
}
/**
 * Push the top element from stack A to stack B
 */
void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);
	print_operation("pb");
}
