#include "push_swap.h"

/* Finds the position of an element in stack with specific index */
static int	find_position(t_stack *stack, int index)
{
	int	position;  /* Position counter */
	
	position = 0;  /* Start at position 0 */
	while (stack)  /* Traverse the entire stack */
	{
		if (stack->index == index)  /* If current node has the target index */
			return (position);  /* Return its position */
		position++;  /* Increment position counter */
		stack = stack->next;  /* Move to next node */
	}
	return (-1);  /* Index not found, return -1 */
}

/* Calculates the most efficient rotation direction and count */
static void	get_rotation_info(t_stack *stack, int index, int *rotation_dir, int *rotation_count)
{
	int	position;  /* Position of the target element */
	int	size;      /* Size of the stack */
	
	position = find_position(stack, index);  /* Find position of target index */
	size = stack_size(stack);  /* Get total number of elements */
	
	if (position <= size / 2)  /* If position is in first half of stack */
	{
		*rotation_dir = 1;  /* Rotate forward (ra/rb) */
		*rotation_count = position;  /* Number of rotations needed */
	}
	else  /* If position is in second half of stack */
	{
		*rotation_dir = -1;  /* Rotate backward (rra/rrb) */
		*rotation_count = size - position;  /* Number of rotations needed */
	}
}

/* Rotates stack B to prepare for pushing element back to A */
static void __attribute__((unused)) rotate_to_position(t_stack **stack, int index, char stack_name)
{
	int	rotation_dir;    /* Direction of rotation (1 for ra/rb, -1 for rra/rrb) */
	int	rotation_count;  /* Number of rotations needed */
	int	i;              /* Counter for rotation operations */
	
	get_rotation_info(*stack, index, &rotation_dir, &rotation_count);  /* Get rotation info */
	
	i = 0;  /* Initialize rotation counter */
	while (i < rotation_count)  /* Perform required number of rotations */
	{
		if (stack_name == 'a')  /* If operating on stack A */
		{
			if (rotation_dir == 1)  /* If rotating forward */
				ra(stack, 1);  /* Rotate stack A */
			else  /* If rotating backward */
				rra(stack, 1);  /* Reverse rotate stack A */
		}
		else if (stack_name == 'b')  /* If operating on stack B */
		{
			if (rotation_dir == 1)  /* If rotating forward */
				rb(stack, 1);  /* Rotate stack B */
			else  /* If rotating backward */
				rrb(stack, 1);  /* Reverse rotate stack B */
		}
		i++;  /* Increment rotation counter */
	}
}

/* Performs radix sort using the least significant bit (LSB) method */
static void	radix_sort(t_stack **stack_a, t_stack **stack_b)
{
	int	size;          /* Total number of elements */
	int	max_bits;      /* Maximum number of bits needed */
	int	i;            /* Bit position counter */
	int	j;            /* Element counter */
	int	current_bit;  /* Current bit being processed */
	
	size = stack_size(*stack_a);  /* Get total number of elements */
	max_bits = 0;  /* Initialize bit count */
	while ((size - 1) >> max_bits)  /* Calculate bits needed to represent largest index */
		max_bits++;  /* Increment bit count */
	
	i = 0;  /* Start with least significant bit */
	while (i < max_bits)  /* Process all bits */
	{
		j = 0;  /* Reset element counter */
		while (j < size)  /* Process all elements */
		{
			current_bit = ((*stack_a)->index >> i) & 1;  /* Extract current bit */
			
			if (current_bit == 0)  /* If bit is 0 */
				pb(stack_a, stack_b, 1);  /* Push to stack B */
			else  /* If bit is 1 */
				ra(stack_a, 1);  /* Keep in stack A, rotate */
			
			j++;  /* Move to next element */
		}
		
		while (stack_size(*stack_b) > 0)  /* Push all elements back to stack A */
			pa(stack_a, stack_b, 1);
		
		i++;  /* Move to next bit position */
	}
}

/* Main function to sort large stacks */
void	sort_large(t_stack **stack_a, t_stack **stack_b)
{
	int	size;  /* Size of stack A */
	
	size = stack_size(*stack_a);  /* Get number of elements in stack A */
	
	if (size <= 100)  /* For smaller sets (<=100 elements) */
		radix_sort(stack_a, stack_b);  /* Use radix sort with binary representation */
	else  /* For larger sets (>100 elements) */
		radix_sort(stack_a, stack_b);  /* Also use radix sort, but could be optimized further */
}
