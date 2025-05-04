/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Finds the position of the smallest element in the stack */
static int	find_min_position(t_stack *stack)
{
	int	min;      /* Minimum value found */
	int	position;  /* Position of the minimum value */
	int	i;        /* Current position being checked */
	
	min = stack->value;  /* Initialize min to first value */
	position = 0;  /* Position of min starts at 0 */
	i = 0;  /* Start at position 0 */
	
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->value < min)  /* If current value is smaller than min */
		{
			min = stack->value;  /* Update minimum value */
			position = i;  /* Update position of minimum */
		}
		stack = stack->next;  /* Move to next node */
		i++;  /* Increment position counter */
	}
	
	return (position);  /* Return position of the minimum value */
}

/* Sort stack with 2 elements */
static void	sort_two(t_stack **stack_a)
{
	if ((*stack_a)->value > (*stack_a)->next->value)  /* If first > second */
		sa(stack_a, 1);  /* Swap the two elements */
}

/* Sorts stack with 4 elements */
static void	sort_four(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;  /* Position of smallest element */
	
	min_pos = find_min_position(*stack_a);  /* Find position of smallest element */
	
	if (min_pos == 1)  /* If minimum is at second position */
		ra(stack_a, 1);  /* Rotate once to bring it to top */
	else if (min_pos == 2)  /* If minimum is at third position */
	{
		ra(stack_a, 1);  /* Rotate once */
		ra(stack_a, 1);  /* Rotate twice to bring it to top */
	}
	else if (min_pos == 3)  /* If minimum is at bottom */
		rra(stack_a, 1);  /* Reverse rotate to bring it to top */
	
	pb(stack_a, stack_b, 1);  /* Push minimum to stack B */
	sort_three(stack_a);  /* Sort remaining three elements */
	pa(stack_a, stack_b, 1);  /* Push minimum back to stack A */
}

/* Sorts stack with 5 elements */
static void	sort_five(t_stack **stack_a, t_stack **stack_b)
{
	int	min_pos;  /* Position of smallest element */
	
	min_pos = find_min_position(*stack_a);  /* Find position of smallest element */
	
	if (min_pos == 1)  /* If minimum is at second position */
		ra(stack_a, 1);  /* Rotate once to bring it to top */
	else if (min_pos == 2)  /* If minimum is at third position */
	{
		ra(stack_a, 1);  /* Rotate once */
		ra(stack_a, 1);  /* Rotate twice to bring it to top */
	}
	else if (min_pos == 3)  /* If minimum is at fourth position */
	{
		rra(stack_a, 1);  /* Reverse rotate once */
		rra(stack_a, 1);  /* Reverse rotate twice to bring it to top */
	}
	else if (min_pos == 4)  /* If minimum is at bottom */
		rra(stack_a, 1);  /* Reverse rotate once to bring it to top */
	
	pb(stack_a, stack_b, 1);  /* Push minimum to stack B */
	sort_four(stack_a, stack_b);  /* Sort remaining four elements */
	pa(stack_a, stack_b, 1);  /* Push minimum back to stack A */
}

/* Main function to sort small stacks (2-5 elements) */
void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;  /* Size of stack A */
	
	size = stack_size(*stack_a);  /* Get the number of elements in stack */
	
	if (size == 2)  /* If stack has 2 elements */
		sort_two(stack_a);  /* Sort a stack of 2 */
	else if (size == 3)  /* If stack has 3 elements */
		sort_three(stack_a);  /* Sort a stack of 3 */
	else if (size == 4)  /* If stack has 4 elements */
		sort_four(stack_a, stack_b);  /* Sort a stack of 4 */
	else if (size == 5)  /* If stack has 5 elements */
		sort_five(stack_a, stack_b);  /* Sort a stack of 5 */
}
