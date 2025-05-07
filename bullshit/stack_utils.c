
#include "push_swap.h"

/* Create a new node with the given value */
t_node	*ft_stack_new(int value)
{
	t_node	*new_node;  /* Pointer to the new node */

	new_node = (t_node *)malloc(sizeof(t_node));  /* Allocate memory */
	if (!new_node)  /* Check if allocation failed */
		return (NULL);
	new_node->value = value;  /* Set the value */
	new_node->index = 0;  /* Initialize index */
	new_node->pos = -1;  /* Initialize position */
	new_node->target_pos = -1;  /* Initialize target position */
	new_node->cost_a = 0;  /* Initialize cost_a */
	new_node->cost_b = 0;  /* Initialize cost_b */
	new_node->next = NULL;  /* Initialize next pointer */
	return (new_node);  /* Return the new node */
}

/* Add a node to the end of the stack */
void	ft_stack_add_back(t_node **stack, t_node *new_node)
{
	t_node	*last;  /* Pointer to the last node */

	if (!new_node)  /* Check if new node exists */
		return ;
	if (!*stack)  /* If stack is empty */
	{
		*stack = new_node;  /* Make new node the first element */
		return ;
	}
	last = ft_stack_last(*stack);  /* Find the last node */
	last->next = new_node;  /* Link last node to new node */
}

/* Get the last node of the stack */
t_node	*ft_stack_last(t_node *stack)
{
	if (!stack)  /* Check if stack exists */
		return (NULL);
	while (stack->next)  /* Traverse to the last node */
		stack = stack->next;
	return (stack);  /* Return the last node */
}

/* Get the size of the stack */
int	ft_stack_size(t_node *stack)
{
	int	size;  /* Counter for the stack size */

	size = 0;  /* Initialize size to 0 */
	while (stack)  /* Traverse the stack */
	{
		size++;  /* Increment size */
		stack = stack->next;  /* Move to next node */
	}
	return (size);  /* Return the size */
}

/* Free the stack */
void	ft_stack_clear(t_node **stack)
{
	t_node	*current;  /* Current node being processed */
	t_node	*next;  /* Next node to process */

	if (!stack || !*stack)  /* Check if stack exists */
		return ;
	current = *stack;  /* Start with the first node */
	while (current)  /* Traverse the stack */
	{
		next = current->next;  /* Save next node */
		free(current);  /* Free current node */
		current = next;  /* Move to next node */
	}
	*stack = NULL;  /* Set stack pointer to NULL */
}


