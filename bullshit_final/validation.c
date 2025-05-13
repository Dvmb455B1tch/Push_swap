#include "push_swap.h"
/**
 * Check if a string represents a number
 */
int	is_number(char *str)
{
	int	i;

	i = 0;
	if (is_sign(str[i]) && str[i + 1] != '\0')
		i++;
	while (str[i] && is_digit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
/**
 * Check if a string represents zero (0, +0, -0, 000, etc.)
 */
int	is_zero(char *str)
{
	int	i;

	i = 0;
	if (is_sign(str[i]))
		i++;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
/**
 * Check for duplicate values in arguments
 */
int	has_duplicates(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 1;
		while (av[j])
		{
			if (i != j && str_compare(av[i], av[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
/**
 * Validate input arguments
 */
int	check_input(int ac, char **av)
{
	int	i;
	int	zero_count;

	if (ac < 2)
		return (0);
	i = 1;
	zero_count = 0;
	while (i < ac)
	{
		if (!is_number(av[i]))
			return (0);
		zero_count += is_zero(av[i]);
		i++;
	}
	// If multiple zeroes are found, we have duplicates
	if (zero_count > 1)
		return (0);
	// Check for duplicate values
	if (has_duplicates(av))
		return (0);
	return (1);
}
/**
 * Parse input arguments and create the stack A
 */
t_node	*parse_input(int ac, char **av)
{
	t_node	*stack_a;
	t_node	*new;
	long	num;
	int	i;

	stack_a = NULL;
	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num > 2147483647/*INT_MAX*/ || num < -2147483648 /*INT_MIN*/)
		{
			free_stack(&stack_a);
			write(2, "Error\n", 6);
			exit(1);
		}
		new = new_node((int)num);
		if (!new)
		{
			free_stack(&stack_a);
			write(2, "Error\n", 6);
			exit(1);
		}	
		add_node_back(&stack_a, new);
		i++;
	}
	return (stack_a);
}
/**
 * Assign index to each value in the stack
 * Index represents the position in the sorted array (0 is smallest)
 */
void	assign_index(t_node *stack_a, int size)
{
	t_node	*current;
	t_node	*highest;
	int	value;
	int	i;

	if (!stack_a)
		return ;
	i = size;
	while (--i >= 0)
	{
		current = stack_a;
		value = -2147483648/*INT_MIN*/;
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
