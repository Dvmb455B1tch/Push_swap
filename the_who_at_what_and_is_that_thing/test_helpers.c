#include "push_swap.h"

/* Optional helper functions for testing and debugging purposes */

/* Prints the contents of a stack */
void	print_stack(t_stack *stack, char stack_name)
{
	ft_putstr_fd("Stack ", 1);                /* Print "Stack " prefix */
	write(1, &stack_name, 1);                 /* Print stack name (A or B) */
	ft_putstr_fd(": ", 1);                    /* Print separator */
	
	if (!stack)                               /* Check if stack is empty */
	{
		ft_putstr_fd("Empty\n", 1);           /* Print "Empty" message */
		return ;                              /* Return from function */
	}
	
	while (stack)                             /* Loop through all elements */
	{
		/* For debugging, you can print both value and index if needed */
		/* Format can be adjusted based on your needs */
		char	num_str[20];                  /* Buffer for number string */
		int		i;                            /* Counter for digit position */
		int		temp;                         /* Temporary value for conversion */
		
		temp = stack->value;                  /* Get current value */
		
		/* Handle negative numbers */
		if (temp < 0)                         /* If number is negative */
		{
			write(1, "-", 1);                 /* Print minus sign */
			temp = -temp;                     /* Make temp positive */
		}
		
		/* Convert number to string */
		i = 0;                                /* Initialize counter */
		do {                                  /* Process all digits */
			num_str[i++] = (temp % 10) + '0'; /* Convert digit to character */
			temp /= 10;                       /* Move to next digit */
		} while (temp > 0);                   /* Continue until no more digits */
		
		/* Print digits in reverse order */
		while (i > 0)                         /* For each digit */
			write(1, &num_str[--i], 1);       /* Print digit */
		
		write(1, " ", 1);                     /* Print space between numbers */
		stack = stack->next;                  /* Move to next element */
	}
	
	write(1, "\n", 1);                        /* Print newline at end */
}

/* Validate that a stack is properly sorted */
int	validate_sort(t_stack *stack)
{
	while (stack && stack->next)              /* While there are at least 2 nodes */
	{
		if (stack->value > stack->next->value) /* If current > next */
			return (0);                       /* Not sorted, return false */
		stack = stack->next;                  /* Move to next node */
	}
	return (1);                               /* Stack is sorted, return true */
}

/* Count the number of operations outputted to sort the stack */
int	count_operations(void)
{
	int		count;                            /* Operation counter */
	char	buffer[2];                        /* Buffer for reading */
	int		read_result;                      /* Result of read operation */
	
	count = 0;                                /* Initialize counter */
	read_result = read(0, buffer, 1);         /* Read one character at a time */
	
	while (read_result > 0)                   /* Continue until end of input */
	{
		if (buffer[0] == '\n')                /* If newline found */
			count++;                          /* Increment operation count */
		read_result = read(0, buffer, 1);     /* Read next character */
	}
	
	return (count);                           /* Return total operation count */
}

/* Helper for testing custom input patterns */
void	test_case(int argc, char **argv)
{
	t_stack	*stack_a;                         /* Stack A for operations */
	t_stack	*stack_b;                         /* Stack B for operations */
	
	stack_a = NULL;                           /* Initialize stack A as empty */
	stack_b = NULL;                           /* Initialize stack B as empty */
	
	parse_arguments(argc, argv, &stack_a);    /* Parse arguments */
	
	ft_putstr_fd("Initial state:\n", 1);      /* Print initial state header */
	print_stack(stack_a, 'A');                /* Print initial stack A */
	print_stack(stack_b, 'B');                /* Print initial stack B */
	
	assign_indexes(&stack_a);                 /* Assign indexes for sorting */
	sort_stacks(&stack_a, &stack_b);          /* Sort the stacks */
	
	ft_putstr_fd("\nFinal state:\n", 1);      /* Print final state header */
	print_stack(stack_a, 'A');                /* Print final stack A */
	print_stack(stack_b, 'B');                /* Print final stack B */
	
	ft_putstr_fd("Validation: ", 1);          /* Print validation header */
	if (validate_sort(stack_a))               /* Check if stack is sorted */
		ft_putstr_fd("Sorted!\n", 1);         /* Print success message */
	else
		ft_putstr_fd("Not sorted!\n", 1);     /* Print failure message */
	
	free_stack(&stack_a);                     /* Free stack A memory */
	free_stack(&stack_b);                     /* Free stack B memory */
}
