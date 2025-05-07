#include "push_swap.h"
/* ************************************************************************** */
/*                         FREE AND ERROR HANDLING                           */
/* ************************************************************************** */

/*
	Free the entire linked list of the stack and null the pointer
*/
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)                              /* While stack is not empty */
	{
		tmp = (*stack)->next;                   /* Save next node */
		free(*stack);                           /* Free current node */
		*stack = tmp;                           /* Move to next node */
	}
}

/*
	Print "Error" to stderr, free the stack and exit
*/
void	exit_error(t_stack **stack)
{
	write(2, "Error\n", 6);                      /* Write error to stderr */
	free_stack(stack);                          /* Free the stack memory */
	exit(EXIT_FAILURE);                         /* Exit with error status */
}

/* ************************************************************************** */
/*                       STACK INITIALIZATION HELPERS                        */
/* ************************************************************************** */

/*
	Helper function to check if a string is a valid integer.
	Allows optional '+' or '-' and then digits.
*/
int	is_valid_input(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')         /* Skip optional sign */
		i++;
	if (!str[i])                                /* Check empty string after sign */
		return (0);
	while (str[i])                              /* Loop through characters */
	{
		if (str[i] < '0' || str[i] > '9')       /* Non-digit character */
			return (0);
		i++;
	}
	return (1);
}

/*
	Check if a value already exists in the stack
*/
int	has_duplicates(t_stack *stack)
{
	t_stack	*current;
	t_stack	*checker;

	current = stack;
	while (current)                             /* Loop through main node */
	{
		checker = current->next;
		while (checker)                         /* Compare with following nodes */
		{
			if (current->value == checker->value)
				return (1);                     /* Duplicate found */
			checker = checker->next;
		}
		current = current->next;
	}
	return (0);                                  /* No duplicates */
}

/* ************************************************************************** */
/*                      PARSING ARGUMENTS INTO STACK                         */
/* ************************************************************************** */

/*
	Create a new stack node and return its pointer
*/
static t_stack	*new_node(int value)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));             /* Allocate memory */
	if (!node)
		return (NULL);                          /* Allocation failed */
	node->value = value;                        /* Assign value */
	node->index = -1;                           /* Init index as unset */
	node->pos = -1;                             /* Init position */
	node->target_pos = -1;                      /* Init target pos */
	node->cost_a = 0;                           /* Init cost A */
	node->cost_b = 0;                           /* Init cost B */
	node->next = NULL;                          /* Init next as null */
	return (node);
}

/*
	Add a node to the end of the stack
*/
static void	append_node(t_stack **stack, int value)
{
	t_stack	*node;
	t_stack	*last;

	node = new_node(value);                     /* Create new node */
	if (!node)
		exit_error(stack);                      /* Exit if malloc failed */
	if (!*stack)                                /* Empty list: new node becomes head */
	{
		*stack = node;
		return ;
	}
	last = *stack;
	while (last->next)                          /* Go to end of list */
		last = last->next;
	last->next = node;                          /* Append new node */
}

/*
	Convert string to long (like atoi, but safe)
*/
static long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')             /* Handle sign */
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9')) /* Accumulate digits */
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
	Parse command-line arguments into a linked list stack.
	Handles multiple args or a single string of space-separated numbers.
*/
t_stack	*parse_args(int argc, char **argv)
{
	t_stack	*stack;
	long	num;
	int		i;

	stack = NULL;
	i = 1;
	while (i < argc)
	{
		if (!is_valid_input(argv[i]))           /* Validate each argument */
			exit_error(&stack);
		num = ft_atol(argv[i]);                 /* Convert to number */
		if (num > INT_MAX || num < INT_MIN)     /* Range check */
			exit_error(&stack);
		append_node(&stack, (int)num);          /* Add to stack */
		i++;
	}
	if (has_duplicates(stack))                  /* Final check for duplicates */
		exit_error(&stack);
	return (stack);                             /* Return populated stack */
}

