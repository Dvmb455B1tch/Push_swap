#include "push_swap.h"

/*
	Assign an index to each node representing its rank (sorted order)
*/
void	index_stack(t_stack *a)
{
	t_stack	*cur;
	t_stack	*tmp;
	int		idx;

	if (!a)
		return ;
	idx = 0;
	while (1)
	{
		cur = NULL;
		tmp = a;
		while (tmp)
		{
			if (tmp->index == -1 && (!cur || tmp->value < cur->value))
				cur = tmp;
			tmp = tmp->next;
		}
		if (!cur)
			break ;
		cur->index = idx++;
	}
}

/*
	Handle sorting of 2 or 3 elements
*/
void	sort_three(t_stack **a)
{
	int	first;
	int	second;
	int	last;

	if (stack_size(*a) == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
		return ;
	}
	first = (*a)->value;
	second = (*a)->next->value;
	last = (*a)->next->next->value;

	if (first > second && second < last && first < last)
		sa(a);
	else if (first > second && second > last)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < last && first > last)
		ra(a);
	else if (first < second && second > last && first < last)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > last && first > last)
		rra(a);
}
#include "push_swap.h"

void	turk_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	pushed;
	int	i;

	size = stack_size(*a);
	if (is_sorted(*a) || size <= 1)
		return ;
	if (size == 2)
		sa(a);
	else if (size == 3)
		sort_three(a);
	else
	{
		index_stack(*a);
		pushed = 0;
		i = 0;
		while (size > 6 && i < size && pushed < size / 2)
		{
			if ((*a)->index <= size / 2)
			{
				pb(a, b);
				pushed++;
			}
			else
				ra(a);
			i++;
		}
		while (stack_size(*a) > 3)
			pb(a, b);
		sort_three(a);
		// Then call your push back logic (greedy insertions)
		// e.g., calculate target positions and cheapest moves
		// (this part must already be written or needs writing)
	}
}


