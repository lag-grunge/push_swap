#include "push_swap.h"

void	small_2(t_dlist	**stack_A)
{
	if (seek_pos(*stack_A, 1, 1))
		execute_command("sa", stack_A, NULL);
	return ;
}

void	small_3(t_dlist	**stack_A, int start)
{
	if (seek_pos(*stack_A, start + 2, 1))
		execute_command("ra", stack_A, NULL);
	else if (seek_pos((*stack_A)->next, start + 2, 1))
		execute_command("rra", stack_A, NULL);
	if (seek_pos(*stack_A, start + 1, 1))
		execute_command("sa", stack_A, NULL);
	return ;
}

void	small_4(t_dlist	**stack_A)
{
	t_dlist	*stack_B;

    stack_B = NULL;
	partition(&stack_B, stack_A, 0, 1);
	small_3(stack_A, 1);
	execute_command("pa", stack_A, &stack_B);
}

void	small_5(t_dlist	**stack_A)
{
	int		res;
    t_dlist	*stack_B;

    stack_B = NULL;
	res = 0;
	partition(&stack_B, stack_A, 0, 2);
	if (get_pos(stack_B) == 0)
	{
		if (get_pos(*stack_A) == 4)
			res = execute_command("rr", stack_A, &stack_B);
		else if (get_pos((*stack_A)->next) == 4)
			res = execute_command("rrr", stack_A, &stack_B);
		if (!res && get_pos(*stack_A) == 3)
			execute_command("ss", stack_A, &stack_B);
        else if (get_pos(*stack_A) == 3)
            execute_command("sa", stack_A, &stack_B);
        else if (!res)
            execute_command("sb", stack_A, &stack_B);
	}
	else
		small_3(stack_A, 2);
	execute_command("pa", stack_A, &stack_B);
	execute_command("pa", stack_A, &stack_B);
}

void	small_size(t_dlist **stack_A, size_t size)
{
	if (size == 2)
		small_2(stack_A);
	else if (size == 3) 
		small_3(stack_A, 0);
	else if (size == 4) 
		small_4(stack_A);
	else if (size == 5) 
		small_5(stack_A);
}