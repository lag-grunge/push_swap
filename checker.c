#include "push_swap.h"

static void	init_data_stuff(t_stck_data *data)
{
	data->arr_sorted = NULL;
	data->cmd_array = NULL;
	data->op_lines = NULL;
	data->i_A = data->size;
	data->i_B = 0;
}

static int	oper_lines(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	static char	*op_line;
	int			ret;

	ret = get_next_line(&op_line);
	if (ret == -1)
	{
		free_stack(*stack_B);
		exit_error(GNL_READ_MALLOC_ERROR, *stack_A, free_stack, data);
	}
	else if (ret == 0)
		return (ret);
	else if (!execute_command(op_line, stack_A, stack_B, 1))
	{
		free_stack(*stack_B);
		exit_error(NON_CORRECT_COMMAND, *stack_A, free_stack, data);
	}
	free(op_line);
	op_line = 0;
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_dlist		*stack_A;
	t_dlist		*stack_B;
	t_stck_data	data;
	int			ret;

	check_input(argc, argv, &data);
	init_data_stuff(&data);
	init_stack(argc, argv, &stack_A, &data);
	data.arr_sorted = insertion_sort(stack_A, data.size);
	init_stack(0, NULL, &stack_B, &data);
	ret = oper_lines(&stack_A, &stack_B, &data);
	while (1 == ret)
		ret = oper_lines(&stack_A, &stack_B, &data);
	free_stack(stack_B);
	check_if_stack_sorted(&stack_A, IS_CHECKER, &data);
	exit_error(OK_STACK_SORTED, stack_A, &free_stack, &data);
}
