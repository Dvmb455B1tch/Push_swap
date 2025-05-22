/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* This function calculates the cost of moving each element from stack_b to its 
 * target position in stack_a. The cost has two components:
 * 1. cost_b: Cost to bring the element to the top of stack_b
 * 2. cost_a: Cost to position stack_a correctly for insertion
 * Positive cost means rotate (r) operations, negative cost means reverse rotate (rr) */
void	calculate_cost(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;        /* Pointer to traverse stack_b */
	int		size_a;          /* Size of stack_a */
	int		size_b;          /* Size of stack_b */

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;             /* Safety check for null stacks */
	size_a = stack_size(*stack_a);
	size_b = stack_size(*stack_b);
	current = *stack_b;
	while (current)          /* Iterate through each element in stack_b */
	{
		current->cost_b = current->position;  /* Initial cost is position */
		if (current->position > size_b / 2)
			/* If position is in lower half, use reverse rotate (cheaper) */
			current->cost_b = (size_b - current->position) * -1;
		current->cost_a = current->target_pos;  /* Cost to move stack_a */
		if (current->target_pos > size_a / 2)
			/* If target position is in lower half, use reverse rotate */
			current->cost_a = (size_a - current->target_pos) * -1;
		current = current->next;
	}
}

/* This function finds the element in stack_b with the cheapest total cost to move
 * to its target position in stack_a, and executes that move. This is the core of
 * the sorting algorithm's optimization strategy. */
void	execute_cheapest_move(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;           /* Pointer to traverse stack_b */
	int		cheapest_cost;      /* Track the lowest total cost found */
	int		cost_a;             /* Cost for stack_a of the cheapest move */
	int		cost_b;             /* Cost for stack_b of the cheapest move */

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;                /* Safety check for null stacks */
	current = *stack_b;
	cheapest_cost = 2147483647; /* Initialize to INT_MAX */
	while (current)             /* Iterate through each element in stack_b */
	{
		/* Check if this element has a cheaper total cost */
		if (absolute_value(current->cost_a) + absolute_value(current->cost_b)
			< absolute_value(cheapest_cost))
		{
			/* Update the cheapest cost and remember the associated move */
			cheapest_cost = absolute_value(current->cost_a)
				+ absolute_value(current->cost_b);
			cost_a = current->cost_a;
			cost_b = current->cost_b;
		}
		current = current->next;
	}
	/* Execute the cheapest move found */
	execute_move(stack_a, stack_b, cost_a, cost_b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Handle parsing errors by freeing memory, printing error message and exiting */
static void	handle_parse_error(t_node **stack_a)
{
	free_stack(stack_a);         /* Free all allocated memory */
	write(2, "Error\n", 6);       /* Print error message to stderr */
	exit(1);                     /* Exit with error code 1 */
}

/* Parse a single argument string which could contain multiple numbers separated
 * by spaces. Each number is converted to an integer and added to stack_a. */
static void	parse_line(t_node **stack_a, char *str)
{
	int		j;        /* Index for traversing the input string */
	int		k;        /* Index for building number buffer */
	long	num;              /* Store number as long to check for INT overflow */
	t_node	*new;             /* New node to add to stack */
	char	buffer[12];       /* Buffer to hold a single number as string */

	j = 0;
	while (str[j])
	{
		while (str[j] == ' ')    /* Skip spaces */
			j++;
		if (str[j] == '\0')      /* End of string */
			break ;
		k = 0;
		/* Extract a number into buffer */
		while (str[j] && str[j] != ' ' && k < 11)
			buffer[k++] = str[j++];
		buffer[k] = '\0';        /* Null-terminate the buffer */
		num = ft_atoi(buffer);   /* Convert to number */
		if (num > 2147483647 || num < -2147483648)
			handle_parse_error(stack_a);  /* Check for INT overflow */
		new = new_node((int)num);        /* Create new node */
		if (!new)
			handle_parse_error(stack_a);  /* Check for allocation failure */
		add_node_back(stack_a, new);     /* Add to stack_a */
	}
}

/* Parse all input arguments to create stack_a with the numbers to be sorted.
 * In push_swap, arguments are passed as separate strings or as a single string
 * with multiple numbers. */
t_node	*parse_input(int ac, char **av)
{
	t_node	*stack_a;         /* The stack to be filled with numbers */
	int		i;                /* Loop counter for arguments */

	stack_a = NULL;
	i = 1;                     /* Start from 1 to skip program name */
	while (i < ac)
	{
		parse_line(&stack_a, av[i]);  /* Parse each argument */
		i++;
	}
	return (stack_a);          /* Return the populated stack */
}

 /* After this function, nodes will have index values where:
     * The highest value has index = size - 1
     * The lowest value has index = 0
     * This simplifies sorting, as the original values are normalized to a range [0, size - 1]
     */
void	assign_index(t_node *stack_a, int size)
{
	t_node	*current;         /* For traversing the stack */
	t_node	*highest;         /* Points to node with highest unindexed value */
	int		value;            /* Current highest value found */
	int		i;                /* Loop counter and index value */

	if (!stack_a)
		return ;               /* Safety check for empty stack */
	i = size;
	while (--i >= 0)           /* Loop from size-1 down to 0 */
	{
		current = stack_a;
		value = -2147483648;   /* Start with INT_MIN */
		highest = NULL;
		/* Find the highest unindexed value */
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
			highest->index = i;  /* Assign index in descending order */
	}

}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Main function - entry point of the program */
int	main(int ac, char **av)
{
	t_node	*stack_a;        /* Main stack with initial unsorted numbers */
	t_node	*stack_b;        /* Secondary stack used for sorting */
	int		size;            /* Number of elements to sort */

	if (ac < 2)              /* No arguments provided */
		return (0);
	if (!check_input(ac, av))  /* Validate all input */
	{
		write(2, "Error\n", 6);  /* Print error for invalid input */
		return (1);
	}
	stack_b = NULL;            /* Initialize stack_b as empty */
	stack_a = parse_input(ac, av);  /* Parse arguments into stack_a */
	size = stack_size(stack_a);     /* Get number of elements */
	assign_index(stack_a, size);    /* Assign normalized indices */
	if (!is_sorted(stack_a))        /* Check if already sorted */
		sort(&stack_a, &stack_b);   /* Sort the stack */
	free_stack(&stack_a);           /* Free allocated memory */
	free_stack(&stack_b);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Execute reverse rotations on both stacks simultaneously when both need
 * reverse rotation (costs are negative). This optimizes the number of operations
 * by using 'rrr' instead of separate 'rra' and 'rrb' operations. */
static void	execute_reverse_rotate_both(t_node **stack_a, t_node **stack_b,
		int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;             /* Adjust costs to reflect operation */
		(*cost_b)++;
		rrr(stack_a, stack_b);   /* Reverse rotate both stacks */
	}
}

/* Execute rotations on both stacks simultaneously when both need
 * rotation (costs are positive). This optimizes by using 'rr' instead
 * of separate 'ra' and 'rb' operations. */
static void	execute_rotate_both(t_node **stack_a, t_node **stack_b,
		int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;             /* Adjust costs to reflect operation */
		(*cost_b)--;
		rr(stack_a, stack_b);    /* Rotate both stacks */
	}
}

/* Move stack_a to the desired position after combined operations.
 * Positive cost means normal rotation (ra), negative means reverse rotation (rra) */
void	move_stack_a(t_node **stack_a, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(stack_a);     /* Rotate a - move top element to bottom */
			(*cost)--;       /* Decrease remaining cost */
		}
		else if (*cost < 0)
		{
			rra(stack_a);    /* Reverse rotate a - move bottom element to top */
			(*cost)++;       /* Increase (move closer to zero) remaining cost */
		}
	}
}

/* Move stack_b to the desired position after combined operations.
 * Positive cost means normal rotation (rb), negative means reverse rotation (rrb) */
void	move_stack_b(t_node **stack_b, int *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(stack_b);     /* Rotate b - move top element to bottom */
			(*cost)--;       /* Decrease remaining cost */
		}
		else if (*cost < 0)
		{
			rrb(stack_b);    /* Reverse rotate b - move bottom element to top */
			(*cost)++;       /* Increase (move closer to zero) remaining cost */
		}
	}
}

/* Execute a complete move operation to bring an element from stack_b to its
 * target position in stack_a. This is the main operation in the sorting algorithm:
 * 1. Optimize by doing combined operations when possible
 * 2. Finish any remaining individual stack operations
 * 3. Finally push the element from b to a */
void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		execute_reverse_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)
		execute_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	move_stack_a(stack_a, &cost_a);    /* Complete stack_a movements */
	move_stack_b(stack_b, &cost_b);    /* Complete stack_b movements */
	pa(stack_a, stack_b);              /* Push element from b to a */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Set the position field for each node in the stack.
 * Position is the node's distance from the top of the stack (0-indexed). */
void	set_position(t_node **stack)
{
	t_node	*current;      /* Pointer for traversing the stack */
	int		i;             /* Position counter */

	if (!stack || !*stack)
		return ;            /* Safety check for null stack */
	current = *stack;
	i = 0;
	while (current)
	{
		current->position = i;  /* Set current node's position */
		current = current->next;
		i++;
	}
}

/* Find the position of the node with the lowest index in the stack.
 * This is useful for final rotation to put the stack in order. */
int	get_lowest_index_position(t_node **stack)
{
	t_node	*current;          /* Pointer for traversing the stack */
	int		lowest_index;      /* Track the lowest index found */
	int		lowest_pos;        /* Position of the lowest index node */

	if (!stack || !*stack)
		return (-1);            /* Safety check for null stack */
	set_position(stack);        /* Update positions for all nodes */
	current = *stack;
	lowest_index = 2147483647;  /* Start with INT_MAX */
	lowest_pos = 0;
	while (current)
	{
		if (current->index < lowest_index)
		{
			lowest_index = current->index;
			lowest_pos = current->position;
		}
		current = current->next;
	}
	return (lowest_pos);        /* Return position of lowest index */
}

/* Helper function to find the position of the node with the minimum index.
 * Used when no suitable target exists in stack_a for a node in stack_b. */
static int	find_min_index_position(t_node **stack_a)
{
	t_node	*current;         /* Pointer for traversing the stack */
	int		target_index;     /* Track the minimum index found */
	int		target_pos;       /* Position of the minimum index node */

	current = *stack_a;
	target_index = 2147483647;  /* Start with INT_MAX */
	target_pos = 0;
	while (current)
	{
		if (current->index < target_index)
		{
			target_index = current->index;
			target_pos = current->position;
		}
		current = current->next;
	}
	return (target_pos);       /* Return position of minimum index */
}

/* Find the target position in stack_a for a node from stack_b with index b_index.
 * The target is the node in stack_a with the smallest index greater than b_index.
 * If no such node exists, the target is the node with the smallest index overall. */
static int	find_target_position(t_node **stack_a, int b_index)
{
	t_node	*current;         /* Pointer for traversing stack_a */
	int		target_index;     /* Track the best target index found */
	int		target_pos;       /* Position of the best target node */

	current = *stack_a;
	target_index = 2147483647;  /* Start with INT_MAX */
	target_pos = 0;
	while (current)
	{
		/* Look for the smallest index in stack_a that is greater than b_index */
		if (current->index > b_index && current->index < target_index)
		{
			target_index = current->index;
			target_pos = current->position;
		}
		current = current->next;
	}
	/* If no suitable target was found, use the node with minimum index */
	if (target_index == 2147483647)
		target_pos = find_min_index_position(stack_a);
	return (target_pos);
}

/* Set target positions for all nodes in stack_b.
 * The target position is where the node should be inserted in stack_a. */
void	set_target_position(t_node **stack_a, t_node **stack_b)
{
	t_node	*current_b;     /* Pointer for traversing stack_b */

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;              /* Safety check for null stacks */
	set_position(stack_a);    /* Update positions in stack_a */
	set_position(stack_b);    /* Update positions in stack_b */
	current_b = *stack_b;
	while (current_b)
	{
		/* Find and set target position for this node */
		current_b->target_pos = find_target_position(stack_a, current_b->index);
		current_b = current_b->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Print an operation to standard output.
 * The push_swap program must output the operations it performs to sort the stack. */
void	print_operation(char *op)
{
	int	i;                /* Counter for string length */

	i = 0;
	while (op[i])         /* Count characters in operation string */
		i++;
	write(1, op, i);      /* Write operation to stdout */
	write(1, "\n", 1);    /* Write newline */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Internal function to push the top element from src stack to dest stack.
 * This is the core operation for pa and pb commands. */
void	push(t_node **src, t_node **dest)
{
	t_node	*temp;        /* Temporary pointer to top node of src */

	if (!*src)
		return ;           /* Safety check for empty source stack */
	temp = *src;           /* Save pointer to top node */
	*src = (*src)->next;   /* Update src to point to next node */
	temp->next = *dest;    /* Make old top node point to dest top */
	*dest = temp;          /* Update dest to point to new top */
}

/* Push the top element from stack_b to stack_a (pa operation) */
void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);   /* Move top of B to top of A */
	print_operation("pa");    /* Output the operation */
}

/* Push the top element from stack_a to stack_b (pb operation) */
void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);   /* Move top of A to top of B */
	print_operation("pb");    /* Output the operation */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */


#include "push_swap.h"

/* Internal function to reverse rotate a stack: move bottom element to top.
 * This is the core operation for rra, rrb, and rrr commands. */
void	reverse_rotate(t_node **stack)
{
	t_node	*last;          /* Pointer to the last node */
	t_node	*second_last;   /* Pointer to the second last node */

	if (!*stack || !(*stack)->next)
		return ;             /* Safety check for empty or single-element stack */
	last = get_last_node(*stack);           /* Get last node */
	second_last = get_second_last_node(*stack);  /* Get second last node */
	last->next = *stack;     /* Make last node point to first node */
	*stack = last;           /* Update stack to point to new first node (old last) */
	second_last->next = NULL;  /* Terminate the list at new last node */
}

/* Reverse rotate stack_a (rra operation) */
void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);    /* Reverse rotate stack A */
	print_operation("rra");     /* Output the operation */
}

/* Reverse rotate stack_b (rrb operation) */
void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);    /* Reverse rotate stack B */
	print_operation("rrb");     /* Output the operation */
}

/* Reverse rotate both stacks simultaneously (rrr operation) */
void	rrr(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a);    /* Reverse rotate stack A */
	reverse_rotate(stack_b);    /* Reverse rotate stack B */
	print_operation("rrr");     /* Output the operation */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Internal function to rotate a stack: move top element to bottom.
 * This is the core operation for ra, rb, and rr commands. */
void	rotate(t_node **stack)
{
	t_node	*temp;        /* Temporary pointer to top node */
	t_node	*last;        /* Pointer to last node */

	if (!*stack || !(*stack)->next)
		return ;           /* Safety check for empty or single-element stack */
	temp = *stack;         /* Save pointer to top node */
	*stack = (*stack)->next;  /* Update stack to point to new top (old second) */
	last = get_last_node(*stack);  /* Get last node */
	temp->next = NULL;     /* Detach old top node */
	last->next = temp;     /* Attach old top to end of list */
}

/* Rotate stack_a (ra operation) */
void	ra(t_node **stack_a)
{
	rotate(stack_a);        /* Rotate stack A */
	print_operation("ra");  /* Output the operation */
}

/* Rotate stack_b (rb operation) */
void	rb(t_node **stack_b)
{
	rotate(stack_b);        /* Rotate stack B */
	print_operation("rb");  /* Output the operation */
}

/* Rotate both stacks simultaneously (rr operation) */
void	rr(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a);        /* Rotate stack A */
	rotate(stack_b);        /* Rotate stack B */
	print_operation("rr");  /* Output the operation */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Special algorithm to sort exactly three elements efficiently.
 * This is optimized for the minimal number of operations. */
void	sort_three(t_node **stack)
{
	int	highest_index;      /* Tracks the highest index in the stack */

	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;              /* Safety check for stacks with < 3 elements */
	if (is_sorted(*stack))
		return ;              /* Already sorted, nothing to do */
	
	/* Find the highest index among the three nodes */
	highest_index = (*stack)->index;
	if ((*stack)->next->index > highest_index)
		highest_index = (*stack)->next->index;
	if ((*stack)->next->next->index > highest_index)
		highest_index = (*stack)->next->next->index;
	
	/* Perform operations based on position of highest index */
	if ((*stack)->index == highest_index)
		ra(stack);            /* If highest is at top, rotate once */
	else if ((*stack)->next->index == highest_index)
		rra(stack);           /* If highest is in middle, reverse rotate once */
	
	/* After the above, the highest is at the bottom. Now check if
	 * the top two elements need to be swapped */
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);            /* Swap if needed */
}

/* Push all elements except three from stack_a to stack_b.
 * Uses an optimization to push smaller elements first, which reduces
 * future sorting operations. */
static void	push_all_except_three(t_node **stack_a, t_node **stack_b)
{
	int	size;             /* Total number of elements in stack_a */
	int	pushed;           /* Count of elements pushed to stack_b */
	int	i;                /* Loop counter */

	size = stack_size(*stack_a);
	if (size <= 3)
		return ;            /* Already 3 or fewer elements, nothing to do */
	
	pushed = 0;
	i = 0;
	
	/* First phase: push elements with small indices (lower half) to B */
	while (size > 6 && i < size && pushed < size / 2)
	{
		if ((*stack_a)->index <= size / 2)
		{
			pb(stack_a, stack_b);  /* Push to B if index is small */
			pushed++;
		}
		else
			ra(stack_a);           /* Otherwise rotate A to check next element */
		i++;
	}
	
	/* Second phase: push remaining elements until only 3 are left in A */
	while (size - pushed > 3)
	{
		pb(stack_a, stack_b);
		pushed++;
	}
}

/* Shift the stack so that the smallest element is at the top.
 * Used at the end of sorting to finalize the order. */
void	shift_stack(t_node **stack_a)
{
	int	lowest_pos;       /* Position of element with lowest index */
	int	size;             /* Size of the stack */

	if (!stack_a || !*stack_a)
		return ;            /* Safety check for null stack */
	size = stack_size(*stack_a);
	lowest_pos = get_lowest_index_position(stack_a);
	
	/* Choose optimal rotation direction based on position */
	if (lowest_pos > size / 2)
	{
		/* If lowest is in bottom half, use reverse rotation */
		while (lowest_pos < size)
		{
			rra(stack_a);
			lowest_pos++;
		}
	}
	else
	{
		/* If lowest is in top half, use normal rotation */
		while (lowest_pos > 0)
		{
			ra(stack_a);
			lowest_pos--;
		}
	}
}

/* Main sorting algorithm that implements a variation of insertion sort using
 * stack operations. The general approach is:
 * 1. Push all but 3 elements to stack_b
 * 2. Sort the 3 elements in stack_a
 * 3. For each element in stack_b, find optimal position in stack_a
 * 4. Calculate cost of moving each element and choose cheapest
 * 5. Execute moves until stack_b is empty
 * 6. Rotate stack_a to put smallest element at top */
void	sort(t_node **stack_a, t_node **stack_b)
{
	if (!stack_a || !*stack_a)
		return ;              /* Safety check for null stack */
	if (is_sorted(*stack_a))
		return ;              /* Already sorted, nothing to do */
	
	/* Special cases for 2 or 3 elements */
	if (stack_size(*stack_a) == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);      /* For 2 elements, just swap if needed */
		return ;
	}
	if (stack_size(*stack_a) == 3)
	{
		sort_three(stack_a);  /* Use specialized 3-element sort */
		return ;
	}
	
	/* For more than 3 elements, use the full algorithm */
	push_all_except_three(stack_a, stack_b);  /* Keep 3 in A, rest in B */
	sort_three(stack_a);                      /* Sort the 3 in A */
	
	/* Main loop: move elements one by one from B to A in optimal order */
	while (*stack_b)
	{
		set_target_position(stack_a, stack_b);  /* Find target positions */
		calculate_cost(stack_a, stack_b);       /* Calculate move costs */
		execute_cheapest_move(stack_a, stack_b);  /* Execute cheapest move */
	}
	
	/* Final step: rotate A to proper position with smallest at top */
	if (!is_sorted(*stack_a))
		shift_stack(stack_a);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+    */

#include "push_swap.h"

/* Create a new stack node with the given value.
 * This is the basic building block of our linked list implementation of stacks.
 * The function initializes all fields with default values. */
t_node	*new_node(int value)
{
	t_node	*node;           /* Pointer to the new node */

	node = malloc(sizeof(t_node));  /* Allocate memory for the node */
	if (!node)
		return (NULL);        /* Return NULL if allocation fails */
	node->value = value;      /* Set the node's value */
	node->index = 0;          /* Initialize index to 0 */
	node->position = -1;      /* Initialize position to -1 (unassigned) */
	node->target_pos = -1;    /* Initialize target position to -1 (unassigned) */
	node->cost_a = -1;        /* Initialize cost_a to -1 (unassigned) */
	node->cost_b = -1;        /* Initialize cost_b to -1 (unassigned) */
	node->next = NULL;        /* Initialize next pointer to NULL */
	return (node);            /* Return the new node */
}

/* Add a new node to the end of the stack.
 * This maintains the stack data structure as a linked list. */
void	add_node_back(t_node **stack, t_node *new)
{
	t_node	*last;           /* Pointer to the last node in stack */

	if (!new)
		return ;              /* Safety check for null new node */
	if (!*stack)
	{
		*stack = new;         /* If stack is empty, new node becomes stack */
		return ;
	}
	last = get_last_node(*stack);  /* Find the last node */
	last->next = new;         /* Attach new node after the last node */
}

/* Find and return the last node in the stack.
 * This is used for operations like reverse rotation and adding nodes. */
t_node	*get_last_node(t_node *stack)
{
	if (!stack)
		return (NULL);        /* Safety check for null stack */
	while (stack->next)
		stack = stack->next;  /* Traverse to the end of the list */
	return (stack);           /* Return the last node */
}

/* Find and return the second last node in the stack.
 * This is particularly useful for reverse rotation operations. */
t_node	*get_second_last_node(t_node *stack)
{
	if (!stack || !stack->next)
		return (NULL);        /* Safety check for null or single-node stack */
	while (stack->next && stack->next->next)
		stack = stack->next;  /* Traverse until second last node */
	return (stack);           /* Return the second last node */
}

/* Count and return the number of nodes in the stack.
 * This is used to determine stack size for various operations. */
int	stack_size(t_node *stack)
{
	int	size;               /* Counter for stack size */

	size = 0;
	while (stack)
	{
		size++;              /* Increment counter for each node */
		stack = stack->next; /* Move to next node */
	}
	return (size);           /* Return the final count */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Check if a string represents a valid number.
 * A valid number can have an optional sign followed by digits only. */
int	is_number(char *str)
{
	int	i;                  /* Index for traversing the string */

	i = 0;
	if (is_sign(str[i]) && str[i + 1] != '\0')
		i++;                /* Skip sign character if present */
	while (str[i] && is_digit(str[i]))
		i++;                /* Skip all digit characters */
	if (str[i] != '\0')
		return (0);         /* Return false if any non-digit characters found */
	return (1);             /* Return true if string contains only digits (and optional sign) */
}

/* Free all memory allocated for the stack.
 * This function iterates through each node and frees it. */
void	free_stack(t_node **stack)
{
	t_node	*tmp;           /* Temporary pointer for traversal */

	if (!stack || !*stack)
		return ;             /* Safety check for null stack */
	while (*stack)
	{
		tmp = (*stack)->next;  /* Save pointer to next node */
		free(*stack);          /* Free current node */
		*stack = tmp;          /* Move to next node */
	}
	*stack = NULL;           /* Set stack pointer to NULL */
}

/* Check if a stack is sorted in ascending order.
 * Returns 1 if sorted, 0 if not sorted. */
int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);       /* Return false if any pair is not in order */
		stack = stack->next;  /* Move to next node */
	}
	return (1);              /* Return true if all elements are in order */
}

/* Free both stacks, print an error message, and exit the program.
 * This is used for fatal errors during processing. */
void	free_and_exit(t_node **stack_a, t_node **stack_b)
{
	free_stack(stack_a);     /* Free stack A */
	free_stack(stack_b);     /* Free stack B */
	write(2, "Error\n", 6);    /* Print error message to stderr */
	exit(1);                 /* Exit with error code 1 */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Internal function to swap the top two elements of a stack.
 * This swaps both the values and the indices, which is crucial
 * for maintaining the correct order in the sorting algorithm. */
void	swap(t_node *stack)
{
	int	temp;              /* Temporary variable for swapping */

	if (!stack || !stack->next)
		return ;             /* Safety check for stacks with < 2 elements */
	
	/* Swap the values */
	temp = stack->value;
	stack->value = stack->next->value;
	stack->next->value = temp;
	
	/* Swap the indices */
	temp = stack->index;
	stack->index = stack->next->index;
	stack->next->index = temp;
}

/* Swap the top two elements of stack_a (sa operation) */
void	sa(t_node **stack_a)
{
	swap(*stack_a);         /* Perform swap operation on stack A */
	print_operation("sa");  /* Output the operation */
}

/* Swap the top two elements of stack_b (sb operation) */
void	sb(t_node **stack_b)
{
	swap(*stack_b);         /* Perform swap operation on stack B */
	print_operation("sb");  /* Output the operation */
}

/* Swap the top two elements of both stacks simultaneously (ss operation) */
void	ss(t_node **stack_a, t_node **stack_b)
{
	swap(*stack_a);         /* Swap top elements of stack A */
	swap(*stack_b);         /* Swap top elements of stack B */
	print_operation("ss");  /* Output the operation */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Return the absolute value of a number.
 * This is used primarily in cost calculations to find the most efficient moves. */
int	absolute_value(int nb)
{
	if (nb < 0)
		return (-nb);       /* Return positive equivalent if negative */
	return (nb);            /* Return as is if already positive */
}

/* Convert a string to a long integer.
 * This extended version of atoi handles spaces, signs, and checks for overflow. */
long	ft_atoi(const char *str)
{
	long	result;         /* Store the converted number */
	int		sign;           /* Store the sign (1 for positive, -1 for negative) */
	int		i;              /* Index for traversing the string */

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;                /* Skip whitespaces and control characters */
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;      /* Set sign to negative if '-' found */
		i++;                /* Move past the sign */
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');  /* Build the number */
		i++;                /* Move to next character */
	}
	return (result * sign); /* Return the final number with appropriate sign */
}

/* Check if a character is a digit (0-9).
 * Used for validation during input parsing. */
int	is_digit(char c)
{
	return (c >= '0' && c <= '9');  /* Return true if c is a digit */
}

/* Check if a character is a sign (+ or -).
 * Used for validation during input parsing. */
int	is_sign(char c)
{
	return (c == '+' || c == '-');  /* Return true if c is a sign */
}

/* Compare two strings lexicographically.
 * Returns the difference between the first different characters. */
int	str_compare(const char *s1, const char *s2)
{
	int	i;               /* Index for traversing the strings */

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;              /* Skip matching characters */
	return (s1[i] - s2[i]);  /* Return difference at first mismatch */
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */

#include "push_swap.h"

/* Check if a string represents zero.
 * This function is needed to detect multiple zeroes in input,
 * which would be considered duplicates. */
int	is_zero(char *str)
{
	int	i;                /* Index for traversing the string */

	i = 0;
	if (is_sign(str[i]))
		i++;               /* Skip sign if present */
	while (str[i] && str[i] == '0')
		i++;               /* Skip all '0' characters */
	if (str[i] != '\0')
		return (0);        /* Return false if any non-zero character found */
	return (1);            /* Return true if string contains only zeroes */
}

/* Check if there are any duplicate values in the command line arguments. 
 * This is a simple check that works when arguments are separate. */
int	has_duplicates(char **av)
{
	int	i;                /* Index for first argument */
	int	j;                /* Index for second argument */

	i = 1;
	while (av[i])
	{
		j = 1;
		while (av[j])
		{
			if (i != j && ft_atoi(av[i]) == ft_atoi(av[j]))
				return (1);  /* Return true if duplicate found */
			j++;
		}
		i++;
	}
	return (0);            /* Return false if no duplicates */
}

/* Helper function to extract and validate numbers from a string.
 * This handles cases where multiple numbers are in a single argument.
 * Returns 0 if invalid numbers are found, 1 otherwise. */
static int	check_values_in_str(char *str, long *values, int *count)
{
	int		j;             /* Index for traversing the input string */
	int		k;             /* Index for building the number buffer */
	char	buffer[12];     /* Buffer to hold each extracted number */
	long	value;          /* Extracted numeric value */

	j = 0;
	while (str[j])
	{
		while (str[j] == ' ')
			j++;            /* Skip spaces */
		if (str[j] == '\0')
			break ;         /* End of string */
		k = 0;
		while (str[j] && str[j] != ' ' && k < 11)
			buffer[k++] = str[j++];  /* Extract one number */
		buffer[k] = '\0';   /* Null-terminate the buffer */
		if (!is_number(buffer))
			return (0);     /* Return false if not a valid number */
		value = ft_atoi(buffer);
		if (value > 2147483647 || value < -2147483648)
			return (0);     /* Return false if number exceeds INT range */
		values[(*count)++] = value;  /* Store valid number */
	}
	return (1);            /* Return true if all numbers were valid */
}

/* Helper function to check for duplicates in the extracted values.
 * Also counts occurrences of zero, as multiple zeroes are considered duplicates.
 * Returns 1 if duplicates are found, 0 otherwise. */
static int	check_duplicates_in_values(long *values, int count, int *zero_count)
{
	int	i;               /* Index for first value */
	int	j;               /* Index for second value */

	i = 0;
	*zero_count = 0;
	while (i < count)
	{
		if (values[i] == 0)
			(*zero_count)++;  /* Count zeroes */
		j = i + 1;
		while (j < count)
		{
			if (values[i] == values[j])
				return (1);   /* Return true if duplicate found */
			j++;
		}
		i++;
	}
	return (0);             /* Return false if no duplicates */
}

/* Main validation function for input.
 * Checks if all arguments are valid integers, no duplicates,
 * and within the INT range. Returns 1 if input is valid, 0 otherwise. */
int	check_input(int ac, char **av)
{
	int		i;              /* Loop counter for arguments */
	int		zero_count;     /* Count of zeroes found */
	int		found_token;    /* Flag to track if any valid token was found */
	long	values[1024];   /* Array to store all extracted values */
	int		count;          /* Count of total values extracted */

	if (ac < 2)
		return (0);          /* Return false if no arguments provided */
	i = 1;
	zero_count = 0;
	found_token = 0;
	count = 0;
	while (i < ac)
	{
		if (!check_values_in_str(av[i], values, &count))
			return (0);      /* Return false if invalid values found */
		found_token = (count > 0);  /* Set flag if any values were found */
		i++;
	}
	/* Check for no values, duplicates, multiple zeroes, or command-line duplicates */
	if (!found_token || check_duplicates_in_values(values, count, &zero_count)
		|| zero_count > 1 || has_duplicates(av))
		return (0);          /* Return false if any validation fails */
	return (1);              /* Return true if all validations pass */
}
