#include "push_swap.h"

int main(int argc, char *argv[])
{
	t_list	**stack_A;
	t_list	**stack_B;
	char	*op_line;
	t_stck_data *data;

	data = (t_stck_data *)malloc(sizeof(t_stck_data) * 1);
	check_input(argc, argv, data);
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(argc, argv, stack_A, data);
	data->arr_sorted = insertion_sort(*stack_A, data->size);
	op_line = 0;
	stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(0, NULL, stack_B, data);
	while (get_next_line(&op_line))
	{
		if  (!execute_command(op_line, stack_A, stack_B)) 
		{
			free(op_line);
			exit_error(4, (void *)stack_A, free_stack, data);
		}
		free(op_line);
		op_line = 0;
	}
	free(*stack_B);
	check_if_stack_sorted(stack_A, 1, data);
}
