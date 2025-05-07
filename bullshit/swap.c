
#include "push_swap.h"

/* Swaps the first two elements at the top of stack_a */
void	sa(t_node **stack_a)
{
	t_node	*first;  /* Pointer to first node */
	t_node	*second;  /* Pointer to second node */

	if (!*stack_a || !(*stack_a)->next)  /* Check if enough elements exist */
		return ;
	first = *stack_a;  /* Store the first element */
	second = (*stack_a)->next;  /* Store the second element */
	first->next = second->next;  /* First now points to third */
	second->next = first;  /* Second now points to first */
	*stack_a = second;  /* Update stack_a to start with second */
	ft_putstr_fd("sa\n", 1);  /* Print the operation */
}

/* Swaps the first two elements at the top of stack_b */
void	sb(t_node **stack_b)
{
	t_node	*first;  /* Pointer to first node */
	t_node	*second;  /* Pointer to second node */

	if (!*stack_b || !(*stack_b)->next)  /* Check if enough elements exist */
		return ;
	first = *stack_b;  /* Store the first element */
	second = (*stack_b)->next;  /* Store the second element */
	first->next = second->next;  /* First now points to third */
	second->next = first;  /* Second now points to first */
	*stack_b = second;  /* Update stack_b to start with second */
	ft_putstr_fd("sb\n", 1);  /* Print the operation */
}

/* Swaps the first two elements of both stack_a and stack_b */
void	ss(t_node **stack_a, t_node **stack_b)
{
	t_node	*first_a;  /* Pointer to first node of stack_a */
	t_node	*second_a;  /* Pointer to second node of stack_a */
	t_node	*first_b;  /* Pointer to first node of stack_b */
	t_node	*second_b;  /* Pointer to second node of stack_b */

	if ((!*stack_a || !(*stack_a)->next) || (!*stack_b || !(*stack_b)->next))
		return ;  /* Return if either stack doesn't have enough elements */
	
	/* Process stack_a */
	first_a = *stack_a;  /* Store the first element of stack_a */
	second_a = (*stack_a)->next;  /* Store the second element of stack_a */
	first_a->next = second_a->next;  /* First now points to third */
	second_a->next = first_a;  /* Second now points to first */
	*stack_a = second_a;  /* Update stack_a to start with second */
	
	/* Process stack_b */
	first_b = *stack_b;  /* Store the first element of stack_b */
	second_b = (*stack_b)->next;  /* Store the second element of stack_b */
	first_b->next = second_b->next;  /* First now points to third */
	second_b->next = first_b;  /* Second now points to first */
	*stack_b = second_b;  /* Update stack_b to start with second */
	
	ft_putstr_fd("ss\n", 1);  /* Print the operation */
}


