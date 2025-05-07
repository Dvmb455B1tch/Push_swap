#include "push_swap.h"

/*
	Sort two elements if out of order
*/
void	sort_2(t_stack **a)
{
	if (!a || !*a || !(*a)->next)
		return;
	if ((*a)->value > (*a)->next->value)
		sa(a);
}
/*
	Sort exactly 3 elements with minimal operations
*/
void	sort_3(t_stack **a)
{
	int	first = (*a)->value;
	int	second = (*a)->next->value;
	int	third = (*a)->next->next->value;

	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

/*
	Push smallest to B, sort 3 in A, push back
*/
void	sort_4(t_stack **a, t_stack **b)
{
	int	min;

	update_positions(*a);
	min = (*a)->value;
	t_stack *tmp = *a;
	while (tmp)
	{
		if (tmp->value < min)
			min = tmp->value;
		tmp = tmp->next;
	}
	while ((*a)->value != min)
		ra(a);
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

/*
	Push two smallest to B, sort 3 in A, return them
*/
void	sort_5(t_stack **a, t_stack **b)
{
	int	min;
	int	i = 0;

	while (i < 2)
	{
		update_positions(*a);
		min = (*a)->value;
		t_stack *tmp = *a;
		while (tmp)
		{
			if (tmp->value < min)
				min = tmp->value;
			tmp = tmp->next;
		}
		while ((*a)->value != min)
			ra(a);
		pb(a, b);
		i++;
	}
	sort_3(a);
	if ((*b)->value < (*b)->next->value)
		sb(b);
	pa(a, b);
	pa(a, b);
}

