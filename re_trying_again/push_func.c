#include "push_swap.h"
/* ************************************************************************** */
/*                               PUSH FUNCTIONS                              */
/* ************************************************************************** */

/*
	Push the top element from source to destination stack
*/
static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*top;

	if (!*src)                                   /* No element to push */
		return ;
	top = *src;                                  /* Take top of source */
	*src = (*src)->next;                         /* Move source head down */
	top->next = *dest;                           /* Link pushed element to destination */
	*dest = top;                                 /* Update dest head */
}

/*
	Push top of stack B to stack A and print "pa"
*/
void	pa(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_b, stack_a);                     /* Push from B to A */
	write(1, "pa\n", 3);                         /* Output operation */
}

/*
	Push top of stack A to stack B and print "pb"
*/
void	pb(t_stack **stack_a, t_stack **stack_b)
{
	push(stack_a, stack_b);                     /* Push from A to B */
	write(1, "pb\n", 3);                         /* Output operation */
}


