/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Checks if a string is a valid number (integer) */
int	is_number(char *str)
{
	int	i;  /* Index for traversing the string */
	
	i = 0;  /* Start at beginning of string */
	if (str[i] == '-' || str[i] == '+')  /* Handle sign if present */
		i++;  /* Move past sign character */
	
	if (!str[i])  /* Check if only a sign was provided */
		return (0);  /* Not a valid number, return false */
	
	while (str[i])  /* Process all characters in string */
	{
		if (str[i] < '0' || str[i] > '9')  /* Check if character is not a digit */
			return (0);  /* Not a valid number, return false */
		i++;  /* Move to next character */
	}
	
	return (1);  /* Valid number, return true */
}

/* Checks if a value already exists in the stack (duplicate check) */
int	is_duplicate(t_stack *stack, int value)
{
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->value == value)  /* Check if current node's value matches */
			return (1);  /* Duplicate found, return true */
		stack = stack->next;  /* Move to next node */
	}
	
	return (0);  /* No duplicate found, return false */
}

/* Displays error message and exits the program */
void	error_exit(t_stack **stack_a, t_stack **stack_b)
{
	if (stack_a)  /* If stack A exists */
		free_stack(stack_a);  /* Free all memory allocated for stack A */
	
	if (stack_b)  /* If stack B exists */
		free_stack(stack_b);  /* Free all memory allocated for stack B */
	
	ft_putstr_fd("Error\n", 2);  /* Output error message to stderr */
	exit(1);  /* Exit with error code */
}

/* Parses the command line arguments and builds stack A */
void	parse_arguments(int argc, char **argv, t_stack **stack_a)
{
	int		i;        /* Loop counter for arguments */
	long	value;    /* Value to store after conversion */
	t_stack	*new_node;  /* Pointer for each new node */
	t_stack	*last;      /* Pointer to the last node in stack */
	
	i = 1;  /* Start with first argument (skip program name) */
	last = NULL;  /* Initialize last pointer as NULL */
	
	while (i < argc)  /* Process all arguments */
	{
		if (!is_number(argv[i]))  /* Check if argument is a valid number */
			error_exit(stack_a, NULL);  /* If not, exit with error */
		
		value = ft_atol(argv[i]);  /* Convert string to long integer */
		
		if (value > INT_MAX || value < INT_MIN)  /* Check for integer overflow */
			error_exit(stack_a, NULL);  /* If overflow, exit with error */
		
		if (is_duplicate(*stack_a, (int)value))  /* Check for duplicate values */
			error_exit(stack_a, NULL);  /* If duplicate, exit with error */
		
		new_node = create_node((int)value);  /* Create new node with the value */
		if (!new_node)  /* Check if node creation failed */
			error_exit(stack_a, NULL);  /* If failed, exit with error */
		
		if (!*stack_a)  /* If stack is empty */
			*stack_a = new_node;  /* Set new node as the first node */
		else  /* If stack already has nodes */
		{
			last = *stack_a;  /* Start at the beginning of stack */
			while (last->next)  /* Find the last node */
				last = last->next;
			last->next = new_node;  /* Attach new node at the end */
		}
		
		i++;  /* Move to next argument */
	}
}
