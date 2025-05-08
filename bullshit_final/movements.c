#include "push_swap.h"

/**
 * Execute simultaneous reverse rotations on both stacks
 */
static void	execute_reverse_rotate_both(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(stack_a, stack_b);
	}
}

/**
 * Execute simultaneous rotations on both stacks
 */
static void	execute_rotate_both(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(stack_a, stack_b);
	}
}

/**
 * Move stack A into position using the cost
 */
void	move_stack_a(t_node **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(stack_a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rra(stack_a);
			(*cost)++;
		}
	}
}

/**
 * Move stack B into position using the cost
 */
void	move_stack_b(t_node **stack_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(stack_b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rrb(stack_b);
			(*cost)++;
		}
	}
}

/**
 * Execute the move with the given cost
 */
void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
	// Optimize by doing both operations simultaneously when possible
	if (cost_a < 0 && cost_b < 0)
		execute_reverse_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		execute_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	
	// Move the remaining operations
	move_stack_a(stack_a, &cost_a);
	move_stack_b(stack_b, &cost_b);
	
	// Push from B to A
	pa(stack_a, stack_b);
}
