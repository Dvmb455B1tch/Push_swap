/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-04 12:00:00 by student           #+#    #+#             */
/*   Updated: 2025-05-04 12:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Outputs a string to a file descriptor */
void	ft_putstr_fd(char *s, int fd)
{
	int	i;  /* Loop counter for traversing the string */
	
	if (!s || fd < 0)  /* Check for NULL string or invalid file descriptor */
		return ;  /* If invalid, return without doing anything */
	
	i = 0;  /* Start at the beginning of the string */
	while (s[i])  /* Loop until the end of the string */
	{
		write(fd, &s[i], 1);  /* Write the current character to file descriptor */
		i++;  /* Move to the next character */
	}
}

/* Converts a string to a long integer */
long	ft_atol(const char *str)
{
	int		i;      /* Index for traversing the string */
	int		sign;   /* Sign of the number (1 for positive, -1 for negative) */
	long	result;  /* The resulting converted number */
	
	i = 0;  /* Start at the beginning of the string */
	sign = 1;  /* Default sign is positive */
	result = 0;  /* Initialize result to 0 */
	
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))  /* Skip whitespace */
		i++;  /* Move past whitespace characters */
	
	if (str[i] == '-' || str[i] == '+')  /* Check for sign character */
	{
		if (str[i] == '-')  /* If negative sign found */
			sign = -1;  /* Set sign to negative */
		i++;  /* Move past sign character */
	}
	
	while (str[i] >= '0' && str[i] <= '9')  /* Process numeric characters */
	{
		result = result * 10 + (str[i] - '0');  /* Update result value */
		i++;  /* Move to next character */
	}
	
	return (result * sign);  /* Return the final converted value with sign */
}
