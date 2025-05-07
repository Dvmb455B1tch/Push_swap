#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*stack_a;  /* Stack A */
	t_node	*stack_b;  /* Stack B */
	int		size;  /* Size of stack_a */

	if (argc < 2)  /* Check if arguments are provided */
		return (0);  /* Exit if no arguments */
	
	stack_a = NULL;  /* Initialize stack_a */
	stack_b = NULL;  /* Initialize stack_b */
	
	/* Parse arguments into stack_a */
	if (!ft_parse_args(argc, argv, &stack_a))
	{
		ft_stack_clear(&stack_a);  /* Clean up stack_a */
		return (1);  /* Exit with error */
	}
	
	/* Check for duplicates */
	if (ft_check_duplicates(stack_a))
	{
		ft_putstr_fd("Error\n", 2);  /* Output error message */
		ft_stack_clear(&stack_a);  /* Clean up stack_a */
		return (1);  /* Exit with error */
	}
	
	/* Assign indices for sorting */
	size = ft_stack_size(stack_a);  /* Get size of stack_a */
	ft_assign_index(stack_a, size);  /* Assign indices */
	
	/* Check if already sorted */
	if (!ft_is_sorted(stack_a))
		ft_sort(&stack_a, &stack_b);  /* Sort stack_a */
	
	/* Clean up stacks */
	ft_stack_clear(&stack_a);  /* Clean up stack_a */
	ft_stack_clear(&stack_b);  /* Clean up stack_b */
	
	return (0);  /* Exit with success */
}
