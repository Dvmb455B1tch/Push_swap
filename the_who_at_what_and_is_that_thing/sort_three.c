/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sorts a stack with exactly 3 elements */
void	sort_three(t_stack **stack_a)
{
	int	first;   /* Value of the first element */
	int	second;  /* Value of the second element */
	int	third;   /* Value of the third element */
	
	if (stack_size(*stack_a) != 3)  /* Check if stack has exactly 3 elements */
		return ;  /* If not, do nothing */
	
	first = (*stack_a)->value;          /* Get value of first element */
	second = (*stack_a)->next->value;   /* Get value of second element */
	third = (*stack_a)->next->next->value;  /* Get value of third element */
	
	if (first > second && second < third && first < third)  /* Case: 2 1 3 */
		sa(stack_a, 1);  /* Swap first two elements */
	else if (first > second && second > third)  /* Case: 3 2 1 */
	{
		sa(stack_a, 1);  /* Swap first two elements */
		rra(stack_a, 1);  /* Reverse rotate once */
	}
	else if (first > second && second < third && first > third)  /* Case: 3 1 2 */
		ra(stack_a, 1);  /* Rotate once */
	else if (first < second && second > third && first < third)  /* Case: 1 3 2 */
	{
		sa(stack_a, 1);  /* Swap first two elements */
		ra(stack_a, 1);  /* Rotate once */
	}
	else if (first < second && second > third && first > third)  /* Case: 2 3 1 */
		rra(stack_a, 1);  /* Reverse rotate once */
	/* Note: Case 1 2 3 is already sorted, so no action needed */
}
