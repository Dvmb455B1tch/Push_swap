/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:14:14 by riramana          #+#    #+#             */
/*   Updated: 2025/07/19 20:44:29 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_node **stack)
{
	int	highest_index;

	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	if (is_sorted(*stack))
		return ;
	highest_index = (*stack)->index;
	if ((*stack)->next->index > highest_index)
		highest_index = (*stack)->next->index;
	if ((*stack)->next->next->index > highest_index)
		highest_index = (*stack)->next->next->index;
	if ((*stack)->index == highest_index)
		ra(stack);
	else if ((*stack)->next->index == highest_index)
		rra(stack);
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}

static void	push_all_except_three(t_node **stack_a, t_node **stack_b)
{
	int	size;
	int	pushed;
	int	i;

	size = stack_size(*stack_a);
	if (size <= 3)
		return ;
	pushed = 0;
	i = 0;
	while (size > 6 && i < size && pushed < size / 2)
	{
		if ((*stack_a)->index <= size / 2)
		{
			pb(stack_a, stack_b);
			pushed++;
		}
		else
			ra(stack_a);
		i++;
	}
	while (size - pushed > 3)
	{
		pb(stack_a, stack_b);
		pushed++;
	}
}

void	shift_stack(t_node **stack_a)
{
	int	lowest_pos;
	int	size;

	if (!stack_a || !*stack_a)
		return ;
	size = stack_size(*stack_a);
	lowest_pos = get_lowest_index_position(stack_a);
	if (lowest_pos > size / 2)
	{
		while (lowest_pos < size)
		{
			rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		while (lowest_pos > 0)
		{
			ra(stack_a);
			lowest_pos--;
		}
	}
}

void	sort(t_node **stack_a, t_node **stack_b)
{
	if (!stack_a || !*stack_a)
		return ;
	if (is_sorted(*stack_a))
		return ;
	if (stack_size(*stack_a) == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
		return ;
	}
	if (stack_size(*stack_a) == 3)
	{
		sort_three(stack_a);
		return ;
	}
	push_all_except_three(stack_a, stack_b);
	sort_three(stack_a);
	while (*stack_b)
	{
		set_target_position(stack_a, stack_b);
		calculate_cost(stack_a, stack_b);
		execute_cheapest_move(stack_a, stack_b);
	}
	if (!is_sorted(*stack_a))
		shift_stack(stack_a);
}
