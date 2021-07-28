#include "checker.h"

int execute_command(char *op_line, t_list *stack_A, t_list *stack_B)
{
	if (!ft_strcmp("ra", op_line))
		ra
	else if (!ft_strcmp("rra", op_line))
		rra
	else if (!ft_strcmp("pa", op_line))
		pa
	else if (!ft_strcmp("sa", op_line))
		sa
	else if (!ft_strcmp("rb", op_line))
		rb
	else if (!ft_strcmp("rrb", op_line))
		rrb
	else if (!ft_strcmp("pb", op_line))
		pb
	else if (!ft_strcmp("sb", op_line))
		sb
	else if (!ft_strcmp("rr", op_line))
		rr
	else if (!ft_strcmp("rrr", op_line))
		rrr
	else if (!ft_strcmp("ss", op_line))
		ss
	else
		return (0);
	return (1);
}

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
	stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
	while (ret)
	{
		if  (!execute_command(op_line, stack_A, stack_B)) ////
		{
			free(op_line);
			exit_error(4, (void *)stack_A, free_stack, arr_sorted);
		}
		ret = get_next_line(op_line);
		free(op_line);
		op_line = 0;
	}
	check_if_stack_sorted(stack_A, size, 1);
}
