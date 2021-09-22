#include "push_swap.h"

void big_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	//radix_sort(stack_A, stack_B, data->size);
	merge_sort(stack_A, stack_B, data);
}
