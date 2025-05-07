#include "push_swap.h"
/* ************************************************************************** */
/*                           REVERSE ROTATE FUNCTIONS                        */
/* ************************************************************************** */

/*
	Shift down all elements of the stack by 1
	The last element becomes the first one
*/
static void	reverse_rotate(t_stack **stack)
{
	t_stack	*prev;
	t_stack	*last;

	if (!*stack || !(*stack)->next)             /* Nothing to rotate if < 2 elements */
		return ;
	last = *stack;
	while (last->next)                           /* Find last node */
	{
		prev = last;                             /* Save previous */
		last = last->next;
	}
	prev->next = NULL;                           /* Break the link before last */
	last->next = *stack;                         /* Point last to head */
	*stack = last;                               /* Update head to last */
}

/*
	Reverse rotate stack A and print "rra"
*/
void	rra(t_stack **stack_a)
{
	reverse_rotate(stack_a);                    /* Reverse rotate A */
	write(1, "rra\n", 4);                         /* Output operation */
}

/*
	Reverse rotate stack B and print "rrb"
*/
void	rrb(t_stack **stack_b)
{
	reverse_rotate(stack_b);                    /* Reverse rotate B */
	write(1, "rrb\n", 4);                         /* Output operation */
}

/*
	Reverse rotate both stacks and print "rrr"
*/
void	rrr(t_stack **stack_a, t_stack **stack_b)
{
	reverse_rotate(stack_a);                    /* Reverse rotate A */
	reverse_rotate(stack_b);                    /* Reverse rotate B */
	write(1, "rrr\n", 4);                         /* Output operation */
}

