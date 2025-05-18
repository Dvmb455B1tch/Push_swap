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

static int	check_values_in_str(char *str, long *values, int *count)
{
	int		j;
	int		k;
	char	buffer[12];
	long	value;

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
		value = ft_atoi(buffer);
		if (value > 2147483647 || value < -2147483648)
			return (0);
		values[(*count)++] = value;
	}
	return (1);
}

static int	check_duplicates_in_values(long *values, int count, int *zero_count)
{
	int	i;
	int	j;

	i = 0;
	*zero_count = 0;
	while (i < count)
	{
		if (values[i] == 0)
			(*zero_count)++;
		j = i + 1;
		while (j < count)
		{
			if (values[i] == values[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_input(int ac, char **av)
{
	int		i;
	int		zero_count;
	int		found_token;
	long	values[1024];
	int		count;

	if (ac < 2)
		return (0);
	i = 1;
	zero_count = 0;
	found_token = 0;
	count = 0;
	while (i < ac)
	{
		if (!check_values_in_str(av[i], values, &count))
			return (0);
		found_token = (count > 0);
		i++;
	}
	if (!found_token || check_duplicates_in_values(values, count, &zero_count)
		|| zero_count > 1 || has_duplicates(av))
		return (0);
	return (1);
}
