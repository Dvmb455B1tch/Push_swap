#include "push_swap.h"
/**
 * Return the absolute value of a number
 */
int	absolute_value(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
/**
 * Convert string to long integer
 */
long	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	
	// Handle whitespace
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	// Convert digits
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	
	return (result * sign);
}
/**
 * Check if a character is a digit
 */
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
/**
 * Check if a character is a sign (+ or -)
 */
int	is_sign(char c)
{
	return (c == '+' || c == '-');
}
/**
 * Compare two strings
 */
int	str_compare(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	
	return (s1[i] - s2[i]);
}

