#include "push_swap.h"

/* Rotates stack A: First element becomes last */
void	ra(t_stack **stack_a, int print)
{
	t_stack	*first;  /* Pointer to the first element */
	t_stack	*last;   /* Pointer to the last element */
	
	if (!*stack_a || !(*stack_a)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	first = *stack_a;        /* Store the first element */
	*stack_a = first->next;  /* Update stack to start from second element */
	
	last = first;  /* Initialize last as the current first */
	while (last->next)  /* Find the last element */
		last = last->next;
	
	last->next = first;  /* Connect last to first, making first the new last */
	first->next = NULL;  /* Set next of new last to NULL */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("ra\n", 1);  /* Output the operation name */
}

/* Rotates stack B: First element becomes last */
void	rb(t_stack **stack_b, int print)
{
	t_stack	*first;  /* Pointer to the first element */
	t_stack	*last;   /* Pointer to the last element */
	
	if (!*stack_b || !(*stack_b)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	first = *stack_b;        /* Store the first element */
	*stack_b = first->next;  /* Update stack to start from second element */
	
	last = first;  /* Initialize last as the current first */
	while (last->next)  /* Find the last element */
		last = last->next;
	
	last->next = first;  /* Connect last to first, making first the new last */
	first->next = NULL;  /* Set next of new last to NULL */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("rb\n", 1);  /* Output the operation name */
}

/* Rotates both stacks: First element of each becomes last */
void	rr(t_stack **stack_a, t_stack **stack_b, int print)
{
	ra(stack_a, 0);  /* Rotate stack A without printing */
	rb(stack_b, 0);  /* Rotate stack B without printing */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("rr\n", 1);  /* Output the operation name */
}
