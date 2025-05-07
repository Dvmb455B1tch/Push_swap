#include "push_swap.h"
/*
Check if a string represents a valid integer
*/
int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')          /* Optional sign */
		i++;
	if (str[i] == '\0')                          /* Only sign, no digits */
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')        /* Not a digit */
			return (0);
		i++;
	}
	return (1);
}

/*
Check if stack contains duplicate values
*/
int	has_duplicates(t_stack *stack, int value)
{
	while (stack != NULL)
	{
		if (stack->value == value)               /* Duplicate found */
			return (1);
		stack = stack->next;
	}
	return (0);
}

/*
	Convert string to long, checking for overflow
*/
long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))  /* Skip whitespace */
		str++;
	if (*str == '-' || *str == '+')              /* Handle sign */
		sign = (*str++ == '-') ? -1 : 1;
	while (*str >= '0' && *str <= '9')           /* Convert digits */
		res = res * 10 + (*str++ - '0');
	return (res * sign);
}

/*
	Add node to stack
*/
void	append_node(t_stack **stack, int value)
{
	t_stack	*new;
	t_stack	*last;

	new = (t_stack *)malloc(sizeof(t_stack));    /* Allocate node */
	if (!new)
		error_exit();                            /* Exit on failure */
	new->value = value;                          /* Store integer */
	new->index = -1;                             /* Will be set later */
	new->pos = -1;
	new->next = NULL;
	if (!*stack)                                 /* First node */
		*stack = new;
	else
	{
		last = get_last_node(*stack);            /* Find last */
		last->next = new;                        /* Append */
	}
}

/*
	Parse argv strings and build stack a
*/
void	build_stack(t_stack **a, int argc, char **argv)
{
	int		i;
	long	num;

	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))                 /* Invalid char */
			error_exit();
		num = ft_atol(argv[i]);                  /* Convert */
		if (num < -2147483648 || num > 2147483647)
			error_exit();                        /* Out of int range */
		if (has_duplicates(*a, (int)num))        /* Already exists */
			error_exit();
		append_node(a, (int)num);                /* Add to stack */
		i++;
	}
}

