
#include "push_swap.h"

void	small_2(t_list	**stack)
{
	if ((t_ps_data *)(*stack->content)->pos == 1)
		swap(stack);
	return ;
}

void	small_3(t_list	**stack)
{
	if ((t_ps_data *)(*stack->content)->pos == 2)
		reverse_rotate(stack);
	else if ((t_ps_data *)(*stack->next->content)->pos == 2)
		rotate(stack);
	if ((t_ps_data *)(*stack->content)->pos == 1)
		swap(stack);
	return ;
}

void	small_4(t_list	**stack)
{
	t_list	*stack2;

	stack2 = NULL;
	partition(&stack2, stack1, 0, 1);
	small_3(stack);
	push(stack, &stack2);
	return ;
}



void	small_5(t_list	**stack)
{
	t_list	*stack2;
	int	res;

	stack2 = NULL;
	res = 0;
	partition(&stack2, stack1, 0, 2);
	if ((t_ps_data *)(*stack2->content)->pos == 0)
	{
		if ((t_ps_data *)(*stack->content)->pos == 2)
			res = 1;
		else if ((t_ps_data *)(*stack->next->content)->pos == 2)
			res = 2;
		if (res == 2)
			reverse_rotate_both(stack, stack2);
		else if (res == 1)
			rotate_both(stack, stack2);
		if ((t_ps_data *)(*stack->content)->pos == 1 && !res)
			swap_both(stack, stack2);
		else if ((t_ps_data *)(*stack->content)->pos == 0 && !res)
			swap(stack2);
	}
	else
		small_3(stack);
	push(stack, &stack2);
	push(stack, &stack2);
	return ;
}


