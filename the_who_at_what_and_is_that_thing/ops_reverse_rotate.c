#include "push_swap.h"

/* Reverse rotates stack A: Last element becomes first */
void	rra(t_stack **stack_a, int print)
{
	t_stack	*last;       /* Pointer to last element */
	t_stack	*second_last;  /* Pointer to second-to-last element */
	
	if (!*stack_a || !(*stack_a)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	last = *stack_a;        /* Start from first element */
	second_last = NULL;     /* Initialize second-last as NULL */
	
	while (last->next)  /* Find the last element */
	{
		second_last = last;  /* Keep track of second-last element */
		last = last->next;   /* Move to next element */
	}
	
	second_last->next = NULL;  /* Remove last element from end */
	last->next = *stack_a;     /* Connect last to current first */
	*stack_a = last;           /* Update stack to start from last element */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("rra\n", 1);  /* Output the operation name */
}

/* Reverse rotates stack B: Last element becomes first */
void	rrb(t_stack **stack_b, int print)
{
	t_stack	*last;       /* Pointer to last element */
	t_stack	*second_last;  /* Pointer to second-to-last element */
	
	if (!*stack_b || !(*stack_b)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	last = *stack_b;        /* Start from first element */
	second_last = NULL;     /* Initialize second-last as NULL */
	
	while (last->next)  /* Find the last element */
	{
		second_last = last;  /* Keep track of second-last element */
		last = last->next;   /* Move to next element */
	}
	
	second_last->next = NULL;  /* Remove last element from end */
	last->next = *stack_b;     /* Connect last to current first */
	*stack_b = last;           /* Update stack to start from last element */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("rrb\n", 1);  /* Output the operation name */
}

/* Reverse rotates both stacks: Last element of each becomes first */
void	rrr(t_stack **stack_a, t_stack **stack_b, int print)
{
	rra(stack_a, 0);  /* Reverse rotate stack A without printing */
	rrb(stack_b, 0);  /* Reverse rotate stack B without printing */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("rrr\n", 1);  /* Output the operation name */
}
