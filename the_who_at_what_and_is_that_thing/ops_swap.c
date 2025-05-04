/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swaps the first two elements of stack A */
void	sa(t_stack **stack_a, int print)
{
	t_stack	*first;   /* Pointer to first element */
	t_stack	*second;  /* Pointer to second element */
	
	if (!*stack_a || !(*stack_a)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	first = *stack_a;  /* Store pointer to first element */
	second = first->next;  /* Store pointer to second element */
	
	first->next = second->next;  /* Connect first to third element */
	second->next = first;        /* Connect second to first element */
	*stack_a = second;           /* Update stack pointer to new first element */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("sa\n", 1);  /* Output the operation name */
}

/* Swaps the first two elements of stack B */
void	sb(t_stack **stack_b, int print)
{
	t_stack	*first;   /* Pointer to first element */
	t_stack	*second;  /* Pointer to second element */
	
	if (!*stack_b || !(*stack_b)->next)  /* Check if stack has < 2 elements */
		return ;  /* If so, do nothing */
	
	first = *stack_b;  /* Store pointer to first element */
	second = first->next;  /* Store pointer to second element */
	
	first->next = second->next;  /* Connect first to third element */
	second->next = first;        /* Connect second to first element */
	*stack_b = second;           /* Update stack pointer to new first element */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("sb\n", 1);  /* Output the operation name */
}

/* Swaps the first two elements of both stacks */
void	ss(t_stack **stack_a, t_stack **stack_b, int print)
{
	sa(stack_a, 0);  /* Swap stack A without printing */
	sb(stack_b, 0);  /* Swap stack B without printing */
	
	if (print)  /* If print flag is set */
		ft_putstr_fd("ss\n", 1);  /* Output the operation name */
}
