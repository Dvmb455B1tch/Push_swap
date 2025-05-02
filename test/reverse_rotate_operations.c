/*
** rra - Reverse rotates stack A: the last element becomes the first.
*/
void	rra(t_node **stack_a)
{
	t_node	*prev;              // Second-to-last node
	t_node	*last;              // Last node to move to the front

	if (!stack_a || !*stack_a || !(*stack_a)->next) // Not enough elements to reverse
		return ;

	prev = NULL;
	last = *stack_a;
	while (last->next)         // Find the last node
	{
		prev = last;           // Save previous
		last = last->next;     // Move forward
	}

	prev->next = NULL;         // Cut the link from prev to last
	last->next = *stack_a;     // Last now points to old head
	*stack_a = last;           // Head is updated to the last node
}

/*
** rrb - Reverse rotates stack B: the last element becomes the first.
*/
void	rrb(t_node **stack_b)
{
	t_node	*prev;              // Previous to last node
	t_node	*last;              // Last node

	if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;

	prev = NULL;
	last = *stack_b;
	while (last->next)         // Walk to last node
	{
		prev = last;
		last = last->next;
	}

	prev->next = NULL;         // Cut the last node off
	last->next = *stack_b;     // Make last point to head
	*stack_b = last;           // New head becomes the last
}

/*
** rrr - Performs rra and rrb simultaneously.
*/
void	rrr(t_node **stack_a, t_node **stack_b)
{
	rra(stack_a); // Reverse rotate A
	rrb(stack_b); // Reverse rotate B
}

