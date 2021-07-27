#include "push_swap.h"

void	small_2(t_list	**stack_A)
{
	if (seek_pos(*stack_A, 1, 1))
		sa
	return ;
}

void	small_3(t_list	**stack_A)
{
	if (seek_pos(*stack_A, 2, 1))
		rra
	else if (seek_pos((*stack_A)->next, 2, 1))
		ra
	if (seek_pos(*stack_A, 1, 1))
		sa
	return ;
}

void	small_4(t_list	**stack_A)
{
	t_list	**stack_B;
	t_list	*elem;

	elem = NULL;
	stack_B = &elem;
	partition(stack_B, stack_A, 0, 1);
	small_3(stack_A);
	pa
	return ;
}

void	small_5(t_list	**stack_A)
{
	t_list	**stack_B;
	int		res;
	t_list	*elem;

	elem = NULL;
	stack_B = &elem;
	res = 0;
	partition(stack_B, stack_A, 0, 2);
	if (seek_pos(*stack_B, 0, 1))
	{
		if (seek_pos(*stack_A, 2, 1))
			res = 1;
		else if (seek_pos((*stack_A)->next, 2, 1))
			res = 2;
		if (res == 2)
			rrr
		else if (res == 1)
			rr
		if (!res && seek_pos(*stack_A, 1, 1))
			ss
		else if (!res)
			sb
	}
	else
		small_3(stack_A);
	push(stack_A, stack_B);
	push(stack_A, stack_B);
	return ;
}


