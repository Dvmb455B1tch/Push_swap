/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:19:15 by riramana          #+#    #+#             */
/*   Updated: 2025/07/19 20:44:18 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_node **stack)
{
	t_node	*last;
	t_node	*second_last;

	if (!*stack || !(*stack)->next)
		return ;
	last = get_last_node(*stack);
	second_last = get_second_last_node(*stack);
	last->next = *stack;
	*stack = last;
	second_last->next = NULL;
}

void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);
	print_operation("rra");
}

void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);
	print_operation("rrb");
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	print_operation("rrr");
}
