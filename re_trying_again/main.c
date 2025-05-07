#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);                          /* No input */
	build_stack(&a, argc, argv);                 /* Parse input */
	if (is_sorted(a))                            /* Already sorted */
	{
		free_stack(&a);
		return (0);
	}
	turk_sort(&a, &b);                           /* Sort using Turkish algorithm */
	free_stack(&a);                              /* Clean up */
	return (0);
}
