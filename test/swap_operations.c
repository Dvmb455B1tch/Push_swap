#include "push_swap.h"

//sa - Swap the first two elements of stack A

void	sa(t_node **stack_a)
{
	t_node	*first;
	t_node	*second;

	// Check if the stack exists and has at least 2 elements
	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;

	first = *stack_a;              // First node (top of stack)
	second = first->next;          // Second node

	first->next = second->next;    // Point first to the third element (can be NULL)
	second->next = first;          // Second now points to first
	*stack_a = second;             // Second becomes the new head (top of stack)
}

/*
** sb - Swap the first two elements of stack B
*/
void	sb(t_node **stack_b)
{
	t_node	*first;
	t_node	*second;

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;

	first = *stack_b;
	second = first->next;

	first->next = second->next;
	second->next = first;
	*stack_b = second;
}

/*
** ss - Swap the first two elements of both stacks A and B
*/
void	ss(t_node **stack_a, t_node **stack_b)
{
	// Swap A and B simultaneously
	sa(stack_a);
	sb(stack_b);
}

