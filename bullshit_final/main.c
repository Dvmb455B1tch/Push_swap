#include "push_swap.h"

/**
 * Main function for push_swap
 */
int	main(int ac, char **av)
{
	t_node	*stack_a;
	t_node	*stack_b;
	int		size;

	if (ac < 2)
		return (0);
	
	if (!check_input(ac, av))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	
	stack_b = NULL;
	stack_a = parse_input(ac, av);
	size = stack_size(stack_a);
	
	// Assign index to each element (used for sorting)
	assign_index(stack_a, size);
	
	// If stack is not already sorted, sort it
	if (!is_sorted(stack_a))
		sort(&stack_a, &stack_b);
	
	// Free memory before exiting
	free_stack(&stack_a);
	free_stack(&stack_b);
	
	return (0);
}
