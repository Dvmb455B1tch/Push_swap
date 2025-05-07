#include "push_swap.h" /* Access to stack struct and prototypes */
/*
	Return the number of elements in the stack
*/
int	stack_size(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)                        /* Loop through list */
	{
		count++;                                 /* Count each node */
		stack = stack->next;
	}
	return (count);                              /* Return total */
}

/*
	Return the last node of a stack
*/
t_stack	*get_last_node(t_stack *stack)
{
	if (!stack)                                  /* Empty list */
		return (NULL);
	while (stack->next != NULL)                  /* Traverse to end */
		stack = stack->next;
	return (stack);                              /* Return last node */
}

/*
	Return the node with the smallest value
*/
t_stack	*get_min_node(t_stack *stack)
{
	t_stack	*min;

	if (!stack)                                  /* Safety check */
		return (NULL);
	min = stack;                                 /* Assume first is smallest */
	while (stack != NULL)
	{
		if (stack->value < min->value)           /* Found smaller */
			min = stack;
		stack = stack->next;
	}
	return (min);                                /* Return min node */
}

/*
	Return the node with the largest value
*/
t_stack	*get_max_node(t_stack *stack)
{
	t_stack	*max;

	if (!stack)                                  /* Safety check */
		return (NULL);
	max = stack;                                 /* Start with head */
	while (stack != NULL)
	{
		if (stack->value > max->value)           /* Update max if found */
			max = stack;
		stack = stack->next;
	}
	return (max);                                /* Return max node */
}

/*
	Update the `pos` field of each node in the stack
	This represents the index in the stack starting from 0
*/
void	update_positions(t_stack *stack)
{
	int	pos;

	pos = 0;
	while (stack != NULL)
	{
		stack->pos = pos;                        /* Assign position */
		pos++;                                   /* Increment counter */
		stack = stack->next;
	}
}

/*
	Return the index of a node in the stack by its value
*/
int	get_index(t_stack *stack, int value)
{
	int	index;

	index = 0;
	while (stack != NULL)
	{
		if (stack->value == value)               /* Match found */
			return (index);
		index++;
		stack = stack->next;
	}
	return (-1);                                 /* Not found */
}

/*
	Check if the stack is sorted in ascending order
*/
int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)   /* Disorder found */
			return (0);
		stack = stack->next;
	}
	return (1);                                  /* Sorted */
}

/*
	Free the entire stack
*/
void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack)
	{
		tmp = (*stack)->next;                    /* Save next */
		free(*stack);                            /* Free current */
		*stack = tmp;                            /* Move to next */
	}
	*stack = NULL;                               /* Safety set to NULL */
}

/*
	Print error message and exit
*/
void	error_exit(void)
{
	write(2, "Error\n", 6);                       /* Print to stderr */
	exit(1);                                     /* Exit with error code */
}

