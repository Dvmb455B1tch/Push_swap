#include "push_swap.h"

/* Assign positions to all nodes in stack */
void	ft_assign_position(t_node *stack)
{
	int	pos;  /* Position counter */

	pos = 0;  /* Initialize position */
	while (stack)  /* Process all nodes */
	{
		stack->pos = pos;  /* Assign position */
		stack = stack->next;  /* Move to next node */
		pos++;  /* Increment position */
	}
}

/* Find the index of the smallest element in stack */
int	ft_find_smallest_index(t_node *stack)
{
	int		smallest;  /* Smallest index found */
	t_node	*current;  /* Current node being checked */

	smallest = stack->index;  /* Initialize with first node's index */
	current = stack;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		if (current->index < smallest)  /* Check if smaller */
			smallest = current->index;  /* Update smallest */
		current = current->next;  /* Move to next node */
	}
	return (smallest);  /* Return smallest index */
}

/* Find the target position in stack_a for an element from stack_b */
int	ft_get_target_position(t_node *stack_a, int index_b, int target, int pos)
{
	t_node	*current;  /* Current node being checked */
	int		closest;  /* Closest larger index found */

	closest = 2147483647;  /* Initialize with max int */
	current = stack_a;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		if (current->index > index_b && current->index < closest)
		{
			closest = current->index;  /* Update closest */
			target = current->pos;  /* Update target position */
		}
		current = current->next;  /* Move to next node */
	}
	if (closest != 2147483647)  /* Check if a match was found */
		return (target);  /* Return target position */
	
	/* If no larger index was found, target the smallest index */
	current = stack_a;  /* Reset to first node */
	while (current)  /* Process all nodes */
	{
		if (current->index == ft_find_smallest_index(stack_a))
		{
			pos = current->pos;  /* Get position of smallest element */
			break ;  /* Exit loop */
		}
		current = current->next;  /* Move to next node */
	}
	return (pos);  /* Return position of smallest element */
}

/* Assign target positions to all nodes in stack_b */
void	ft_assign_target_position(t_node *stack_a, t_node *stack_b)
{
	t_node	*current_b;  /* Current node in stack_b */
	int		target_pos;  /* Target position */

	ft_assign_position(stack_a);  /* Update positions in stack_a */
	ft_assign_position(stack_b);  /* Update positions in stack_b */
	current_b = stack_b;  /* Start with first node in stack_b */
	while (current_b)  /* Process all nodes in stack_b */
	{
		target_pos = ft_get_target_position(stack_a, current_b->index, 0, 0);
		current_b->target_pos = target_pos;  /* Assign target position */
		current_b = current_b->next;  /* Move to next node */
	}
}

