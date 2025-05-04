/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;  /* Stack A for push_swap operations */
	t_stack	*stack_b;  /* Stack B for push_swap operations */

	stack_a = NULL;     /* Initialize stack A as empty */
	stack_b = NULL;     /* Initialize stack B as empty */
	
	if (argc < 2)       /* Check if we have any arguments */
		return (0);     /* If no arguments, exit peacefully */
	
	parse_arguments(argc, argv, &stack_a);  /* Parse command line arguments */
	
	if (stack_is_sorted(stack_a))  /* Check if stack is already sorted */
	{
		free_stack(&stack_a);      /* Free stack memory before exit */
		return (0);                /* Exit if already sorted */
	}
	
	assign_indexes(&stack_a);      /* Assign indexes for sorting optimization */
	sort_stacks(&stack_a, &stack_b);  /* Execute sorting algorithm */
	
	free_stack(&stack_a);          /* Free stack A memory */
	free_stack(&stack_b);          /* Free stack B memory */
	return (0);                    /* Exit successfully */
}
