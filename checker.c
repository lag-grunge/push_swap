#include "push_swap.h"

static void init_data_stuff(t_stck_data *data)
{
    data->arr_sorted = NULL;
    data->cmd_array = NULL;
    data->op_lines = NULL;
    data->i_A = data->size;
    data->i_B = 0;
}

int main(int argc, char *argv[])
{
	t_dlist	*stack_A;
	t_dlist	*stack_B;
	char	*op_line;
	t_stck_data data;

    check_input(argc, argv, &data);
    init_data_stuff(&data);
    init_stack(argc, argv, &stack_A, &data);
	data.arr_sorted = insertion_sort(stack_A, data.size);
	op_line = 0;
	stack_B = (t_dlist *)malloc(sizeof(t_dlist) * 1);
	init_stack(0, NULL, &stack_B, &data);
	while (get_next_line(&op_line))
	{
		if  (!execute_command(op_line, &stack_A, &stack_B))
		{
			free(op_line);
            free_stack(stack_B);
			exit_error(COMMAND_NOT_EXECUTES, (void *)stack_A, free_stack, &data);
		}
		free(op_line);
		op_line = 0;
	}
	free_stack(stack_B);
	check_if_stack_sorted(&stack_A, IS_CHECKER, &data);
}
