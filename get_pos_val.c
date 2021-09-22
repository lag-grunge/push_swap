#include "push_swap.h"

size_t	get_pos(t_dlist *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->pos);
}

size_t  get_flag(t_dlist *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->flag);
}

size_t	*set_flag(t_dlist *stack_elem)
{
	return &(((t_ps_data *)(stack_elem->content))->flag);
}

int 	seek_pos(t_dlist *stack, size_t part, size_t size)
{
	size_t	pos;

	pos = ((t_ps_data *)(stack->content))->pos;
	if (pos >= part && pos < part + size)
		return (1);
	return (0);
}

void	partition(t_dlist **stack_B, t_dlist **stack_A, size_t part, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (seek_pos(*stack_A, part, size))
		{
			execute_command("pb", stack_A, stack_B);
			i++;
		}
		else
			execute_command("ra", stack_A, stack_B);
	}
}
