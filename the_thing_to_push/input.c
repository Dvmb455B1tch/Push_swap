/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:19:03 by riramana          #+#    #+#             */
/*   Updated: 2025/07/19 20:42:25 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	handle_parse_error(t_node **stack_a)
{
	free_stack(stack_a);
	write(2, "Error\n", 6);
	exit(1);
}

static void	parse_line(t_node **stack_a, char *str)
{
	int		j;
	int		k;
	long	num;
	t_node	*new;
	char	buffer[12];

	j = 0;
	while (str[j])
	{
		while (str[j] == ' ')
			j++;
		if (str[j] == '\0')
			break ;
		k = 0;
		while (str[j] && str[j] != ' ' && k < 11)
			buffer[k++] = str[j++];
		buffer[k] = '\0';
		num = ft_atoi(buffer);
		new = new_node((int)num);
		if (!new)
			handle_parse_error(stack_a);
		add_node_back(stack_a, new);
	}
}

t_node	*parse_input(int ac, char **av)
{
	t_node	*stack_a;
	int		i;

	stack_a = NULL;
	i = 1;
	while (i < ac)
	{
		parse_line(&stack_a, av[i]);
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
