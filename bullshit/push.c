
#include "push_swap.h"

/* Push the top element from stack_b to stack_a */
void	pa(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_b;  /* Pointer to top element of stack_b */

	if (!*stack_b)  /* Check if stack_b is empty */
		return ;
	top_b = *stack_b;  /* Store the top element of stack_b */
	*stack_b = (*stack_b)->next;  /* Update stack_b to start with next element */
	top_b->next = *stack_a;  /* Make top_b point to current top of stack_a */
	*stack_a = top_b;  /* Update stack_a to start with top_b */
	ft_putstr_fd("pa\n", 1);  /* Print the operation */
}

/* Push the top element from stack_a to stack_b */
void	pb(t_node **stack_a, t_node **stack_b)
{
	t_node	*top_a;  /* Pointer to top element of stack_a */

	if (!*stack_a)  /* Check if stack_a is empty */
		return ;
	top_a = *stack_a;  /* Store the top element of stack_a */
	*stack_a = (*stack_a)->next;  /* Update stack_a to start with next element */
	top_a->next = *stack_b;  /* Make top_a point to current top of stack_b */
	*stack_b = top_a;  /* Update stack_b to start with top_a */
	ft_putstr_fd("pb\n", 1);  /* Print the operation */
}


