#include "push_swap.h"

void	sort(t_dlist **stack_A, t_stck_data *data)
{
	t_dlist	*stack_B;

	if (data->size >= 2 && data->size <= 5)
	{
		small_size(stack_A, data->size);
		return ;
	}
	init_stack(0, NULL, &stack_B, data);
	if (6 <= data->size && data->size <= ALGO_BORDER)
		asipes_sort(stack_A, &stack_B, data);
	else if (ALGO_BORDER < data->size)
		merge_sort(stack_A, &stack_B, data);
	free_stack(stack_B);
}
