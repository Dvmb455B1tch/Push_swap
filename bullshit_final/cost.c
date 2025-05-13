#include "push_swap.h"
/**
 * Calculate the cost to move each element in stack B to its target position in stack A
 * - cost_b: cost to move element to top of stack B
 * - cost_a: cost to move target position to top of stack A
 * Positive cost means rotate (r), negative cost means reverse rotate (rr)
 */
void	calculate_cost(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;
	int	size_a;
	int	size_b;

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;
	
	size_a = stack_size(*stack_a);
	size_b = stack_size(*stack_b);
	current = *stack_b;
	
	while (current)
	{
		// Calculate cost to move to top of stack B
		current->cost_b = current->position;
		if (current->position > size_b / 2)
			current->cost_b = (size_b - current->position) * -1;
		
		// Calculate cost to move target position to top of stack A
		current->cost_a = current->target_pos;
		if (current->target_pos > size_a / 2)
			current->cost_a = (size_a - current->target_pos) * -1;
		
		current = current->next;
	}
}
/**
 * Find the element with lowest total cost and move it
 */
void	execute_cheapest_move(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;
	int	cheapest_cost;
	int	cost_a;
	int	cost_b;

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;
	
	current = *stack_b;
	cheapest_cost = 2147483647;//INT_MAX;
	
	while (current)
	{
		if (absolute_value(current->cost_a) + absolute_value(current->cost_b) < absolute_value(cheapest_cost))
		{
			cheapest_cost = absolute_value(current->cost_a) + absolute_value(current->cost_b);
			cost_a = current->cost_a;
			cost_b = current->cost_b;
		}
		current = current->next;
	}
	
	execute_move(stack_a, stack_b, cost_a, cost_b);
}
