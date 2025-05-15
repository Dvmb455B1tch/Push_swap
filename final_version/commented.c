/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commented.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvmb455b1tch <dvmb455b1tch@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:44:50 by riramana          #+#    #+#             */
/*   Updated: 2025/05/15 14:52:53 by dvmb455b1tc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_cost(t_node **stack_a, t_node **stack_b)
{
    /* This function calculates the cost of moving each element in stack_b to its target position in stack_a */
    t_node	*current;           /* Pointer to iterate through stack_b */
    int		size_a;             /* Size of stack_a */
    int		size_b;             /* Size of stack_b */

    /* Return if either stack is invalid */
    if (!stack_a || !*stack_a || !stack_b || !*stack_b)
        return ;
    
    /* Get the size of both stacks */
    size_a = stack_size(*stack_a);
    size_b = stack_size(*stack_b);
    
    /* Iterate through each element in stack_b */
    current = *stack_b;
    while (current)
    {
        /* Calculate cost to move element to the top of stack_b */
        current->cost_b = current->position;
        
        /* If element is in the bottom half, calculate cost using reverse rotate (negative value) */
        if (current->position > size_b / 2)
            current->cost_b = (size_b - current->position) * -1;
        
        /* Calculate cost to move target position to the top of stack_a */
        current->cost_a = current->target_pos;
        
        /* If target position is in the bottom half, calculate cost using reverse rotate (negative value) */
        if (current->target_pos > size_a / 2)
            current->cost_a = (size_a - current->target_pos) * -1;
        
        /* Move to the next element in stack_b */
        current = current->next;
    }
}

void	execute_cheapest_move(t_node **stack_a, t_node **stack_b)
{
    /* This function finds and executes the cheapest move to sort one element from stack_b to stack_a */
    t_node	*current;           /* Pointer to iterate through stack_b */
    int		cheapest_cost;      /* Total cost of the cheapest move found */
    int		cost_a;             /* Cost for stack_a of the cheapest move */
    int		cost_b;             /* Cost for stack_b of the cheapest move */

    /* Return if either stack is invalid */
    if (!stack_a || !*stack_a || !stack_b || !*stack_b)
        return ;
    
    /* Start from the top of stack_b */
    current = *stack_b;
    
    /* Initialize cheapest_cost to maximum integer value */
    cheapest_cost = 2147483647;
    
    /* Iterate through each element in stack_b to find the cheapest move */
    while (current)
    {
        /* If total absolute cost is less than current cheapest cost */
        if (absolute_value(current->cost_a) + absolute_value(current->cost_b)
            < absolute_value(cheapest_cost))
        {
            /* Update cheapest cost and store the associated costs for both stacks */
            cheapest_cost = absolute_value(current->cost_a)
                + absolute_value(current->cost_b);
            cost_a = current->cost_a;
            cost_b = current->cost_b;
        }
        /* Move to the next element in stack_b */
        current = current->next;
    }
    
    /* Execute the cheapest move found */
    execute_move(stack_a, stack_b, cost_a, cost_b);
}

/* ************************************************************************** */
/*                                                                            */
/*   input.c - Functions for parsing and validating input                     */
/*                                                                            */
/* ************************************************************************** */

static void	handle_parse_error(t_node **stack_a)
{
    /* This function handles parsing errors by freeing allocated memory and exiting */
    free_stack(stack_a);    /* Free the stack before exiting */
    write(2, "Error\n", 6);   /* Write error message to stderr */
    exit(1);                /* Exit with error code 1 */
}

static void	parse_line(t_node **stack_a, char *str)
{
    /* This function parses a line of input and adds values to stack_a */
    int		j;              /* Index for iterating through the string */
    int		k;              /* Index for storing characters in buffer */
    long	num;            /* Stores converted number (long to check for overflow) */
    t_node	*new;           /* New node to be added to the stack */
    char	buffer[12];     /* Buffer to store one number as a string (max 11 chars for INT_MIN) */

    j = 0;
    while (str[j])
    {
        /* Skip spaces */
        while (str[j] == ' ')
            j++;
        
        /* Break if end of string */
        if (str[j] == '\0')
            break ;
        
        /* Extract one number into buffer */
        k = 0;
        while (str[j] && str[j] != ' ' && k < 11)
            buffer[k++] = str[j++];
        buffer[k] = '\0';
        
        /* Convert string to number */
        num = ft_atoi(buffer);
        
        /* Check if number fits in an int */
        if (num > 2147483647 || num < -2147483648)
            handle_parse_error(stack_a);
        
        /* Create a new node with the number */
        new = new_node((int)num);
        if (!new)
            handle_parse_error(stack_a);
        
        /* Add the new node to the stack */
        add_node_back(stack_a, new);
    }
}

t_node	*parse_input(int ac, char **av)
{
    /* This function parses command line arguments into a stack */
    t_node	*stack_a;       /* The stack to build */
    int		i;              /* Counter for arguments */

    stack_a = NULL;         /* Initialize stack as empty */
    i = 1;                  /* Start from first argument (index 1) */
    
    /* Process each argument */
    while (i < ac)
    {
        parse_line(&stack_a, av[i]);   /* Parse current argument */
        i++;                            /* Move to next argument */
    }
    
    /* Return the constructed stack */
    return (stack_a);
}

void	assign_index(t_node *stack_a, int size)
{
    /* This function assigns sorting indices to the elements in stack_a */
    /* Indices are assigned from highest to lowest, with highest value getting smallest index */
    t_node	*current;       /* Pointer to iterate through the stack */
    t_node	*highest;       /* Pointer to the node with highest unindexed value */
    int		value;          /* Current highest value found */
    int		i;              /* Counter for indices */

    /* Return if stack is empty */
    if (!stack_a)
        return ;
    
    /* Start from highest index (size-1) and work down to 0 */
    i = size;
    while (--i >= 0)
    {
        current = stack_a;
        value = -2147483648;    /* Initialize with minimum integer value */
        highest = NULL;
        
        /* Find node with highest value that hasn't been indexed yet */
        while (current)
        {
            if (current->value > value && current->index == 0)
            {
                value = current->value;
                highest = current;
            }
            current = current->next;
        }
        
        /* Assign current index to the highest value found */
        if (highest)
            highest->index = i;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*   main.c - Entry point of the push_swap program                           */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
    /* This is the main function that controls the program flow */
    t_node	*stack_a;       /* Stack A - holds the initial unsorted numbers */
    t_node	*stack_b;       /* Stack B - initially empty, used for sorting */
    int		size;           /* Size of stack A */

    /* Do nothing if no arguments */
    if (ac < 2)
        return (0);
    
    /* Check if input is valid */
    if (!check_input(ac, av))
    {
        write(2, "Error\n", 6);   /* Write error message to stderr */
        return (1);               /* Return error code */
    }
    
    /* Initialize stack B as empty */
    stack_b = NULL;
    
    /* Parse input arguments to create stack A */
    stack_a = parse_input(ac, av);
    
    /* Get size of stack A */
    size = stack_size(stack_a);
    
    /* Assign sorting indices to elements in stack A */
    assign_index(stack_a, size);
    
    /* Only sort if not already sorted */
    if (!is_sorted(stack_a))
        sort(&stack_a, &stack_b);
    
    /* Free allocated memory */
    free_stack(&stack_a);
    free_stack(&stack_b);
    
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*   movements.c - Functions to execute sorting operations                    */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	execute_reverse_rotate_both(t_node **stack_a, t_node **stack_b,
        int *cost_a, int *cost_b)
{
    /* This function performs reverse rotations on both stacks simultaneously when possible */
    /* Used when both stacks need reverse rotation (negative costs) */
    while (*cost_a < 0 && *cost_b < 0)
    {
        (*cost_a)++;    /* Decrease absolute cost for stack A */
        (*cost_b)++;    /* Decrease absolute cost for stack B */
        rrr(stack_a, stack_b);  /* Perform reverse rotation on both stacks */
    }
}

static void	execute_rotate_both(t_node **stack_a, t_node **stack_b,
        int *cost_a, int *cost_b)
{
    /* This function performs rotations on both stacks simultaneously when possible */
    /* Used when both stacks need rotation (positive costs) */
    while (*cost_a > 0 && *cost_b > 0)
    {
        (*cost_a)--;    /* Decrease cost for stack A */
        (*cost_b)--;    /* Decrease cost for stack B */
        rr(stack_a, stack_b);   /* Perform rotation on both stacks */
    }
}

void	move_stack_a(t_node **stack_a, int *cost)
{
    /* This function moves stack A to position based on cost */
    while (*cost)
    {
        if (*cost > 0)
        {
            /* Positive cost means rotate */
            ra(stack_a);     /* Rotate stack A */
            (*cost)--;       /* Decrease remaining rotations */
        }
        else if (*cost < 0)
        {
            /* Negative cost means reverse rotate */
            rra(stack_a);    /* Reverse rotate stack A */
            (*cost)++;       /* Decrease remaining reverse rotations */
        }
    }
}

void	move_stack_b(t_node **stack_b, int *cost)
{
    /* This function moves stack B to position based on cost */
    while (*cost)
    {
        if (*cost > 0)
        {
            /* Positive cost means rotate */
            rb(stack_b);     /* Rotate stack B */
            (*cost)--;       /* Decrease remaining rotations */
        }
        else if (*cost < 0)
        {
            /* Negative cost means reverse rotate */
            rrb(stack_b);    /* Reverse rotate stack B */
            (*cost)++;       /* Decrease remaining reverse rotations */
        }
    }
}

void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
    /* This function executes the optimal sequence of moves to place a B element in the correct position in A */
    
    /* First optimize by doing simultaneous operations when possible */
    if (cost_a < 0 && cost_b < 0)
        /* If both stacks need reverse rotation, do them together */
        execute_reverse_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
    else if (cost_a > 0 && cost_b > 0)
        /* If both stacks need rotation, do them together */
        execute_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
    
    /* Finish positioning stack A */
    move_stack_a(stack_a, &cost_a);
    
    /* Finish positioning stack B */
    move_stack_b(stack_b, &cost_b);
    
    /* Push top element from B to A */
    pa(stack_a, stack_b);
}

/* ************************************************************************** */
/*                                                                            */
/*   position.c - Functions to calculate positions                            */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_position(t_node **stack)
{
    /* This function sets the current position of each element in the stack */
    t_node	*current;   /* Pointer to iterate through the stack */
    int		i;          /* Position counter */

    /* Return if stack is invalid */
    if (!stack || !*stack)
        return ;
    
    /* Iterate through stack and set positions */
    current = *stack;
    i = 0;
    while (current)
    {
        current->position = i;  /* Set position of current node */
        current = current->next;  /* Move to next node */
        i++;                      /* Increment position counter */
    }
}

int	get_lowest_index_position(t_node **stack)
{
    /* This function finds the position of the element with the lowest index */
    t_node	*current;       /* Pointer to iterate through the stack */
    int		lowest_index;   /* Lowest index found */
    int		lowest_pos;     /* Position of the lowest index */

    /* Return -1 if stack is invalid */
    if (!stack || !*stack)
        return (-1);
    
    /* Set positions for all elements */
    set_position(stack);
    
    /* Initialize search variables */
    current = *stack;
    lowest_index = 2147483647;  /* Start with maximum value */
    lowest_pos = 0;
    
    /* Find element with lowest index */
    while (current)
    {
        if (current->index < lowest_index)
        {
            lowest_index = current->index;
            lowest_pos = current->position;
        }
        current = current->next;
    }
    
    /* Return position of lowest index */
    return (lowest_pos);
}

static int	find_min_index_position(t_node **stack_a)
{
    /* This function finds the position of the element with the minimum index in stack A */
    t_node	*current;       /* Pointer to iterate through the stack */
    int		target_index;   /* Minimum index found */
    int		target_pos;     /* Position of minimum index */

    /* Initialize variables */
    current = *stack_a;
    target_index = 2147483647;  /* Start with maximum value */
    target_pos = 0;
    
    /* Find element with minimum index */
    while (current)
    {
        if (current->index < target_index)
        {
            target_index = current->index;
            target_pos = current->position;
        }
        current = current->next;
    }
    
    /* Return position of minimum index */
    return (target_pos);
}

static int	find_target_position(t_node **stack_a, int b_index)
{
    /* This function finds the target position in stack A for an element from stack B */
    t_node	*current;       /* Pointer to iterate through stack A */
    int		target_index;   /* Index of target element in stack A */
    int		target_pos;     /* Position of target element */

    /* Initialize variables */
    current = *stack_a;
    target_index = 2147483647;  /* Start with maximum value */
    target_pos = 0;
    
    /* Find the smallest element in A that is larger than the B element */
    while (current)
    {
        if (current->index > b_index && current->index < target_index)
        {
            target_index = current->index;
            target_pos = current->position;
        }
        current = current->next;
    }
    
    /* If no larger element found, target is the smallest element in A */
    if (target_index == 2147483647)
        target_pos = find_min_index_position(stack_a);
    
    /* Return target position */
    return (target_pos);
}

void	set_target_position(t_node **stack_a, t_node **stack_b)
{
    /* This function sets the target position in stack A for each element in stack B */
    t_node	*current_b;     /* Pointer to iterate through stack B */

    /* Return if either stack is invalid */
    if (!stack_a || !*stack_a || !stack_b || !*stack_b)
        return ;
    
    /* Set current positions for both stacks */
    set_position(stack_a);
    set_position(stack_b);
    
    /* Find target position for each element in stack B */
    current_b = *stack_b;
    while (current_b)
    {
        current_b->target_pos = find_target_position(stack_a, current_b->index);
        current_b = current_b->next;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*   print_operation.c - Function to print operations                         */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_operation(char *op)
{
    /* This function prints an operation name followed by a newline */
    int	i;              /* Counter for string length */

    /* Calculate string length */
    i = 0;
    while (op[i])
        i++;
    
    /* Write operation name to stdout */
    write(1, op, i);
    
    /* Write newline */
    write(1, "\n", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*   push.c - Functions for push operations                                   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_node **src, t_node **dest)
{
    /* This function pushes the top element from source stack to destination stack */
    t_node	*temp;      /* Temporary pointer to the top element */

    /* Do nothing if source stack is empty */
    if (!*src)
        return ;
    
    /* Store the top element of source stack */
    temp = *src;
    
    /* Remove top element from source stack */
    *src = (*src)->next;
    
    /* Add element to the top of destination stack */
    temp->next = *dest;
    *dest = temp;
}

void	pa(t_node **stack_a, t_node **stack_b)
{
    /* This function pushes the top element from stack B to stack A */
    push(stack_b, stack_a);     /* Perform push operation */
    print_operation("pa");      /* Print the operation */
}

void	pb(t_node **stack_a, t_node **stack_b)
{
    /* This function pushes the top element from stack A to stack B */
    push(stack_a, stack_b);     /* Perform push operation */
    print_operation("pb");      /* Print the operation */
}

/* ************************************************************************** */
/*                                                                            */
/*   reverse_rotate.c - Functions for reverse rotate operations               */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_node **stack)
{
    /* This function moves the bottom element to the top of the stack */
    t_node	*last;          /* Pointer to the last element */
    t_node	*second_last;   /* Pointer to the second last element */

    /* Do nothing if stack has less than 2 elements */
    if (!*stack || !(*stack)->next)
        return ;
    
    /* Get the last and second last elements */
    last = get_last_node(*stack);
    second_last = get_second_last_node(*stack);
    
    /* Move last element to the top */
    last->next = *stack;
    *stack = last;
    
    /* Set new end of stack */
    second_last->next = NULL;
}

void	rra(t_node **stack_a)
{
    /* This function performs reverse rotate on stack A */
    reverse_rotate(stack_a);    /* Perform reverse rotate */
    print_operation("rra");     /* Print the operation */
}

void	rrb(t_node **stack_b)
{
    /* This function performs reverse rotate on stack B */
    reverse_rotate(stack_b);    /* Perform reverse rotate */
    print_operation("rrb");     /* Print the operation */
}

void	rrr(t_node **stack_a, t_node **stack_b)
{
    /* This function performs reverse rotate on both stacks */
    reverse_rotate(stack_a);    /* Reverse rotate stack A */
    reverse_rotate(stack_b);    /* Reverse rotate stack B */
    print_operation("rrr");     /* Print the combined operation */
}

/* ************************************************************************** */
/*                                                                            */
/*   rotate.c - Functions for rotate operations                               */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_node **stack)
{
    /* This function moves the top element to the bottom of the stack */
    t_node	*temp;      /* Temporary pointer to the top element */
    t_node	*last;      /* Pointer to the last element */

    /* Do nothing if stack has less than 2 elements */
    if (!*stack || !(*stack)->next)
        return ;
    
    /* Store the top element */
    temp = *stack;
    
    /* Update the top of the stack */
    *stack = (*stack)->next;
    
    /* Find the end of the stack */
    last = get_last_node(*stack);
    
    /* Add the original top element to the end */
    temp->next = NULL;
    last->next = temp;
}

void	ra(t_node **stack_a)
{
    /* This function performs rotate on stack A */
    rotate(stack_a);        /* Perform rotate */
    print_operation("ra");  /* Print the operation */
}

void	rb(t_node **stack_b)
{
    /* This function performs rotate on stack B */
    rotate(stack_b);        /* Perform rotate */
    print_operation("rb");  /* Print the operation */
}

void	rr(t_node **stack_a, t_node **stack_b)
{
    /* This function performs rotate on both stacks */
    rotate(stack_a);        /* Rotate stack A */
    rotate(stack_b);        /* Rotate stack B */
    print_operation("rr");  /* Print the combined operation */
}

/* ************************************************************************** */
/*                                                                            */
/*   sort.c - Functions for sorting algorithms                                */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_node **stack)
{
    /* This function sorts exactly three elements in the stack */
    int	highest_index;     /* Index of the highest element */

    /* Return if stack is invalid or has fewer than 3 elements */
    if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
        return ;
    
    /* Return if already sorted */
    if (is_sorted(*stack))
        return ;
    
    /* Find the highest index value */
    highest_index = (*stack)->index;
    if ((*stack)->next->index > highest_index)
        highest_index = (*stack)->next->index;
    if ((*stack)->next->next->index > highest_index)
        highest_index = (*stack)->next->next->index;
    
    /* If highest element is at the top, rotate it to the bottom */
    if ((*stack)->index == highest_index)
        ra(stack);
    /* If highest element is in the middle, reverse rotate to move it to the bottom */
    else if ((*stack)->next->index == highest_index)
        rra(stack);
    
    /* If the first two elements are not in order, swap them */
    if ((*stack)->index > (*stack)->next->index)
        sa(stack);
}

static void	push_all_except_three(t_node **stack_a, t_node **stack_b)
{
    /* This function pushes all elements except three to stack B */
    int	size;           /* Size of stack A */
    int	pushed;         /* Count of elements pushed to B */
    int	i;              /* Loop counter */

    /* Get size of stack A */
    size = stack_size(*stack_a);
    
    /* If size <= 3, nothing to push */
    if (size <= 3)
        return ;
    
    /* Initialize counters */
    pushed = 0;
    i = 0;
    
    /* For larger stacks, first push smaller half of elements to B */
    while (size > 6 && i < size && pushed < size / 2)
    {
        if ((*stack_a)->index <= size / 2)
        {
            /* If current element is in the smaller half, push it to B */
            pb(stack_a, stack_b);
            pushed++;
        }
        else
            /* Otherwise, rotate it to the bottom */
            ra(stack_a);
        i++;
    }
    
    /* Push remaining elements until only 3 are left in stack A */
    while (size - pushed > 3)
    {
        pb(stack_a, stack_b);
        pushed++;
    }
}

void	shift_stack(t_node **stack_a)
{
    /* This function rotates stack A until the smallest element is at the top */
    int	lowest_pos;     /* Position of the element with lowest index */
    int	size;           /* Size of the stack */

    /* Return if stack is invalid */
    if (!stack_a || !*stack_a)
        return ;
    
    /* Get stack size and position of smallest element */
    size = stack_size(*stack_a);
    lowest_pos = get_lowest_index_position(stack_a);
    
    /* If smallest element is in the bottom half */
    if (lowest_pos > size / 2)
    {
        /* Use reverse rotate to bring it to the top (shorter path) */
        while (lowest_pos < size)
        {
            rra(stack_a);
            lowest_pos++;
        }
    }
    else
    {
        /* Use rotate to bring it to the top */
        while (lowest_pos > 0)
        {
            ra(stack_a);
            lowest_pos--;
        }
    }
}

void	sort(t_node **stack_a, t_node **stack_b)
{
    /* This is the main sorting function */
    
    /* Return if stack is invalid */
    if (!stack_a || !*stack_a)
        return ;
    
    /* Return if already sorted */
    if (is_sorted(*stack_a))
        return ;
    
    /* Special case for 2 elements: just swap if needed */
    if (stack_size(*stack_a) == 2)
    {
        if ((*stack_a)->value > (*stack_a)->next->value)
            sa(stack_a);
        return ;
    }
    
    /* Special case for 3 elements: use optimized sort_three function */
    if (stack_size(*stack_a) == 3)
    {
        sort_three(stack_a);
        return ;
    }
    
    /* For more than 3 elements: */
    /* 1. Push all except 3 elements to stack B */
    push_all_except_three(stack_a, stack_b);
    
    /* 2. Sort the remaining 3 elements in stack A */
    sort_three(stack_a);
    
    /* 3. Insert elements from B back to A in the correct position */
    while (*stack_b)
    {
        /* Calculate target positions for all elements in B */
        set_target_position(stack_a, stack_b);
        
        /* Calculate cost of moving each element to its target position */
        calculate_cost(stack_a, stack_b);
        
        /* Execute the cheapest move */
        execute_cheapest_move(stack_a, stack_b);
    }
    
    /* 4. Final rotation to put smallest element at the top */
    if (!is_sorted(*stack_a))
        shift_stack(stack_a);
}

/* ************************************************************************** */
/*                                                                            */
/*   stack.c - Functions for stack manipulation                               */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*new_node(int value)
{
    /* This function creates a new stack node with the given value */
    t_node	*node;      /* Pointer to the new node */

    /* Allocate memory for new node */
    node = malloc(sizeof(t_node));
    if (!node)
        return (NULL);
    
    /* Initialize node values */
    node->value = value;
    node->index = 0;
    node->position = -1;
    node->target_pos = -1;
    node->cost_a = -1;
    node->cost_b = -1;
    node->next = NULL;
    
    /* Return the new node */
    return (node);
}

void	add_node_back(t_node **stack, t_node *new)
{
    /* This function adds a new node to the end of the stack */
    t_node	*last;      /* Pointer to the last node in the stack */

    /* Return if new node is NULL */
    if (!new)
        return ;
    
    /* If stack is empty, new node becomes the stack */
    if (!*stack)
    {
        *stack = new;
        return ;
    }
    
    /* Find the last node */
    last = get_last_node(*stack);
    
    /* Add new node after the last node */
    last->next = new;
}

t_node	*get_last_node(t_node *stack)
{
    /* This function finds and returns the last node in the stack */
    if (!stack)
        return (NULL);    /* Return NULL if stack is empty */
    
    /* Traverse to the end of the stack */
    while (stack->next)
        stack = stack->next;
    
    /* Return the last node */
    return (stack);
}

t_node	*get_second_last_node(t_node *stack)
{
    /* This function finds and returns the second-to-last node in the stack */
    if (!stack || !stack->next)
        return (NULL);    /* Return NULL if stack has fewer than 2 elements */
    
    /* Traverse until we reach the second-to-last node */
    while (stack->next && stack->next->next)
        stack = stack->next;
    
    /* Return the second-to-last node */
    return (stack);
}

int	stack_size(t_node *stack)
{
    /* This function counts the number of elements in the stack */
    int	size;    /* Counter for stack size */

    size = 0;
    
    /* Count each node while traversing the stack */
    while (stack)
    {
        size++;
        stack = stack->next;
    }
    
    /* Return the final count */
    return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*   stack_utils.c - Functions for freeing memory                             */
/*                                                                            */
/* ************************************************************************** */

void	free_stack(t_node **stack)
{
    /* This function frees all memory allocated for the stack */
    t_node	*tmp;    /* Temporary pointer for traversal */

    /* Return if stack doesn't exist or is already empty */
    if (!stack || !*stack)
        return ;

    /* Free each node in the stack */
    while (*stack)
    {
        tmp = (*stack)->next;   /* Save pointer to next node */
        free(*stack);           /* Free current node */
        *stack = tmp;           /* Move to next node */
    }
    
    /* Set stack pointer to NULL to prevent dangling references */
    *stack = NULL;
}

int	is_sorted(t_node *stack)
{
    /* This function checks if the stack is sorted in ascending order */
    
    /* Traverse stack and check if each value is less than the next */
    while (stack && stack->next)
    {
        if (stack->value > stack->next->value)
            return (0);    /* Return 0 (false) if not sorted */
        stack = stack->next;
    }
    
    /* Return 1 (true) if stack is sorted or has 0-1 elements */
    return (1);
}

void	free_and_exit(t_node **stack_a, t_node **stack_b)
{
    /* This function frees both stacks, prints an error message, and exits */
    
    /* Free both stacks */
    free_stack(stack_a);
    free_stack(stack_b);
    
    /* Print error message to stderr */
    write(2, "Error\n", 6);
    
    /* Exit with error code */
    exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*   swap.c - Functions for swap operations                                   */
/*                                                                            */
/* ************************************************************************** */

void	swap(t_node *stack)
{
    /* This function swaps the top two elements of the stack */
    int	temp;    /* Temporary variable for swapping */

    /* Do nothing if stack has fewer than 2 elements */
    if (!stack || !stack->next)
        return ;

    /* Swap values */
    temp = stack->value;
    stack->value = stack->next->value;
    stack->next->value = temp;
    
    /* Swap indices */
    temp = stack->index;
    stack->index = stack->next->index;
    stack->next->index = temp;
}

void	sa(t_node **stack_a)
{
    /* This function performs swap operation on stack A */
    swap(*stack_a);           /* Perform swap */
    print_operation("sa");    /* Print the operation */
}

void	sb(t_node **stack_b)
{
    /* This function performs swap operation on stack B */
    swap(*stack_b);           /* Perform swap */
    print_operation("sb");    /* Print the operation */
}

void	ss(t_node **stack_a, t_node **stack_b)
{
    /* This function performs swap operation on both stacks */
    swap(*stack_a);           /* Swap stack A */
    swap(*stack_b);           /* Swap stack B */
    print_operation("ss");    /* Print the combined operation */
}

/* ************************************************************************** */
/*                                                                            */
/*   utils.c - General utility functions                                      */
/*                                                                            */
/* ************************************************************************** */

int	absolute_value(int nb)
{
    /* This function returns the absolute value of a number */
    if (nb < 0)
        return (-nb);    /* Return positive version of negative number */
    return (nb);         /* Return number as is if already positive */
}

long	ft_atoi(const char *str)
{
    /* This function converts a string to a long integer (similar to atoi) */
    long	result;    /* Accumulator for the result */
    int		sign;      /* Sign of the number (+1 or -1) */
    int		i;         /* Index for string traversal */

    /* Initialize variables */
    result = 0;
    sign = 1;
    i = 0;
    
    /* Skip whitespace */
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    
    /* Handle sign character */
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;    /* Set sign to negative */
        i++;
    }
    
    /* Convert digits to number */
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');    /* Add digit to result */
        i++;
    }
    
    /* Return result with appropriate sign */
    return (result * sign);
}

int	is_digit(char c)
{
    /* This function checks if a character is a digit */
    return (c >= '0' && c <= '9');
}

int	is_sign(char c)
{
    /* This function checks if a character is a sign (+ or -) */
    return (c == '+' || c == '-');
}

int	str_compare(const char *s1, const char *s2)
{
    /* This function compares two strings (similar to strcmp) */
    int	i;    /* Index for string traversal */

    i = 0;
    
    /* Compare characters until a difference is found or end of string */
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    
    /* Return difference between first differing characters */
    return (s1[i] - s2[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*   validation.c - Functions for input validation                            */
/*                                                                            */
/* ************************************************************************** */

int	is_number(char *str)
{
    /* This function checks if a string represents a valid number */
    int	i;    /* Index for string traversal */

    i = 0;
    
    /* Handle optional sign at the beginning */
    if (is_sign(str[i]) && str[i + 1] != '\0')
        i++;
    
    /* Check that all remaining characters are digits */
    while (str[i] && is_digit(str[i]))
        i++;
    
    /* If we reached the end of string, it's a valid number */
    if (str[i] != '\0')
        return (0);    /* Not a valid number */
    return (1);        /* Valid number */
}

int	is_zero(char *str)
{
    /* This function checks if a string represents zero */
    int	i;    /* Index for string traversal */

    i = 0;
    
    /* Skip optional sign */
    if (is_sign(str[i]))
        i++;
    
    /* Check if all remaining characters are '0' */
    while (str[i] && str[i] == '0')
        i++;
    
    /* If we reached the end of string, it's zero */
    if (str[i] != '\0')
        return (0);    /* Not zero */
    return (1);        /* Is zero */
}

int	has_duplicates(char **av)
{
    /* This function checks if there are duplicate numbers in the arguments */
    int	i;    /* Index for first argument */
    int	j;    /* Index for second argument (to compare with first) */

    i = 1;
    
    /* Compare each argument with all other arguments */
    while (av[i])
    {
        j = 1;
        while (av[j])
        {
            /* If same value appears in different positions, it's a duplicate */
            if (i != j && ft_atoi(av[i]) == ft_atoi(av[j]))
                return (1);    /* Duplicate found */
            j++;
        }
        i++;
    }
    
    /* No duplicates found */
    return (0);
}

static int	check_tokens(char *str, int *zero_count, int *found_token)
{
    /* This function checks if a string contains valid number tokens */
    int		j;         /* Index for traversing the string */
    int		k;         /* Index for building the token buffer */
    char	buffer[12];    /* Buffer to store one token at a time */

    j = 0;
    
    /* Process each token in the string */
    while (str[j])
    {
        /* Skip spaces */
        while (str[j] == ' ')
            j++;
        
        /* Break if end of string */
        if (str[j] == '\0')
            break ;
        
        /* Extract one token into buffer */
        k = 0;
        while (str[j] && str[j] != ' ' && k < 11)
            buffer[k++] = str[j++];
        buffer[k] = '\0';
        
        /* Check if token is a valid number */
        if (!is_number(buffer))
            return (0);    /* Invalid token found */
        
        /* Update counters */
        *zero_count += is_zero(buffer);    /* Count zeros for duplicate zero check */
        *found_token = 1;                  /* Mark that we found at least one token */
    }
    
    /* All tokens are valid */
    return (1);
}

int	check_input(int ac, char **av)
{
    /* This function validates the entire input for the push_swap program */
    int	i;              /* Index for arguments */
    int	zero_count;     /* Count of zero values (to check for duplicates) */
    int	found_token;    /* Flag to ensure we have at least one valid token */

    /* No arguments provided */
    if (ac < 2)
        return (0);
    
    /* Initialize counters */
    i = 1;
    zero_count = 0;
    found_token = 0;
    
    /* Process each argument */
    while (i < ac)
    {
        /* Check if argument contains valid tokens */
        if (!check_tokens(av[i], &zero_count, &found_token))
            return (0);    /* Invalid tokens found */
        i++;
    }
    
    /* Final validation checks */
    if (!found_token                  /* No valid tokens found */
        || zero_count > 1             /* More than one zero (duplicate zeros) */
        || has_duplicates(av))        /* Other duplicates found */
        return (0);                   /* Input is invalid */
    
    /* Input is valid */
    return (1);
}
