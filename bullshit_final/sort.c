#include "push_swap.h"

/**
 * Sort a stack with 3 elements using the minimum number of operations
 */
void	sort_three(t_node **stack)
{
	int	highest_index;
	
	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	
	if (is_sorted(*stack))
		return ;
	
	// Find the highest index in the stack
	highest_index = (*stack)->index;
	if ((*stack)->next->index > highest_index)
		highest_index = (*stack)->next->index;
	if ((*stack)->next->next->index > highest_index)
		highest_index = (*stack)->next->next->index;
	
	// If highest is at the top, rotate it to the bottom
	if ((*stack)->index == highest_index)
		ra(stack);
	// If highest is in the middle, reverse rotate to get it to the bottom
	else if ((*stack)->next->index == highest_index)
		rra(stack);
	
	// If the first two elements are not in order, swap them
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}

/**
 * Push elements from stack A to stack B, leaving only 3 elements in A
 * Push smaller values first for better sorting efficiency
 */
static void	push_all_except_three(t_node **stack_a, t_node **stack_b)
{
	int	size;
	int	pushed;
	int	i;
	
	size = stack_size(*stack_a);
	if (size <= 3)
		return ;
	
	pushed = 0;
	i = 0;
	
	// First push all elements with index <= size/2 (the smaller half)
	while (size > 6 && i < size && pushed < size / 2)
	{
		if ((*stack_a)->index <= size / 2)
		{
			pb(stack_a, stack_b);
			pushed++;
		}
		else
			ra(stack_a);
		i++;
	}
	
	// Then push remaining elements except 3
	while (size - pushed > 3)
	{
		pb(stack_a, stack_b);
		pushed++;
	}
}

/**
 * Shift the stack so the lowest element is at the top
 */
void	shift_stack(t_node **stack_a)
{
	int	lowest_pos;
	int	size;
	
	if (!stack_a || !*stack_a)
		return ;
	
	size = stack_size(*stack_a);
	lowest_pos = get_lowest_index_position(stack_a);
	
	// If lowest is in bottom half, reverse rotate
	if (lowest_pos > size / 2)
	{
		while (lowest_pos < size)
		{
			rra(stack_a);
			lowest_pos++;
		}
	}
	// If lowest is in top half, rotate
	else
	{
		while (lowest_pos > 0)
		{
			ra(stack_a);
			lowest_pos--;
		}
	}
}

/**
 * Main sorting algorithm
 */
void	sort(t_node **stack_a, t_node **stack_b)
{
	if (!stack_a || !*stack_a)
		return ;
	
	// If already sorted, do nothing
	if (is_sorted(*stack_a))
		return ;
	
	// If only 2 elements, just swap if needed
	if (stack_size(*stack_a) == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
		return ;
	}
	
	// If 3 elements, use the specialized algorithm
	if (stack_size(*stack_a) == 3)
	{
		sort_three(stack_a);
		return ;
	}
	
	// For larger stacks, use the cost-based algorithm
	push_all_except_three(stack_a, stack_b);
	sort_three(stack_a);
	
	// Push elements back from B to A in correct order
	while (*stack_b)
	{
		set_target_position(stack_a, stack_b);
		calculate_cost(stack_a, stack_b);
		execute_cheapest_move(stack_a, stack_b);
	}
	
	// Finally, rotate stack A so lowest value is at the top
	if (!is_sorted(*stack_a))
		shift_stack(stack_a);
}
