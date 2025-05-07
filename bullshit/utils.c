#include "push_swap.h"

/* Convert string to integer */
int	ft_atoi(const char *str)
{
	int			i;         /* Loop counter */
	int			sign;      /* Sign of the number */
	long long	result;    /* Result to handle overflow */

	i = 0;  /* Initialize counter */
	sign = 1;  /* Default sign is positive */
	result = 0;  /* Initialize result */
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))  /* Skip whitespace */
		i++;
	if (str[i] == '-' || str[i] == '+')  /* Handle sign */
	{
		if (str[i] == '-')
			sign = -1;  /* Change sign to negative */
		i++;  /* Move past sign character */
	}
	while (str[i] >= '0' && str[i] <= '9')  /* Process digits */
	{
		result = result * 10 + (str[i] - '0');  /* Convert char to digit */
		if ((result * sign) > 2147483647 || (result * sign) < -2147483648)
			return (0);  /* Return 0 on overflow (should be handled as error) */
		i++;  /* Move to next character */
	}
	return ((int)(result * sign));  /* Return final result with sign */
}

/* Output string to file descriptor */
void	ft_putstr_fd(char *str, int fd)
{
	int	i;  /* Loop counter */

	if (!str)  /* Check if string exists */
		return ;
	i = 0;  /* Initialize counter */
	while (str[i])  /* Traverse string */
	{
		write(fd, &str[i], 1);  /* Write one character at a time */
		i++;  /* Move to next character */
	}
}

/* Get absolute value of integer */
int	ft_abs(int n)
{
	if (n < 0)  /* Check if number is negative */
		return (-n);  /* Return positive equivalent */
	return (n);  /* Already positive, return as is */
}

/* Get minimum of two integers */
int	ft_min(int a, int b)
{
	if (a < b)  /* Compare the two values */
		return (a);  /* Return the smaller one */
	return (b);  /* Return b if it's smaller or equal */
}

/* Get maximum of two integers */
int	ft_max(int a, int b)
{
	if (a > b)  /* Compare the two values */
		return (a);  /* Return the larger one */
	return (b);  /* Return b if it's larger or equal */
}
/* Check if the string is a valid integer */
static int	ft_is_valid_int(char *str)
{
	int			i;  /* Loop counter */
	long long	num;  /* Store number to check for overflow */
	int			sign;  /* Sign of the number */

	i = 0;  /* Initialize counter */
	sign = 1;  /* Default sign is positive */
	if (str[i] == '-' || str[i] == '+')  /* Handle sign */
	{
		if (str[i] == '-')
			sign = -1;  /* Change sign to negative */
		i++;  /* Move past sign character */
	}
	if (!str[i])  /* Check if string has digits */
		return (0);  /* Return invalid if no digits */
	num = 0;  /* Initialize number */
	while (str[i])  /* Process all characters */
	{
		if (str[i] < '0' || str[i] > '9')  /* Check if digit */
			return (0);  /* Return invalid if not digit */
		num = num * 10 + (str[i] - '0');  /* Convert char to digit */
		if ((num * sign) > 2147483647 || (num * sign) < -2147483648)
			return (0);  /* Return invalid on overflow */
		i++;  /* Move to next character */
	}
	return (1);  /* Return valid */
}

/* Parse arguments and build stack A */
int	ft_parse_args(int argc, char **argv, t_node **stack_a)
{
	int		i;  /* Loop counter */
	int		value;  /* Value to add to stack */
	t_node	*new_node;  /* New node to add to stack */

	i = 1;  /* Start from first argument */
	while (i < argc)  /* Process all arguments */
	{
		if (!ft_is_valid_int(argv[i]))  /* Validate argument */
		{
			ft_putstr_fd("Error\n", 2);  /* Output error message */
			return (0);  /* Return failure */
		}
		value = ft_atoi(argv[i]);  /* Convert to integer */
		new_node = ft_stack_new(value);  /* Create new node */
		if (!new_node)  /* Check if allocation failed */
		{
			ft_stack_clear(stack_a);  /* Clean up stack */
			ft_putstr_fd("Error\n", 2);  /* Output error message */
			return (0);  /* Return failure */
		}
		ft_stack_add_back(stack_a, new_node);  /* Add to stack */
		i++;  /* Move to next argument */
	}
	return (1);  /* Return success */
}

/* Check for duplicate values in stack */
int	ft_check_duplicates(t_node *stack)
{
	t_node	*current;  /* Current node being checked */
	t_node	*compare;  /* Node to compare with */

	current = stack;  /* Start with first node */
	while (current)  /* Process all nodes */
	{
		compare = current->next;  /* Start with next node */
		while (compare)  /* Compare with all subsequent nodes */
		{
			if (current->value == compare->value)  /* Check for duplicate */
				return (1);  /* Return duplicate found */
			compare = compare->next;  /* Move to next node */
		}
		current = current->next;  /* Move to next node */
	}
	return (0);  /* Return no duplicates */
}

/* Check if stack is sorted */
int	ft_is_sorted(t_node *stack)
{
	t_node	*current;  /* Current node being checked */

	if (!stack)  /* Check if stack exists */
		return (1);  /* Empty stack is considered sorted */
	current = stack;  /* Start with first node */
	while (current->next)  /* Process all but last node */
	{
		if (current->value > current->next->value)  /* Check order */
			return (0);  /* Return not sorted */
		current = current->next;  /* Move to next node */
	}
	return (1);  /* Return sorted */
}

