#include "push_swap.h"

/**
 * Set the position of each element in the stack
 * Position is the current location in the stack (0 is top)
 */
void	set_position(t_node **stack)
{
	t_node	*current;
	int		i;

	if (!stack || !*stack)
		return ;
	current = *stack;
	i = 0;
	while (current)
	{
		current->position = i;
		current = current->next;
		i++;
	}
}

/**
 * Find the position of the lowest indexed element
 */
int	get_lowest_index_position(t_node **stack)
{
	t_node	*current;
	int		lowest_index;
	int		lowest_pos;

	if (!stack || !*stack)
		return (-1);
	
	set_position(stack);
	current = *stack;
	lowest_index = 2147483647;//INT_MAX;
	lowest_pos = 0;
	
	while (current)
	{
		if (current->index < lowest_index)
		{
			lowest_index = current->index;
			lowest_pos = current->position;
		}
		current = current->next;
	}
	return (lowest_pos);
}

/**
 * Find the best target position in stack A for each element in stack B
 */
static int	find_target_position(t_node **stack_a, int b_index)
{
	t_node	*current;
	int		target_index;
	int		target_pos;

	current = *stack_a;
	target_index = 2147483647;//INT_MAX;
	target_pos = 0;
	
	// First try to find the closest greater index in stack A
	while (current)
	{
		if (current->index > b_index && current->index < target_index)
		{
			target_index = current->index;
			target_pos = current->position;
		}
		current = current->next;
	}
	
	// If no greater index found, find the smallest index in stack A
	if (target_index == 2147483647/*INT_MAX*/)
	{
		current = *stack_a;
		target_index = 	2147483647;//INT_MAX;
		
		while (current)
		{
			if (current->index < target_index)
			{
				target_index = current->index;
				target_pos = current->position;
			}
			current = current->next;
		}
	}
	
	return (target_pos);
}

/**
 * Set the target position for each element in stack B
 */
void	set_target_position(t_node **stack_a, t_node **stack_b)
{
	t_node	*current_b;
	
	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;
	
	set_position(stack_a);
	set_position(stack_b);
	
	current_b = *stack_b;
	while (current_b)
	{
		current_b->target_pos = find_target_position(stack_a, current_b->index);
		current_b = current_b->next;
	}
}
