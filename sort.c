#include "push_swap.h"

void big_sort(t_list **stack_A, t_list **stack_B, t_stck_data *data)
{
	//radix_sort(stack_A, stack_B, data->size);
	asipes_sort(stack_A, stack_B, data);
}
