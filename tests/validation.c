/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riramana <riramana@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:20:51 by riramana          #+#    #+#             */
/*   Updated: 2025/05/13 13:54:55 by riramana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (zero_count > 1)
		return (0);
	if (has_duplicates(av))
		return (0);
	return (1);
}
