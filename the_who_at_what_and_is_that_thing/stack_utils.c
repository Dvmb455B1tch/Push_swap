#include "push_swap.h"

/* Checks if the stack is sorted in ascending order */
int	stack_is_sorted(t_stack *stack)
{
	while (stack && stack->next)  /* While there are at least 2 nodes */
	{
		if (stack->value > stack->next->value)  /* If current > next */
			return (0);  /* Stack is not sorted, return 0 (false) */
		stack = stack->next;  /* Move to next node */
	}
	return (1);  /* Stack is sorted, return 1 (true) */
}

/* Finds and returns the minimum value in the stack */
int	get_min_value(t_stack *stack)
{
	int	min;  /* Variable to hold the minimum value */
	
	if (!stack)  /* Check if stack is empty */
		return (0);  /* Return 0 if empty */
	
	min = stack->value;  /* Initialize min with the first value */
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->value < min)  /* If current value is smaller */
			min = stack->value;  /* Update min value */
		stack = stack->next;  /* Move to next node */
	}
	return (min);  /* Return the minimum value found */
}

/* Finds and returns the maximum value in the stack */
int	get_max_value(t_stack *stack)
{
	int	max;  /* Variable to hold the maximum value */
	
	if (!stack)  /* Check if stack is empty */
		return (0);  /* Return 0 if empty */
	
	max = stack->value;  /* Initialize max with the first value */
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->value > max)  /* If current value is larger */
			max = stack->value;  /* Update max value */
		stack = stack->next;  /* Move to next node */
	}
	return (max);  /* Return the maximum value found */
}

/* Finds the position (index) of a given value in the stack */
int	get_index_in_stack(t_stack *stack, int value)
{
	int	index;  /* Variable to track position in stack */
	
	index = 0;  /* Initialize position counter to 0 */
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->value == value)  /* If current value matches */
			return (index);  /* Return the current position */
		index++;  /* Increment position counter */
		stack = stack->next;  /* Move to next node */
	}
	return (-1);  /* Value not found, return -1 */
}

/* Assigns index values to stack nodes based on their sorted order */
void	assign_indexes(t_stack **stack)
{
	t_stack	*current;  /* Pointer for traversing the stack */
	t_stack	*temp;     /* Temporary pointer for inner loop */
	int		size;      /* Size of the stack */
	int		min;       /* Current minimum value */
	int		index;     /* Current index being assigned */
	
	current = *stack;  /* Start at the beginning of stack */
	size = stack_size(*stack);  /* Get total number of elements */
	index = 1;  /* Start with index 1 */
	
	while (index <= size)  /* Continue until all elements indexed */
	{
		min = INT_MAX;  /* Initialize min to maximum integer */
		temp = *stack;  /* Start search from beginning */
		
		while (temp)  /* Search through entire stack */
		{
			if (temp->value < min && temp->index == 0)  /* Find unindexed minimum */
			{
				min = temp->value;  /* Update minimum value */
				current = temp;     /* Track node with minimum value */
			}
			temp = temp->next;  /* Move to next node */
		}
		
		current->index = index;  /* Assign current index to the node */
		index++;  /* Move to next index */
	}
}
