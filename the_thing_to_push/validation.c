/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvmb455b1tch <dvmb455b1tch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:20:51 by riramana          #+#    #+#             */
/*   Updated: 2025/07/13 19:13:54 by dvmb455b1tc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	int		j;
	int		count;
	long	*values;
	int		max_values;

	if (ac < 2)
		return (0);
	max_values = 0;
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == ' ')
				max_values++;
			j++;
		}
		max_values++;
	}
	values = malloc(sizeof(long) * max_values);
	if (!values)
		return (0);
	i = 0;
	count = 0;
	while (++i < ac)
	{
		if (av[i][0] == '\0')
		{
			free(values);
			return (0);
		}
		j = 0;
		while (av[i][j] == ' ')
			j++;
		if (av[i][j] == '\0')
		{
			free(values);
			return (0);
		}
		if (!check_values_in_str(av[i], values, &count))
		{
			free(values);
			return (0);
		}
	}
	if (!count || check_duplicates_in_values(values, count, &i)
		|| has_duplicates(av))
	{
		free(values);
		return (0);
	}
	free(values);
	return (1);
}
