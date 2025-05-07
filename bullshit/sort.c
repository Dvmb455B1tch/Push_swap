#include "push_swap.h"

/* Compare values for sorting */
static int	ft_compare_values(int a, int b, int c)
{
	if (a > b && a > c)  /* a is largest */
		return (a);
	else if (b > a && b > c)  /* b is largest */
		return (b);
	else  /* c is largest */
		return (c);
}

/* Sort three elements */
void	ft_sort_three(t_node **stack_a)
{
	int	largest;  /* Largest value in the stack */

	if (ft_is_sorted(*stack_a))  /* Check if already sorted */
		return ;
	
	largest = ft_compare_values((*stack_a)->value, 
							(*stack_a)->next->value, 
							(*stack_a)->next->next->value);  /* Find largest */
	
	if ((*stack_a)->value == largest)  /* Largest at top */
		ra(stack_a);  /* Rotate to move largest to bottom */
	else if ((*stack_a)->next->value == largest)  /* Largest in middle */
		rra(stack_a);  /* Reverse rotate to move largest to bottom */
	
	if ((*stack_a)->value > (*stack_a)->next->value)  /* Check if first two are in order */
		sa(stack_a);  /* Swap first two elements */
}

/* Assign index to each node based on its value's rank */
void	ft_assign_index(t_node *stack_a, int size)
{
	t_node	*current;  /* Current node being processed */
	t_node	*highest;  /* Node with highest value */
	int		value;  /* Current highest value */
	int		index;  /* Current index being assigned */

	index = size;  /* Start with highest index */
	while (--index >= 0)  /* Process all indices */
	{
		current = stack_a;  /* Start with first node */
		value = -2147483648;  /* Initialize with min int */
		highest = NULL;  /* Reset highest node */
		while (current)  /* Process all nodes */
		{
			if (current->value > value && current->index == 0)
			{
				value = current->value;  /* Update highest value */
				highest = current;  /* Update highest node */
			}
			current = current->next;  /* Move to next node */
		}
		if (highest)  /* Check if a node was found */
			highest->index = index;  /* Assign index */
	}
}

/* Check if stack_a is in position for final rotations */
static int	ft_is_position_correct(t_node *stack_a)
{
	int		min_pos;  /* Position of minimum element */
	int		min_index;  /* Minimum index */
	t_node	*current;  /* Current node being checked */

	min_pos = 0;  /* Initialize position */
	min_index = ft_find_smallest_index(stack_a);  /* Find smallest index */
	current = stack_a;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		if (current->index == min_index)  /* Check if smallest */
			break ;  /* Exit loop */
		min_pos++;  /* Increment position */
		current = current->next;  /* Move to next node */
	}
	return (min_pos);  /* Return position of smallest element */
}

/* Main sorting function using Turk algorithm */
void	ft_sort(t_node **stack_a, t_node **stack_b)
{
	int	size;  /* Size of stack_a */
	int	min_pos;  /* Position of minimum element */

	size = ft_stack_size(*stack_a);  /* Get size of stack_a */
	
	/* If only 2 elements, swap if needed */
	if (size == 2 && !ft_is_sorted(*stack_a))
		sa(stack_a);  /* Swap first two elements */
	/* If 3 elements, use specialized sort */
	else if (size == 3)
		ft_sort_three(stack_a);  /* Sort three elements */
	/* For larger stacks, use Turk algorithm */
	else if (size > 3)
	{
		/* Push all but 3 elements to stack_b */
		while (ft_stack_size(*stack_a) > 3)
			pb(stack_a, stack_b);  /* Push from A to B */
		
		ft_sort_three(stack_a);  /* Sort remaining three elements */
		
		/* Push back elements from stack_b to stack_a in optimal order */
		while (*stack_b)
		{
			ft_assign_target_position(*stack_a, *stack_b);  /* Calculate targets */
			ft_calculate_cost(*stack_a, *stack_b);  /* Calculate costs */
			ft_execute_cheapest(stack_a, stack_b);  /* Execute cheapest move */
		}
		
		/* Final rotation to position smallest element at top */
		ft_assign_position(*stack_a);  /* Update positions */
		min_pos = ft_is_position_correct(*stack_a);  /* Get position of smallest */
		size = ft_stack_size(*stack_a);  /* Get updated size */
		
		/* Choose optimal rotation direction */
		if (min_pos <= size / 2)
		{
			while (min_pos-- > 0)
				ra(stack_a);  /* Rotate up */
		}
		else
		{
			while (min_pos++ < size)
				rra(stack_a);  /* Rotate down */
		}
	}
}

