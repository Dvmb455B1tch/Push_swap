/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:05:04 by riramana          #+#    #+#             */
/*   Updated: 2025/05/13 14:10:06 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_node **src, t_node **dest)
{
	t_node	*temp;

	if (!*src)
		return ;
	temp = *src;
	*src = (*src)->next;
	temp->next = *dest;
	*dest = temp;
}

void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);
	print_operation("pa");
}

void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);
	print_operation("pb");
}
