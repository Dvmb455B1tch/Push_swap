#include "push_swap.h"
/* Calculate the cost to move each element in both stacks */
void	ft_calculate_cost(t_node *stack_a, t_node *stack_b)
{
	int	size_a;  /* Size of stack_a */
	int	size_b;  /* Size of stack_b */
	t_node	*current;  /* Current node being processed */

	size_a = ft_stack_size(stack_a);  /* Get size of stack_a */
	size_b = ft_stack_size(stack_b);  /* Get size of stack_b */
	current = stack_b;  /* Start with first node in stack_b */
	while (current)  /* Process all nodes in stack_b */
	{
		/* Calculate cost to move to top of stack_b */
		if (current->pos <= size_b / 2)
			current->cost_b = current->pos;  /* Cost using rb */
		else
			current->cost_b = -(size_b - current->pos);  /* Cost using rrb */
		
		/* Calculate cost to move target to top of stack_a */
		if (current->target_pos <= size_a / 2)
			current->cost_a = current->target_pos;  /* Cost using ra */
		else
			current->cost_a = -(size_a - current->target_pos);  /* Cost using rra */
		
		current = current->next;  /* Move to next node */
	}
}

/* Find the cheapest node to move */
void	ft_find_cheapest(t_node *stack_b, int *cheapest_index)
{
	int		cheapest_cost;  /* Cost of cheapest move */
	int		cost;  /* Cost of current move */
	t_node	*current;  /* Current node being checked */

	cheapest_cost = 2147483647;  /* Initialize with max int */
	current = stack_b;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		/* Calculate total cost of moving this node */
		cost = ft_abs(current->cost_a) + ft_abs(current->cost_b);
		if (cost < cheapest_cost)  /* Check if cheaper */
		{
			cheapest_cost = cost;  /* Update cheapest cost */
			*cheapest_index = current->index;  /* Update cheapest index */
		}
		current = current->next;  /* Move to next node */
	}
}

/* Execute rotations for both stacks */
static void	ft_execute_rotation(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
	/* While both costs are positive, do double rotation */
	while (cost_a > 0 && cost_b > 0)
	{
		rr(stack_a, stack_b);  /* Rotate both stacks up */
		cost_a--;  /* Decrement cost_a */
		cost_b--;  /* Decrement cost_b */
	}
	/* While both costs are negative, do double reverse rotation */
	while (cost_a < 0 && cost_b < 0)
	{
		rrr(stack_a, stack_b);  /* Rotate both stacks down */
		cost_a++;  /* Increment cost_a */
		cost_b++;  /* Increment cost_b */
	}
	/* Handle remaining rotations for stack_a */
	while (cost_a > 0)
	{
		ra(stack_a);  /* Rotate stack_a up */
		cost_a--;  /* Decrement cost_a */
	}
	while (cost_a < 0)
	{
		rra(stack_a);  /* Rotate stack_a down */
		cost_a++;  /* Increment cost_a */
	}
	/* Handle remaining rotations for stack_b */
	while (cost_b > 0)
	{
		rb(stack_b);  /* Rotate stack_b up */
		cost_b--;  /* Decrement cost_b */
	}
	while (cost_b < 0)
	{
		rrb(stack_b);  /* Rotate stack_b down */
		cost_b++;  /* Increment cost_b */
	}
}

/* Execute the cheapest move */
void	ft_execute_cheapest(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;  /* Current node being checked */
	int		cheapest_index;  /* Index of cheapest node to move */
	int		cost_a;  /* Cost for stack_a */
	int		cost_b;  /* Cost for stack_b */

	ft_find_cheapest(*stack_b, &cheapest_index);  /* Find cheapest move */
	current = *stack_b;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		if (current->index == cheapest_index)  /* Find node with cheapest index */
		{
			cost_a = current->cost_a;  /* Get cost for stack_a */
			cost_b = current->cost_b;  /* Get cost for stack_b */
			ft_execute_rotation(stack_a, stack_b, cost_a, cost_b);  /* Execute rotations */
			pa(stack_a, stack_b);  /* Push from B to A */
			break ;  /* Exit loop */
		}
		current = current->next;  /* Move to next node */
	}
}
