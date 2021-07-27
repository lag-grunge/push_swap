#include "push_swap.h"

void	print_stack(t_list *stack)
{
	while (stack)
	{
		printf("%d\n", ((t_ps_data *)(stack->content))->val);
		stack = stack->next;
	}
}

void	print_arr(int *arr, size_t size)
{
	size_t	i;

	i = 0;
	write(1, "arr\n", 4);
	while (i < size)
	{
		printf("%zu %d\n", i, arr[i]);
		i++;
	}
}
