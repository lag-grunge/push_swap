#include "push_swap.h"

int	seek_pos(t_list *stack, size_t part, size_t size)
{
	size_t	pos;

	pos = ((t_ps_data *)(stack->content))->pos;
	if (pos >= part && pos < part + size)
		return (1);
	return (0);
}

size_t	get_pos(t_list *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->pos);
}

int		get_val(t_list *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->val);
}

void	partition(t_list **stack_B, t_list **stack_A, size_t part, size_t size)
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
