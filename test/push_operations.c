#include "push_swap.h"

//pa - Push the top element from stack B to stack A

void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*temp;

	if (!stack_b || !*stack_b)
		return ;

	temp = *stack_b;           // Store top of stack B
	*stack_b = temp->next;     // Advance B to next node

	temp->next = *stack_a;     // Point pushed node to current top of A
	*stack_a = temp;           // Set A's top to pushed node
}

/*
** pb - Push the top element from stack A to stack B
*/
void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*temp;

	if (!stack_a || !*stack_a)
		return ;

	temp = *stack_a;
	*stack_a = temp->next;

	temp->next = *stack_b;
	*stack_b = temp;
}

