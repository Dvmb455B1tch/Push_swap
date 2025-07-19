/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:10:45 by riramana          #+#    #+#             */
/*   Updated: 2025/07/18 14:21:14 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_node **stack)
{
	t_node	*temp;
	t_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	temp = *stack;
	*stack = (*stack)->next;
	last = get_last_node(*stack);
	temp->next = NULL;
	last->next = temp;
}

void	ra(t_node **stack_a)
{
	rotate(stack_a);
	print_operation("ra");
}

void	rb(t_node **stack_b)
{
	rotate(stack_b);
	print_operation("rb");
}

void	rr(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	print_operation("rr");
}
