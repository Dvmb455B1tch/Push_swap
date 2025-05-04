#include "push_swap.h"

/* Main sorting function that delegates to appropriate sorting algorithm based on size */
void	sort_stacks(t_stack **stack_a, t_stack **stack_b)
{
	int	size;  /* Size of stack A */
	
	size = stack_size(*stack_a);  /* Get number of elements in stack A */
	
	if (size <= 1)  /* If stack has 0 or 1 element */
		return ;  /* Already sorted, do nothing */
	else if (size <= 5)  /* If stack has 2-5 elements */
		sort_small(stack_a, stack_b);  /* Use specialized small stack sorting */
	else  /* If stack has more than 5 elements */
		sort_large(stack_a, stack_b);  /* Use algorithm for large stacks */
}
