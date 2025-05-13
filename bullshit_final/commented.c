I'd like you to indent EVERY LINE of code in this push swap project that is about sorting random numbers with a limited set of instructions with comments that gives a good grasp of what they do for the sake of wanted output without modifying the code itself , the big idea is to "textualize" the algorithm so i can see the different steps of the compilation, i'm gonna put here my code and the push swap subject itself

Modifier
I'll help you indent the code with explanatory comments that clarify the algorithm's steps and functions without modifying the code itself. This will make it easier to understand the push_swap project's purpose: sorting a stack of random numbers using limited operations.


#include "push_swap.h"
/**
 * Calculate the cost to move each element in stack B to its target position in stack A
 * - cost_b: cost to move element to top of stack B
 * - cost_a: cost to move target position to top of stack A
 * Positive cost means rotate (r), negative cost means reverse rotate (rr)
 */
void	calculate_cost(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;        // Pointer to traverse through stack B
	int	size_a;              // Size of stack A for position calculations
	int	size_b;              // Size of stack B for position calculations

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;            // Safety check: Make sure both stacks exist and aren't empty
	
	size_a = stack_size(*stack_a);  // Get stack A size to determine optimal rotation direction
	size_b = stack_size(*stack_b);  // Get stack B size to determine optimal rotation direction
	current = *stack_b;             // Start with the top element of stack B
	
	while (current)                 // Loop through each element in stack B
	{
		// Calculate cost to move to top of stack B
		current->cost_b = current->position;  // Initial cost is current position (rotations needed)
		if (current->position > size_b / 2)   // If element is in bottom half of stack
			current->cost_b = (size_b - current->position) * -1;  // Use reverse rotations (negative cost)
		
		// Calculate cost to move target position to top of stack A
		current->cost_a = current->target_pos;  // Initial cost is target position (rotations needed)
		if (current->target_pos > size_a / 2)   // If target position is in bottom half of stack
			current->cost_a = (size_a - current->target_pos) * -1;  // Use reverse rotations (negative cost)
		
		current = current->next;  // Move to next element in stack B
	}
}
/**
 * Find the element with lowest total cost and move it
 */
void	execute_cheapest_move(t_node **stack_a, t_node **stack_b)
{
	t_node	*current;           // Pointer to traverse stack B
	int	cheapest_cost;         // Track lowest total cost found
	int	cost_a;                // Cost for stack A of cheapest move
	int	cost_b;                // Cost for stack B of cheapest move

	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;              // Safety check: Make sure both stacks exist and aren't empty
	
	current = *stack_b;         // Start with top element of stack B
	cheapest_cost = 2147483647; // INT_MAX as initial value
	
	while (current)             // Loop through each element in stack B
	{
		// If total absolute cost is less than the cheapest found so far
		if (absolute_value(current->cost_a) + absolute_value(current->cost_b) < absolute_value(cheapest_cost))
		{
			cheapest_cost = absolute_value(current->cost_a) + absolute_value(current->cost_b);
			cost_a = current->cost_a;  // Save the stack A cost of this element
			cost_b = current->cost_b;  // Save the stack B cost of this element
		}
		current = current->next;  // Move to next element
	}
	
	execute_move(stack_a, stack_b, cost_a, cost_b);  // Execute the move with lowest total cost
}
#include "push_swap.h"
/**
 * Main function for push_swap
 */
int	main(int ac, char **av)
{
	t_node	*stack_a;        // Will hold input numbers
	t_node	*stack_b;        // Initially empty auxiliary stack
	int	size;                // Size of stack A

	if (ac < 2)
		return (0);         // Exit if no arguments provided
	
	if (!check_input(ac, av))
	{
		write(2, "Error\n", 6);  // Print error message if input is invalid
		return (1);           // Exit with error status
	}
	
	stack_b = NULL;           // Initialize stack B as empty
	stack_a = parse_input(ac, av);  // Parse arguments into stack A
	size = stack_size(stack_a);     // Get size of stack A
	
	// Assign index to each element (used for sorting)
	// Index represents position in sorted array (higher index = higher value)
	assign_index(stack_a, size);
	
	// If stack is not already sorted, sort it
	if (!is_sorted(stack_a))
		sort(&stack_a, &stack_b);  // Main sorting algorithm
	
	// Free memory before exiting
	free_stack(&stack_a);
	free_stack(&stack_b);
	
	return (0);  // Exit successfully
}
NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c \
	  print_operations.c \
	  stack.c \
	  cost.c \
	  position.c \
	  sort.c \
	  validation.c \
	  utils.c \
	  movements.c \
	  swap.c \
	  push.c \
	  rotate.c \
	  reverse_rotate.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
#include "push_swap.h"
/**
 * Execute simultaneous reverse rotations on both stacks
 */
static void	execute_reverse_rotate_both(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)  // While both costs are negative (need reverse rotations)
	{
		(*cost_a)++;  // Decrease absolute cost for stack A by 1 (one less rev rotation needed)
		(*cost_b)++;  // Decrease absolute cost for stack B by 1 (one less rev rotation needed)
		rrr(stack_a, stack_b);  // Do reverse rotation on both stacks simultaneously
	}
}
/**
 * Execute simultaneous rotations on both stacks
 */
static void	execute_rotate_both(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)  // While both costs are positive (need forward rotations)
	{
		(*cost_a)--;  // Decrease cost for stack A by 1 (one less rotation needed)
		(*cost_b)--;  // Decrease cost for stack B by 1 (one less rotation needed)
		rr(stack_a, stack_b);  // Do rotation on both stacks simultaneously
	}
}
/**
 * Move stack A into position using the cost
 */
void	move_stack_a(t_node **stack_a, int *cost)
{
	while (*cost)  // While there are still moves needed
	{
		if (*cost > 0)  // If cost is positive, need to rotate forward
		{
			ra(stack_a);   // Rotate stack A forward
			(*cost)--;     // Decrement cost (one less rotation needed)
		}
		else if (*cost < 0)  // If cost is negative, need to rotate backward
		{
			rra(stack_a);   // Reverse rotate stack A
			(*cost)++;      // Increment cost (getting closer to 0)
		}
	}
}
/**
 * Move stack B into position using the cost
 */
void	move_stack_b(t_node **stack_b, int *cost)
{
	while (*cost)  // While there are still moves needed
	{
		if (*cost > 0)  // If cost is positive, need to rotate forward
		{
			rb(stack_b);   // Rotate stack B forward
			(*cost)--;     // Decrement cost (one less rotation needed)
		}
		else if (*cost < 0)  // If cost is negative, need to rotate backward
		{
			rrb(stack_b);   // Reverse rotate stack B
			(*cost)++;      // Increment cost (getting closer to 0)
		}
	}
}
/**
 * Execute the move with the given cost
 */
void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b)
{
	// Optimize by doing both operations simultaneously when possible
	if (cost_a < 0 && cost_b < 0)  // If both stacks need reverse rotation
		execute_reverse_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	else if (cost_a > 0 && cost_b > 0)  // If both stacks need forward rotation
		execute_rotate_both(stack_a, stack_b, &cost_a, &cost_b);
	
	// Move the remaining operations
	move_stack_a(stack_a, &cost_a);  // Complete remaining moves for stack A
	move_stack_b(stack_b, &cost_b);  // Complete remaining moves for stack B
	
	// Push from B to A
	pa(stack_a, stack_b);  // Push the top element from B to A (now in correct position)
}
#include "push_swap.h"

/**
 * Set the position of each element in the stack
 * Position is the current location in the stack (0 is top)
 */
void	set_position(t_node **stack)
{
	t_node	*current;  // Pointer to traverse the stack
	int		i;         // Position counter

	if (!stack || !*stack)
		return ;      // Safety check: Ensure stack exists and isn't empty
	current = *stack;  // Start at the top of the stack
	i = 0;             // First position is 0 (top of stack)
	while (current)    // Loop through entire stack
	{
		current->position = i;  // Assign current position number to this node
		current = current->next;  // Move to next node
		i++;                      // Increment position counter
	}
}

/**
 * Find the position of the lowest indexed element
 */
int	get_lowest_index_position(t_node **stack)
{
	t_node	*current;     // Pointer to traverse stack
	int		lowest_index; // Track smallest index found
	int		lowest_pos;   // Position of smallest index

	if (!stack || !*stack)
		return (-1);     // Safety check: Return error if stack doesn't exist
	
	set_position(stack);   // Make sure positions are up to date
	current = *stack;      // Start at top of stack
	lowest_index = 2147483647; // INT_MAX as initial value
	lowest_pos = 0;           // Default position
	
	while (current)        // Loop through entire stack
	{
		if (current->index < lowest_index)  // If found smaller index
		{
			lowest_index = current->index;  // Update lowest index
			lowest_pos = current->position; // Update position of lowest index
		}
		current = current->next;  // Move to next node
	}
	return (lowest_pos);  // Return position of lowest index element
}

/**
 * Find the best target position in stack A for each element in stack B
 */
static int	find_target_position(t_node **stack_a, int b_index)
{
	t_node	*current;      // Pointer to traverse stack A
	int		target_index;  // Index to find target position for
	int		target_pos;    // Position of target

	current = *stack_a;    // Start at top of stack A
	target_index = 2147483647; // INT_MAX as initial value
	target_pos = 0;           // Default position
	
	// First try to find the closest greater index in stack A
	// (Finding the element that should be just above the B element after sorting)
	while (current)
	{
		if (current->index > b_index && current->index < target_index)
		{
			target_index = current->index;  // Update closest greater index
			target_pos = current->position; // Update its position
		}
		current = current->next;  // Move to next node
	}
	
	// If no greater index found, find the smallest index in stack A
	// (This means element B is the largest, so it should go before smallest)
	if (target_index == 2147483647/*INT_MAX*/)
	{
		current = *stack_a;  // Restart traversal from top
		target_index = 2147483647; // Reset target index
		
		while (current)
		{
			if (current->index < target_index)
			{
				target_index = current->index;  // Update smallest index
				target_pos = current->position; // Update its position
			}
			current = current->next;  // Move to next node
		}
	}
	
	return (target_pos);  // Return best target position found
}

/**
 * Set the target position for each element in stack B
 */
void	set_target_position(t_node **stack_a, t_node **stack_b)
{
	t_node	*current_b;  // Pointer to traverse stack B
	
	if (!stack_a || !*stack_a || !stack_b || !*stack_b)
		return ;        // Safety check: Ensure both stacks exist
	
	set_position(stack_a);  // Update positions in stack A
	set_position(stack_b);  // Update positions in stack B
	
	current_b = *stack_b;   // Start at top of stack B
	while (current_b)       // Loop through all elements in stack B
	{
		current_b->target_pos = find_target_position(stack_a, current_b->index);  // Find where this element should go in A
		current_b = current_b->next;  // Move to next node in B
	}
}
#include "push_swap.h"
/**
 * Print operation to stdout
 */
void	print_operation(char *op)
{
	int	i;  // Character counter

	i = 0;
	while (op[i])  // Count characters in operation string
		i++;
	write(1, op, i);   // Print the operation
	write(1, "\n", 1); // Print newline
}
#include "push_swap.h"
/**
 * Push the top element from src stack to dest stack
 */
void	push(t_node **src, t_node **dest)
{
	t_node	*temp;  // Temporary pointer to hold the node being moved

	if (!*src)      // If source stack is empty
		return ;    // Nothing to push, return
	temp = *src;    // Store top node of source stack
	*src = (*src)->next;  // Update source stack to point to next node
	temp->next = *dest;   // Set next of pushed node to point to top of dest stack
	*dest = temp;         // Update dest stack to point to new top node
}
/**
 * Push the top element from stack B to stack A
 */
void	pa(t_node **stack_a, t_node **stack_b)
{
	push(stack_b, stack_a);  // Push from B to A
	print_operation("pa");   // Print operation
}
/**
 * Push the top element from stack A to stack B
 */
void	pb(t_node **stack_a, t_node **stack_b)
{
	push(stack_a, stack_b);  // Push from A to B
	print_operation("pb");   // Print operation
}
#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
//# include <limits.h>

typedef struct s_node
{
	int	value;        // The actual number value
	int	index;        // Index for sorting (normalized rank: highest number gets highest index)
	int	position;     // Current position in the stack (0 = top)
	int	target_pos;   // Target position in the other stack
	int	cost_a;       // Cost of moving target position to top of stack A
	int	cost_b;       // Cost of moving element to top of stack B
	struct s_node	*next;  // Pointer to next node in stack
}	t_node;

/* Stack operations */
t_node	*new_node(int value);
void	add_node_back(t_node **stack, t_node *new);
t_node	*get_last_node(t_node *stack);
t_node	*get_second_last_node(t_node *stack);
int	stack_size(t_node *stack);
void	free_stack(t_node **stack);
int	is_sorted(t_node *stack);
void	free_and_exit(t_node **stack_a, t_node **stack_b);

/* Swap operations */
void	swap(t_node *stack);
void	sa(t_node **stack_a);
void	sb(t_node **stack_b);
void	ss(t_node **stack_a, t_node **stack_b);

/* Push operations */
void	push(t_node **src, t_node **dest);
void	pa(t_node **stack_a, t_node **stack_b);
void	pb(t_node **stack_a, t_node **stack_b);

/* Rotate operations */
void	rotate(t_node **stack);
void	ra(t_node **stack_a);
void	rb(t_node **stack_b);
void	rr(t_node **stack_a, t_node **stack_b);

/* Reverse rotate operations */
void	reverse_rotate(t_node **stack);
void	rra(t_node **stack_a);
void	rrb(t_node **stack_b);
void	rrr(t_node **stack_a, t_node **stack_b);

/* Position and cost functions */
void	set_position(t_node **stack);
int	get_lowest_index_position(t_node **stack);
void	set_target_position(t_node **stack_a, t_node **stack_b);
void	calculate_cost(t_node **stack_a, t_node **stack_b);
void	execute_cheapest_move(t_node **stack_a, t_node **stack_b);

/* Movement execution */
void	move_both_stacks(t_node **stack_a, t_node **stack_b, int *cost_a, int *cost_b);
void	move_stack_a(t_node **stack_a, int *cost);
void	move_stack_b(t_node **stack_b, int *cost);
void	execute_move(t_node **stack_a, t_node **stack_b, int cost_a, int cost_b);

/* Sorting algorithms */
void	sort_three(t_node **stack);
void	sort(t_node **stack_a, t_node **stack_b);
void	shift_stack(t_node **stack_a);

/* Parsing and validation */
int	check_input(int ac, char **av);
int	is_number(char *str);
int	has_duplicates(char **av);
int	is_zero(char *str);
t_node	*parse_input(int ac, char **av);
void	assign_index(t_node *stack_a, int size);

/* Helper functions */
void	print_operation(char *op);
int	absolute_value(int nb);
long	ft_atoi(const char *str);
int	is_digit(char c);
int	is_sign(char c);
int	str_compare(const char *s1, const char *s2);

#endif
#include "push_swap.h"
/**
 * Reverse rotate a stack - bottom element becomes the top element
 */
void	reverse_rotate(t_node **stack)
{
	t_node	*last;        // Will point to last node in stack
	t_node	*second_last; // Will point to second-to-last node

	if (!*stack || !(*stack)->next)  // If stack empty or has only one element
		return ;                     // Nothing to rotate, return
	last = get_last_node(*stack);       // Get the last node
	second_last = get_second_last_node(*stack);  // Get second-to-last node
	last->next = *stack;               // Point last node to top of stack
	*stack = last;                     // Make last node the new top
	second_last->next = NULL;          // Make second-last node the new end
}
/**
 * Reverse rotate stack A
 */
void	rra(t_node **stack_a)
{
	reverse_rotate(stack_a);  // Perform reverse rotation on stack A
	print_operation("rra");   // Print operation
}

/**
 * Reverse rotate stack B
 */
void	rrb(t_node **stack_b)
{
	reverse_rotate(stack_b);  // Perform reverse rotation on stack B
	print_operation("rrb");   // Print operation
}
/**
 * Reverse rotate both stacks
 */
void	rrr(t_node **stack_a, t_node **stack_b)
{
	reverse_rotate(stack_a);  // Reverse rotate stack A
	reverse_rotate(stack_b);  // Reverse rotate stack B
	print_operation("rrr");   // Print combined operation
}
#include "push_swap.h"
/**
 * Rotate a stack - top element becomes the bottom element
 */
void	rotate(t_node **stack)
{
	t_node	*temp;  // Temporary pointer for the top node
	t_node	*last;  // Will point to last node in stack

	if (!*stack || !(*stack)->next)  // If stack empty or has only one element
		return ;                     // Nothing to rotate, return
	temp = *stack;                   // Store the top node
	*stack = (*stack)->next;         // Make second node the new top
	last = get_last_node(*stack);    // Find the last node
	temp->next = NULL;               // Detach top node from stack
	last->next = temp;               // Attach old top to end of stack
}
/**
 * Rotate stack A
 */
void	ra(t_node **stack_a)
{
	rotate(stack_a);        // Perform rotation on stack A
	print_operation("ra");  // Print operation
}
/**
 * Rotate stack B
 */
void	rb(t_node **stack_b)
{
	rotate(stack_b);        // Perform rotation on stack B
	print_operation("rb");  // Print operation
}
/**
 * Rotate both stacks
 */
void	rr(t_node **stack_a, t_node **stack_b)
{
	rotate(stack_a);        // Rotate stack A
	rotate(stack_b);        // Rotate stack B
	print_operation("rr");  // Print combined operation
}
#include "push_swap.h"
/**
 * Sort a stack with 3 elements using the minimum number of operations
 */
void	sort_three(t_node **stack)
{
	int	highest_index;  // Will store the highest index among the 3 elements
	
	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;          // Safety check: need exactly 3 elements
	
	if (is_sorted(*stack))
		return ;          // If already sorted, do nothing
	
	// Find the highest index in the stack
	highest_index = (*stack)->index;  // Start with top element
	if ((*stack)->next->index > highest_index)
		highest_index = (*stack)->next->index;  // Check middle element
	if ((*stack)->next->next->index > highest_index)
		highest_index = (*stack)->next->next->index;  // Check bottom element
	
	// If highest is at the top, rotate it to the bottom
	if ((*stack)->index == highest_index)
		ra(stack);
	// If highest is in the middle, reverse rotate to get it to the bottom
	else if ((*stack)->next->index == highest_index)
		rra(stack);
	
	// If the first two elements are not in order, swap them
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}
/**
 * Push elements from stack A to stack B, leaving only 3 elements in A
 * Push smaller values first for better sorting efficiency
 */
static void	push_all_except_three(t_node **stack_a, t_node **stack_b)
{
	int	size;    // Total number of elements
	int	pushed;  // Number of elements pushed so far
	int	i;       // Loop counter
	
	size = stack_size(*stack_a);  // Get total elements in stack A
	if (size <= 3)               // If 3 or fewer elements
		return ;                 // Nothing to push
	
	pushed = 0;  // Initialize pushed counter
	i = 0;       // Initialize loop counter
	
	// First push all elements with index <= size/2 (the smaller half)
	// This optimization makes sorting more efficient
	while (size > 6 && i < size && pushed < size / 2)
	{
		if ((*stack_a)->index <= size / 2)  // If element is in smaller half
		{
			pb(stack_a, stack_b);  // Push to stack B
			pushed++;              // Increment pushed counter
		}
		else
			ra(stack_a);           // Rotate to check next element
		i++;                      // Increment loop counter
	}
	
	// Then push remaining elements except 3
	while (size - pushed > 3)    // Until only 3 elements remain in A
	{
		pb(stack_a, stack_b);    // Push to stack B
		pushed++;                // Increment pushed counter
	}
}
/**
 * Shift the stack so the lowest element is at the top
 */
void	shift_stack(t_node **stack_a)
{
	int	lowest_pos;  // Position of lowest indexed element
	int	size;        // Size of stack
	
	if (!stack_a || !*stack_a)
		return ;      // Safety check: ensure stack exists
	
	size = stack_size(*stack_a);           // Get stack size
	lowest_pos = get_lowest_index_position(stack_a);  // Find lowest element
	
	// If lowest is in bottom half, reverse rotate
	if (lowest_pos > size / 2)
	{
		while (lowest_pos < size)  // Until position wraps around to 0
		{
			rra(stack_a);          // Reverse rotate
			lowest_pos++;          // Update position counter
		}
	}
	// If lowest is in top half, rotate
	else
	{
		while (lowest_pos > 0)    // Until lowest reaches top position
		{
			ra(stack_a);          // Rotate forward
			lowest_pos--;         // Update position counter
		}
	}
}
/**
 * Main sorting algorithm
 */
void	sort(t_node **stack_a, t_node **stack_b)
{
	if (!stack_a || !*stack_a)
		return ;           // Safety check: ensure stack A exists
	
	// If already sorted, do nothing
	if (is_sorted(*stack_a))
		return ;
	
	// If only 2 elements, just swap if needed
	if (stack_size(*stack_a) == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			sa(stack_a);
		return ;
	}
	
	// If 3 elements, use the specialized algorithm
	if (stack_size(*stack_a) == 3)
	{
		sort_three(stack_a);
		return ;
	}
	
	// For larger stacks, use the cost-based algorithm:
	// 1. Push all except 3 elements to stack B
	push_all_except_three(stack_a, stack_b);
	
	// 2. Sort the remaining 3 elements in stack A
	sort_three(stack_a);
	
	// 3. Push elements back from B to A in correct order
	while (*stack_b)
	{
		set_target_position(stack_a, stack_b);  // Find where each B element should go in A
		calculate_cost(stack_a, stack_b);       // Calculate cost of moving each element
		execute_cheapest_move(stack_a, stack_b);  // Execute the cheapest move
	}	
	
	// 4. Finally, rotate stack A so lowest value is at the top
	if (!is_sorted(*stack_a))
		shift_stack(stack_a);
}
#include "push_swap.h"
/**
 * Create a new node with the given value
 */
t_node	*new_node(int value)
{
	t_node	*node;  // New node to be created

	node = malloc(sizeof(t_node));  // Allocate memory
	if (!node)                      // If allocation failed
		return (NULL);             // Return NULL
	node->value = value;            // Set the value
	node->index = 0;                // Initialize index
	node->position = -1;            // Initialize position as invalid
	node->target_pos = -1;          // Initialize target position as invalid
	node->cost_a = -1;              // Initialize cost_a as invalid
	node->cost_b = -1;              // Initialize cost_b as invalid
	node->next = NULL;              // No next node yet
	return (node);                  // Return the new node
}
/**
 * Add a node to the end of a stack
 */
void	add_node_back(t_node **stack, t_node *new)
{
	t_node	*last;  // Will point to last node in stack

	if (!new)       // If new node is NULL
		return ;    // Nothing to add
	if (!*stack)    // If stack is empty
	{
		*stack = new;  // New node becomes the stack
		return ;
	}
	last = get_last_node(*stack);  // Find last node
	last->next = new;              // Add new node at the end
}
/**
 * Get the last node in the stack
 */
t_node	*get_last_node(t_node *stack)
{
	if (!stack)      // If stack is empty
		return (NULL);  // Return NULL
	while (stack->next)  // While not at last node
		stack = stack->next;  // Move to next node
	return (stack);  // Return last node
}
/**
 * Get the second-to-last node in the stack
 */
t_node	*get_second_last_node(t_node *stack)
{
	if (!stack || !stack->next)             // If stack is empty or has only one node
		return (NULL);                       // Return NULL
	while (stack->next && stack->next->next) // While we're not at the second-to-last node
		stack = stack->next;                 // Move to next node
	return (stack);                          // Return second-to-last node
}

/**
 * Get the size of the stack
 */
int	stack_size(t_node *stack)
{
	int	size;                    // Counter for stack size

	size = 0;                     // Initialize counter
	while (stack)                 // While not at end of stack
	{
		size++;                   // Increment counter
		stack = stack->next;      // Move to next node
	}
	return (size);                // Return total count
}

/**
 * Free all nodes in a stack
 */
void	free_stack(t_node **stack)
{
	t_node	*tmp;                // Temporary pointer for freeing nodes

	if (!stack || !*stack)        // If stack doesn't exist or is empty
		return ;                  // Nothing to free
	while (*stack)                // While stack is not empty
	{
		tmp = (*stack)->next;     // Save pointer to next node
		free(*stack);             // Free current node
		*stack = tmp;             // Move stack pointer to next node
	}
	*stack = NULL;                // Set stack pointer to NULL (empty stack)
}

/**
 * Check if stack is sorted
 */
int	is_sorted(t_node *stack)
{
	while (stack && stack->next)  // While not at end of stack and there's a next node
	{
		if (stack->value > stack->next->value)  // If current value > next value
			return (0);                          // Not sorted
		stack = stack->next;                     // Move to next node
	}
	return (1);                   // All values are in order, stack is sorted
}

/**
 * Free both stacks and exit with error
 */
void	free_and_exit(t_node **stack_a, t_node **stack_b)
{
	free_stack(stack_a);          // Free stack A
	free_stack(stack_b);          // Free stack B
	write(2, "Error\n", 6);        // Write error message to stderr
	exit(1);                      // Exit with error status
}
/**
 * Swap the top two elements of a stack
 */
void	swap(t_node *stack)
{
	int	temp;                     // Temporary variable for swapping

	if (!stack || !stack->next)    // If stack is empty or has only one element
		return ;                   // Nothing to swap
	
	// Swap values
	temp = stack->value;           // Store first value
	stack->value = stack->next->value;  // Set first value to second value
	stack->next->value = temp;     // Set second value to first value
	
	// Swap indices
	temp = stack->index;           // Store first index
	stack->index = stack->next->index;  // Set first index to second index
	stack->next->index = temp;     // Set second index to first index
}

/**
 * Swap the top two elements of stack A
 */
void	sa(t_node **stack_a)
{
	swap(*stack_a);                // Perform swap on stack A
	print_operation("sa");         // Print the operation
}

/**
 * Swap the top two elements of stack B
 */
void	sb(t_node **stack_b)
{
	swap(*stack_b);                // Perform swap on stack B
	print_operation("sb");         // Print the operation
}

/**
 * Swap the top two elements of both stacks
 */
void	ss(t_node **stack_a, t_node **stack_b)
{
	swap(*stack_a);                // Swap top two elements of stack A
	swap(*stack_b);                // Swap top two elements of stack B
	print_operation("ss");         // Print the combined operation
}

/**
 * Return the absolute value of a number
 */
int	absolute_value(int nb)
{
	if (nb < 0)                    // If number is negative
		return (-nb);              // Return negative of the number (making it positive)
	return (nb);                   // Otherwise return the number as is
}

/**
 * Convert string to long integer
 */
long	ft_atoi(const char *str)
{
	long	result;                // Result value
	int		sign;                  // Sign of the number
	int		i;                     // Index into string

	result = 0;                    // Initialize result
	sign = 1;                      // Default sign is positive
	i = 0;                         // Start at beginning of string
	
	// Skip whitespace
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	
	// Handle sign character
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')         // If negative sign
			sign = -1;             // Change sign multiplier
		i++;                       // Move past sign character
	}
	
	// Convert digits to number
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');  // Shift left and add digit
		i++;                       // Move to next character
	}
	
	return (result * sign);        // Return result with correct sign
}

/**
 * Check if a character is a digit
 */
int	is_digit(char c)
{
	return (c >= '0' && c <= '9'); // Return true if c is between '0' and '9'
}

/**
 * Check if a character is a sign (+ or -)
 */
int	is_sign(char c)
{
	return (c == '+' || c == '-'); // Return true if c is '+' or '-'
}

/**
 * Compare two strings
 */
int	str_compare(const char *s1, const char *s2)
{
	int	i;                         // Index into strings

	i = 0;                         // Start at beginning of strings
	while (s1[i] && s2[i] && s1[i] == s2[i])  // While characters match
		i++;                       // Move to next character
	
	return (s1[i] - s2[i]);        // Return difference between first non-matching characters
}

/**
 * Check if a string represents a number
 */
int	is_number(char *str)
{
	int	i;                         // Index into string

	i = 0;                         // Start at beginning of string
	if (is_sign(str[i]) && str[i + 1] != '\0')  // If first char is sign and not end of string
		i++;                       // Skip sign character
	while (str[i] && is_digit(str[i]))  // While current char is a digit
		i++;                       // Move to next character
	if (str[i] != '\0')            // If we haven't reached end of string
		return (0);                // Not a valid number
	return (1);                    // Valid number
}

/**
 * Check if a string represents zero (0, +0, -0, 000, etc.)
 */
int	is_zero(char *str)
{
	int	i;                         // Index into string

	i = 0;                         // Start at beginning of string
	if (is_sign(str[i]))           // If first char is sign
		i++;                       // Skip sign character
	while (str[i] && str[i] == '0')  // While current char is '0'
		i++;                       // Move to next character
	if (str[i] != '\0')            // If we haven't reached end of string
		return (0);                // Not representing zero
	return (1);                    // Represents zero
}

/**
 * Check for duplicate values in arguments
 */
int	has_duplicates(char **av)
{
	int	i;                         // Index for outer loop
	int	j;                         // Index for inner loop

	i = 1;                         // Start from first argument
	while (av[i])                  // For each argument
	{
		j = 1;                     // Start from first argument
		while (av[j])              // For each argument
		{
			if (i != j && str_compare(av[i], av[j]) == 0)  // If different positions but same value
				return (1);         // Duplicate found
			j++;                   // Move to next argument
		}
		i++;                       // Move to next argument
	}
	return (0);                    // No duplicates found
}

/**
 * Validate input arguments
 */
int	check_input(int ac, char **av)
{
	int	i;                         // Index into arguments
	int	zero_count;                // Counter for zero arguments

	if (ac < 2)                    // If no arguments provided
		return (0);                // Invalid input
	i = 1;                         // Start from first argument
	zero_count = 0;                // Initialize zero counter
	while (i < ac)                 // For each argument
	{
		if (!is_number(av[i]))     // If not a valid number
			return (0);            // Invalid input
		zero_count += is_zero(av[i]);  // Count zeros
		i++;                       // Move to next argument
	}
	// If multiple zeroes are found, we have duplicates
	if (zero_count > 1)            // If more than one zero
		return (0);                // Invalid input (duplicate zeros)
	// Check for duplicate values
	if (has_duplicates(av))        // If duplicate values found
		return (0);                // Invalid input
	return (1);                    // Input is valid
}

/**
 * Parse input arguments and create the stack A
 */
t_node	*parse_input(int ac, char **av)
{
	t_node	*stack_a;              // Stack A to be created
	t_node	*new;                  // New node to add
	long	num;                   // Number from argument
	int	i;                         // Index into arguments

	stack_a = NULL;                // Initialize stack as empty
	i = 1;                         // Start from first argument
	while (i < ac)                 // For each argument
	{
		num = ft_atoi(av[i]);      // Convert string to number
		if (num > 2147483647/*INT_MAX*/ || num < -2147483648 /*INT_MIN*/)  // If out of int range
		{
			free_stack(&stack_a);  // Free allocated memory
			write(2, "Error\n", 6);  // Print error
			exit(1);               // Exit with error status
		}
		new = new_node((int)num);  // Create new node with value
		if (!new)                  // If allocation failed
		{
			free_stack(&stack_a);  // Free allocated memory
			write(2, "Error\n", 6);  // Print error
			exit(1);               // Exit with error status
		}	
		add_node_back(&stack_a, new);  // Add new node to end of stack
		i++;                       // Move to next argument
	}
	return (stack_a);              // Return created stack
}

/**
 * Assign index to each value in the stack
 * Index represents the position in the sorted array (0 is smallest)
 */
void	assign_index(t_node *stack_a, int size)
{
	t_node	*current;              // For traversing the stack
	t_node	*highest;              // Pointer to highest unindexed node
	int	value;                     // Highest value found so far
	int	i;                         // Loop counter and index value

	if (!stack_a)                  // If stack is empty
		return ;                   // Nothing to do
	i = size;                      // Start with highest index
	while (--i >= 0)               // For each index value (largest to smallest)
	{
		current = stack_a;         // Start at beginning of stack
		value = -2147483648/*INT_MIN*/;  // Start with minimum possible value
		highest = NULL;            // No highest node found yet
		while (current)            // For each node in stack
		{
			if (current->value > value && current->index == 0)  // If unindexed and higher than current highest
			{
				value = current->value;  // Update highest value
				highest = current;       // Update pointer to highest node
			}
			current = current->next;  // Move to next node
		}
		
		if (highest)               // If a highest node was found
			highest->index = i;    // Assign it the current index
	}
}
