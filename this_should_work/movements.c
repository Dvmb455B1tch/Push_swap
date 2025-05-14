/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:33:49 by riramana          #+#    #+#             */
/*   Updated: 2025/05/14 11:34:37 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	execute_reverse_rotate_both(t_node **stack_a, t_node **stack_b,
		int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(stack_a, stack_b);
	}
}

static void	execute_rotate_both(t_node **stack_a, t_node **stack_b,
		int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(stack_a, stack_b);
	}
}

void	move_stack_a(t_node **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(stack_a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rra(stack_a);
			(*cost)++;
		}
	}
}

void	move_stack_b(t_node **stack_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(stack_b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rrb(stack_b);
			(*cost)++;
		}
	}
}

void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		execute_reverse_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		execute_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	move_stack_a(stack_a, &cost_a);
	move_stack_b(stack_b, &cost_b);
	pa(stack_a, stack_b);
}
