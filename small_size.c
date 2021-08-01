#include "push_swap.h"

void	small_2(t_list	**stack_A)
{
	if (seek_pos(*stack_A, 1, 1))
		execute_command("sa", stack_A, NULL);
	return ;
}

void	small_3(t_list	**stack_A, int start)
{
	if (seek_pos(*stack_A, start + 2, 1))
		execute_command("ra", stack_A, NULL);
	else if (seek_pos((*stack_A)->next, start + 2, 1))
		execute_command("rra", stack_A, NULL);
	if (seek_pos(*stack_A, start + 1, 1))
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
	execute_command("pa", stack_A, stack_B);
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
			execute_command("rr", stack_A, stack_B);
		else if (seek_pos((*stack_A)->next, 2, 1))
			execute_command("rrr", stack_A, stack_B);
		else
			res = 0;
		if (!res && seek_pos(*stack_A, 1, 1))
			execute_command("ss", stack_A, stack_B);
		else if (!res)
			execute_command("sb", stack_A, stack_B);
	}
	else
		small_3(stack_A, 2);
	execute_command("pa", stack_A, stack_B);
	execute_command("pa", stack_A, stack_B);
	free(stack_B);
	return ;
}
