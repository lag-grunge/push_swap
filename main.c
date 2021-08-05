#include "push_swap.h"

int main(int argc, char *argv[])
{
	t_list 	**stack_A;
	t_list 	**stack_B;
	t_stck_data *data;

	data = (t_stck_data *)malloc(sizeof(t_stck_data) * 1);
	if (!data)
		exit_error(3, NULL, NULL, NULL);
	check_input(argc, argv, data);
	data->arr_sorted = NULL;
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	if (!stack_A)
		exit_error(3, NULL, NULL, data);
	init_stack(argc, argv, stack_A, data);
	data->arr_sorted = insertion_sort(*stack_A, data->size);
	check_if_stack_sorted(stack_A, 0, data); 
	if (data->size > 1 && data->size < 6)
		small_size(stack_A, data->size);
	else
	{
		stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
		init_stack(0, NULL, stack_B, data);
		big_sort(stack_A, stack_B, data);
		free_stack(*stack_B);
	}
	exit_error(0, (void *)*stack_A, &free_stack, data);
}
