#include "push_swap.h"

void	small_2(t_list	**stack_A)
{
	if (seek_pos(*stack_A, 1, 1))
		sa
	return ;
}

void	small_3(t_list	**stack_A, int start)
{
	if (seek_pos(*stack_A, start + 2, 1))
	{
		rra
		write(1, "rra\n", 4);
	}
	else if (seek_pos((*stack_A)->next, start + 2, 1))
	{
		ra
		write(1, "ra\n", 3);
	}
	if (seek_pos(*stack_A, start + 1, 1))
	{
		sa
		write(1, "sa\n", 3);
	}	
	return ;
}

void	small_4(t_list	**stack_A)
{
	t_list	**stack_B;
	t_list	*elem;

	elem = NULL;
	stack_B = &elem;
	partition(stack_B, stack_A, 0, 1);
	small_3(stack_A, 1);
	pa
	write(1, "pa\n", 3);
	return ;
}

void	small_5(t_list	**stack_A)
{
	t_list	**stack_B;
	int		res;

	stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
	res = 1;
	partition(stack_B, stack_A, 0, 2);
	if (seek_pos(*stack_B, 0, 1))
	{
		if (seek_pos(*stack_A, 2, 1))
			rr
		else if (seek_pos((*stack_A)->next, 2, 1))
			rrr
		else
			res = 0;
		if (!res && seek_pos(*stack_A, 1, 1))
			ss
		else if (!res)
			sb
	}
	else
		small_3(stack_A, 2);
	pa
	pa
	free(stack_B);
	return ;
}


