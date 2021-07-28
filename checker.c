#include "checker.h"

int main(int argc, char *argv[])
{
	size_t size;
	t_list **stack_A;
	t_list **stack_B;
	int *arr_sorted;
	char *op_line;
	int	ret;

	size = check_input(argc, argv);
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(argc, argv, stack_A);
	arr_sorted = insertion_sort(*stack_A, size);
	
	op_line = 0;
	ret = get_next_line(&op_line);
	while (ret)
	{
		if  (!(check_correct_command(op_line)))/////
		{

			exit_error(4, (void *)stack_A, free_stack, arr_sorted);
		}
		execute_command(op_line, stack_A, sta)////
		ret = get_next_line(op_line);
	}
	check_if_stack_sorted(stack_A, size, 1);
}
