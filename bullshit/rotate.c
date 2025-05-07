
#include "push_swap.h"

/* Rotate stack_a up - first element becomes last */
void	ra(t_node **stack_a)
{
	t_node	*first;  /* Pointer to first node */
	t_node	*last;   /* Pointer to last node */

	if (!*stack_a || !(*stack_a)->next)  /* Check if enough elements exist */
		return ;
	first = *stack_a;  /* Store the first element */
	last = ft_stack_last(*stack_a);  /* Find the last element */
	*stack_a = first->next;  /* Update stack_a to start with second element */
	first->next = NULL;  /* First element now points to NULL */
	last->next = first;  /* Last element now points to first */
	ft_putstr_fd("ra\n", 1);  /* Print the operation */
}

/* Rotate stack_b up - first element becomes last */
void	rb(t_node **stack_b)
{
	t_node	*first;  /* Pointer to first node */
	t_node	*last;   /* Pointer to last node */

	if (!*stack_b || !(*stack_b)->next)  /* Check if enough elements exist */
		return ;
	first = *stack_b;  /* Store the first element */
	last = ft_stack_last(*stack_b);  /* Find the last element */
	*stack_b = first->next;  /* Update stack_b to start with second element */
	first->next = NULL;  /* First element now points to NULL */
	last->next = first;  /* Last element now points to first */
	ft_putstr_fd("rb\n", 1);  /* Print the operation */
}

/* Rotate both stack_a and stack_b up */
void	rr(t_node **stack_a, t_node **stack_b)
{
	t_node	*first_a;  /* Pointer to first node of stack_a */
	t_node	*last_a;   /* Pointer to last node of stack_a */
	t_node	*first_b;  /* Pointer to first node of stack_b */
	t_node	*last_b;   /* Pointer to last node of stack_b */

	if ((!*stack_a || !(*stack_a)->next) || (!*stack_b || !(*stack_b)->next))
		return ;  /* Return if either stack doesn't have enough elements */
	
	/* Process stack_a */
	first_a = *stack_a;  /* Store the first element of stack_a */
	last_a = ft_stack_last(*stack_a);  /* Find the last element of stack_a */
	*stack_a = first_a->next;  /* Update stack_a to start with second element */
	first_a->next = NULL;  /* First element now points to NULL */
	last_a->next = first_a;  /* Last element now points to first */
	
	/* Process stack_b */
	first_b = *stack_b;  /* Store the first element of stack_b */
	last_b = ft_stack_last(*stack_b);  /* Find the last element of stack_b */
	*stack_b = first_b->next;  /* Update stack_b to start with second element */
	first_b->next = NULL;  /* First element now points to NULL */
	last_b->next = first_b;  /* Last element now points to first */
	
	ft_putstr_fd("rr\n", 1);  /* Print the operation */
}


