/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:06:32 by riramana          #+#    #+#             */
/*   Updated: 2025/05/13 09:18:10 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_operation(char *op)
{
	int	i;

	i = 0;
	while (op[i])
		i++;
	write(1, op, i);
	write(1, "\n", 1);
}

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
	assign_index(stack_a, size);
	if (!is_sorted(stack_a))
		sort(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
