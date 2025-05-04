#include "push_swap.h"

/* Creates a new node with the given value */
t_stack	*create_node(int value)
{
	t_stack	*new;  /* Pointer to the new node to be created */
	
	new = (t_stack *)malloc(sizeof(t_stack));  /* Allocate memory for node */
	if (!new)                                  /* Check if allocation failed */
		return (NULL);                         /* Return NULL if failed */
	
	new->value = value;  /* Set the value of the node */
	new->index = 0;      /* Initialize index as 0 */
	new->next = NULL;    /* Initialize next pointer as NULL */
	
	return (new);        /* Return the newly created node */
}

/* Adds a node to the front of the stack */
void	push_front(t_stack **stack, t_stack *new)
{
	if (!new)            /* Check if the new node is NULL */
		return ;         /* If NULL, do nothing */
	
	if (!*stack)         /* Check if the stack is empty */
	{
		*stack = new;    /* If empty, set the new node as the stack */
		return ;         /* Return from function */
	}
	
	new->next = *stack;  /* Link new node to the current top */
	*stack = new;        /* Update the stack pointer to the new node */
}

/* Removes and returns the first node from the stack */
t_stack	*pop_front(t_stack **stack)
{
	t_stack	*temp;  /* Temporary pointer to hold the node to be removed */
	
	if (!*stack)     /* Check if the stack is empty */
		return (NULL);  /* Return NULL if empty */
	
	temp = *stack;   /* Store the top node in temp */
	*stack = (*stack)->next;  /* Update stack to point to the next node */
	temp->next = NULL;  /* Disconnect the removed node from the stack */
	
	return (temp);   /* Return the removed node */
}

/* Frees all nodes in the stack */
void	free_stack(t_stack **stack)
{
	t_stack	*temp;  /* Temporary pointer for traversal */
	
	while (*stack)  /* Loop until the stack is empty */
	{
		temp = *stack;  /* Store current node */
		*stack = (*stack)->next;  /* Move to next node */
		free(temp);     /* Free current node */
	}
	*stack = NULL;  /* Set stack pointer to NULL */
}

/* Returns the number of nodes in the stack */
int	stack_size(t_stack *stack)
{
	int	size;  /* Counter for stack size */
	
	size = 0;  /* Initialize size to 0 */
	while (stack)  /* Traverse through the stack */
	{
		size++;    /* Increment counter for each node */
		stack = stack->next;  /* Move to next node */
	}
	return (size);  /* Return the total count */
}
