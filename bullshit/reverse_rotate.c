
#include "push_swap.h"

/* Reverse rotate stack_a - last element becomes first */
void	rra(t_node **stack_a)
{
	t_node	*last;  /* Pointer to last node */
	t_node	*prev;  /* Pointer to second-last node */
	t_node	*current;  /* Pointer to traverse the list */

	if (!*stack_a || !(*stack_a)->next)  /* Check if enough elements exist */
		return ;
	current = *stack_a;  /* Start from the first element */
	while (current->next->next)  /* Find the second-last element */
		current = current->next;
	prev = current;  /* Store the second-last element */
	last = prev->next;  /* Store the last element */
	prev->next = NULL;  /* Second-last now points to NULL */
	last->next = *stack_a;  /* Last now points to first */
	*stack_a = last;  /* Update stack_a to start with last */
	ft_putstr_fd("rra\n", 1);  /* Print the operation */
}

/* Reverse rotate stack_b - last element becomes first */
void	rrb(t_node **stack_b)
{
	t_node	*last;  /* Pointer to last node */
	t_node	*prev;  /* Pointer to second-last node */
	t_node	*current;  /* Pointer to traverse the list */

	if (!*stack_b || !(*stack_b)->next)  /* Check if enough elements exist */
		return ;
	current = *stack_b;  /* Start from the first element */
	while (current->next->next)  /* Find the second-last element */
		current = current->next;
	prev = current;  /* Store the second-last element */
	last = prev->next;  /* Store the last element */
	prev->next = NULL;  /* Second-last now points to NULL */
	last->next = *stack_b;  /* Last now points to first */
	*stack_b = last;  /* Update stack_b to start with last */
	ft_putstr_fd("rrb\n", 1);  /* Print the operation */
}

/* Reverse rotate both stack_a and stack_b */
void	rrr(t_node **stack_a, t_node **stack_b)
{
	t_node	*last_a;  /* Pointer to last node of stack_a */
	t_node	*prev_a;  /* Pointer to second-last node of stack_a */
	t_node	*curr_a;  /* Pointer to traverse stack_a */
	t_node	*last_b;  /* Pointer to last node of stack_b */
	t_node	*prev_b;  /* Pointer to second-last node of stack_b */
	t_node	*curr_b;  /* Pointer to traverse stack_b */

	if ((!*stack_a || !(*stack_a)->next) || (!*stack_b || !(*stack_b)->next))
		return ;  /* Return if either stack doesn't have enough elements */
	
	/* Process stack_a */
	curr_a = *stack_a;  /* Start from the first element of stack_a */
	while (curr_a->next->next)  /* Find the second-last element */
		curr_a = curr_a->next;
	prev_a = curr_a;  /* Store the second-last element */
	last_a = prev_a->next;  /* Store the last element */
	prev_a->next = NULL;  /* Second-last now points to NULL */
	last_a->next = *stack_a;  /* Last now points to first */
	*stack_a = last_a;  /* Update stack_a to start with last */
	
	/* Process stack_b */
	curr_b = *stack_b;  /* Start from the first element of stack_b */
	while (curr_b->next->next)  /* Find the second-last element */
		curr_b = curr_b->next;
	prev_b = curr_b;  /* Store the second-last element */
	last_b = prev_b->next;  /* Store the last element */
	prev_b->next = NULL;  /* Second-last now points to NULL */
	last_b->next = *stack_b;  /* Last now points to first */
	*stack_b = last_b;  /* Update stack_b to start with last */
	
	ft_putstr_fd("rrr\n", 1);  /* Print the operation */
}


