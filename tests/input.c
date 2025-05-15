#include "push_swap.h"

static void	handle_parse_error(t_node **stack_a)
{
	free_stack(stack_a);
	write(2, "Error\n", 6);
	exit(1);
}

t_node	*parse_input(int ac, char **av)
{
	t_node	*stack_a;
	t_node	*new;
	long	num;
	int		i;

	stack_a = NULL;
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num < -2147483648)
			handle_parse_error(&stack_a);
		new = new_node((int)num);
		if (!new)
			handle_parse_error(&stack_a);
		add_node_back(&stack_a, new);
		i++;
	}
	return (stack_a);
}

void	assign_index(t_node *stack_a, int size)
{
	t_node	*current;
	t_node	*highest;
	int		value;
	int		i;

	if (!stack_a)
		return ;
	i = size;
	while (--i >= 0)
	{
		current = stack_a;
		value = -2147483648;
		highest = NULL;
		while (current)
		{
			if (current->value > value && current->index == 0)
			{
				value = current->value;
				highest = current;
			}
			current = current->next;
		}
		if (highest)
			highest->index = i;
	}
}
