#include "push_swap.h"

void	print_stack(t_list *stack)
{

	while (stack)
	{
		printf("%zu %d %zu\n", ((t_ps_data *)(stack->content))->pos, ((t_ps_data *)(stack->content))->val, ((t_asip_data *)(stack->content))->flag);
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

void	debug_print_stack(t_list **stack_A, t_list **stack_B)
{
	sleep(10);
	printf("stack_A\n");
	print_stack(*stack_A);
	if (stack_B)
	{
		printf("stack_B\n");
		print_stack(*stack_B);
	}
}
