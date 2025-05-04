#include "push_swap.h"

/* Takes the first element from stack B and puts it at the top of stack A */
void	pa(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;  /* Temporary pointer to hold the node to move */
	
	if (!*stack_b)  /* Check if stack B is empty */
		return ;    /* If empty, do nothing */
	
	temp = pop_front(stack_b);  /* Remove top element from stack B */
	push_front(stack_a, temp);  /* Add that element to the top of stack A */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("pa\n", 1);  /* Output the operation name */
}

/* Takes the first element from stack A and puts it at the top of stack B */
void	pb(t_stack **stack_a, t_stack **stack_b, int print)
{
	t_stack	*temp;  /* Temporary pointer to hold the node to move */
	
	if (!*stack_a)  /* Check if stack A is empty */
		return ;    /* If empty, do nothing */
	
	temp = pop_front(stack_a);  /* Remove top element from stack A */
	push_front(stack_b, temp);  /* Add that element to the top of stack B */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("pb\n", 1);  /* Output the operation name */
}
