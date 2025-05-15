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
			if (i != j && ft_atoi(av[i]) == ft_atoi(av[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_tokens(char *str, int *zero_count)
{
	int		j;
	int		k;
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
		if (!is_number(buffer))
			return (0);
		*zero_count += is_zero(buffer);
	}
	return (1);
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
		if (!check_tokens(av[i], &zero_count))
			return (0);
		i++;
	}
	if (zero_count > 1 || has_duplicates(av))
		return (0);
	return (1);
}
