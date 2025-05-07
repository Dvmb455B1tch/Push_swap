#include "push_swap.h"

/*
	Swap the values (not nodes) of two stack elements
*/
static void	swap_nodes(t_stack *a, t_stack *b)
{
	int	temp_value;
	int	temp_index;

	temp_value = a->value;
	a->value = b->value;
	b->value = temp_value;

	temp_index = a->index;
	a->index = b->index;
	b->index = temp_index;
}

/*
	Swap top two elements of stack a
*/
void	sa(t_stack **a)
{
	if (!a || !*a || !(*a)->next)
		return ;
	swap_nodes(*a, (*a)->next);
	write(1, "sa\n", 3);
}

/*
	Swap top two elements of stack b
*/
void	sb(t_stack **b)
{
	if (!b || !*b || !(*b)->next)
		return ;
	swap_nodes(*b, (*b)->next);
	write(1, "sb\n", 3);
}

/*
	Swap top two of both a and b
*/
void	ss(t_stack **a, t_stack **b)
{
	sa(a);
	sb(b);
}

