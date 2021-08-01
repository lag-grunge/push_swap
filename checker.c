#include "checker.h"

int main(int argc, char *argv[])
{
	size_t	size;
	t_list	**stack_A;
	t_list	**stack_B;
	char	*op_line;
	int	*arr_sorted;

	size = check_input(argc, argv);
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(argc, argv, stack_A);
	arr_sorted = insertion_sort(*stack_A, size);
	op_line = 0;
	stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(0, NULL, stack_B);
	while (get_next_line(&op_line))
	{
		if  (!execute_command(op_line, stack_A, stack_B)) 
		{
			free(op_line);
			exit_error(4, (void *)stack_A, free_stack, arr_sorted);
		}
		free(op_line);
		op_line = 0;
	}
	check_if_stack_sorted(stack_A, size, 1, arr_sorted);
}
