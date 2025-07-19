/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:57:22 by riramana          #+#    #+#             */
/*   Updated: 2025/07/19 20:44:46 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_node *stack)
{
	int	temp;

	if (!stack || !stack->next)
		return ;
	temp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = temp;
	temp = stack->index;
	stack->index = stack->next->index;
	stack->next->index = temp;
}

void	sa(t_node **stack_a)
{
	swap(*stack_a);
	print_operation("sa");
}

void	sb(t_node **stack_b)
{
	swap(*stack_b);
	print_operation("sb");
}

void	ss(t_node **stack_a, t_node **stack_b)
{
	swap(*stack_a);
	swap(*stack_b);
	print_operation("ss");
}
