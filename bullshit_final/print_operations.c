#include "push_swap.h"
/**
 * Print operation to stdout
 */
void	print_operation(char *op)
{
	int	i;

	i = 0;
	while (op[i])
		i++;
	write(1, op, i);
	write(1, "\n", 1);
}
