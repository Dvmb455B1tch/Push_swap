#include "push_swap.h"

/*
** ra - Rotate stack A upwards (first element becomes last)
*/
void	ra(t_node **stack_a)
{
	t_node	*first;
	t_node	*last;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;

	first = *stack_a;            // Save current top
	*stack_a = first->next;      // New top is second element

	last = *stack_a;
	while (last->next)           // Find the last node
		last = last->next;

	last->next = first;          // Link last to former first
	first->next = NULL;          // End list properly
}

/*
** rb - Rotate stack B upwards
*/
void	rb(t_node **stack_b)
{
	t_node	*first;
	t_node	*last;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;

	first = *stack_b;
	*stack_b = first->next;

	last = *stack_b;
	while (last->next)
		last = last->next;

	last->next = first;
	first->next = NULL;
}

/*
** rr - Rotate both stacks upwards
*/
void	rr(t_node **stack_a, t_node **stack_b)
{
	ra(stack_a);
	rb(stack_b);
}

