#include "checker.h"

int execute_command(char *op_line, t_list **stack_A, t_list **stack_B)
{
	if (!ft_strncmp("ra", op_line, 3))
		ra
	else if (!ft_strncmp("rra", op_line, 3))
		rra
	else if (!ft_strncmp("pa", op_line, 3))
		pa
	else if (!ft_strncmp("sa", op_line, 3))
		sa
	else if (!ft_strncmp("rb", op_line, 3))
		rb
	else if (!ft_strncmp("rrb", op_line, 3))
		rrb
	else if (!ft_strncmp("pb", op_line, 3))
		pb
	else if (!ft_strncmp("sb", op_line, 3))
		sb
	else if (!ft_strncmp("rr", op_line, 3))
		rr
	else if (!ft_strncmp("rrr", op_line, 3))
		rrr
	else if (!ft_strncmp("ss", op_line, 3))
		ss
	else
		return (0);
	return (1);
}
#include <stdio.h>
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
		if  (!execute_command(op_line, stack_A, stack_B)) 
		{
			free(op_line);
			exit_error(4, (void *)stack_A, free_stack, arr_sorted);
		}
		free(op_line);
		op_line = 0;
		ret = get_next_line(&op_line);
	}
	check_if_stack_sorted(stack_A, size, 1, arr_sorted);
}
