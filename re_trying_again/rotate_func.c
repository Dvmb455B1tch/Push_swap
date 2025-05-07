#include "push_swap.h"
/* ************************************************************************** */
/*                              ROTATE FUNCTIONS                             */
/* ************************************************************************** */

/*
	Shift up all elements of the stack by 1
	The first element becomes the last one
*/
static void	rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!*stack || !(*stack)->next)             /* Nothing to rotate if < 2 elements */
		return ;
	first = *stack;                              /* Save first element */
	*stack = first->next;                        /* Move head to second element */
	last = *stack;
	while (last->next)                           /* Go to last node */
		last = last->next;
	last->next = first;                          /* Append first to end */
	first->next = NULL;                          /* First becomes last */
}

/*
	Rotate stack A and print "ra"
*/
void	ra(t_stack **stack_a)
{
	rotate(stack_a);                             /* Rotate A */
	write(1, "ra\n", 3);                          /* Output operation */
}

/*
	Rotate stack B and print "rb"
*/
void	rb(t_stack **stack_b)
{
	rotate(stack_b);                             /* Rotate B */
	write(1, "rb\n", 3);                          /* Output operation */
}

/*
	Rotate both A and B and print "rr"
*/
void	rr(t_stack **stack_a, t_stack **stack_b)
{
	rotate(stack_a);                             /* Rotate A */
	rotate(stack_b);                             /* Rotate B */
	write(1, "rr\n", 3);                          /* Output operation */
}
