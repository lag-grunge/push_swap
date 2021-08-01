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
	printf("%s\n", op_line);
	printf("stack_A\n");
	print_stack(*stack_A);
	printf("stack_B\n");
	print_stack(*stack_B);
	return (1);
}

void 	half(t_list **stack_A, t_list **stack_B, size_t 	size)
{
	size_t	i;

	i = 0;
	while (i < size / 2)
	{
		execute_command("pb", stack_A, stack_B);
		i++;
	}
}

void	operate_chunk(t_list **stack_A, t_list **stack_B, size_t size, size_t chunk)
{
	size_t  i;
	int		retA;
	int		retB;
	
	i = 0;
	if (chunk == 1)
	{
		while (i < size / 2 - 1)
		{	
			retA = 0;
			retB = 0;
			if (get_pos(*stack_A, 0) > get_pos(*stack_B, 1))
				retA = 1;
			if (get_pos(*stack_B, 0) > get_pos(*stack_B, 1))
				retB = 1;
			if (retA && retB)
				execute_command("ss", stack_A, stack_B);
			else if (retA)
				execute_command("sa", stack_A, stack_B);
			else if (retB)
				execute_command("sb", stack_A, stack_B);
			execute_command("rr", stack_A, stack_B);
			execute_command("rr", stack_A, stack_B);
		}
	}
}

int 	merge_sort(t_list **stack_A, t_list **stack_B, size_t size)
{
	size_t chunk;
	
	chunk = 1;
	half(stack_A, stack_B, size);
	operate_chunk(stack_A, stack_B, chunk, size);
	return (chunk);	
}

#include <stdio.h>
int main(int argc, char *argv[])
{
	size_t size;
	t_list **stack_A;
	t_list **stack_B;
	int *arr_sorted;
	char *op_line;

	size = check_input(argc, argv);
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(argc, argv, stack_A);
	arr_sorted = insertion_sort(*stack_A, size);
	op_line = 0;
	stack_B = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(0, NULL, stack_B);
/*	while (get_next_line(&op_line))
	{
		if  (!execute_command(op_line, stack_A, stack_B)) 
		{
			free(op_line);
			exit_error(4, (void *)stack_A, free_stack, arr_sorted);
		}
		free(op_line);
		op_line = 0;
	}
	check_if_stack_sorted(stack_A, size, 1, arr_sorted);*/
	half(stack_A, stack_B, size);
	merge_sort(stack_A, stack_B, size);
}
