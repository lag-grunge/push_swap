#include "push_swap.h"

static void	put_command(char *op_line)
{
	write(1, op_line, ft_strlen(op_line));
	write(1, "\n", 1);
}

int execute_command(char *op_line, t_dlist **stack_A, t_dlist **stack_B)
{
	if (!ft_strncmp("ra", op_line, 3))
		rotate(stack_A);
	else if (!ft_strncmp("rra", op_line, 3))
		reverse_rotate(stack_A);
	else if (!ft_strncmp("pa", op_line, 3))
		push(stack_A, stack_B);
	else if (!ft_strncmp("sa", op_line, 3))
		swap(stack_A);
	else if (!ft_strncmp("rb", op_line, 3))
		rotate(stack_B);
	else if (!ft_strncmp("rrb", op_line, 3))
		reverse_rotate(stack_B);
	else if (!ft_strncmp("pb", op_line, 3))
		push(stack_B, stack_A);
	else if (!ft_strncmp("sb", op_line, 3))
		swap(stack_B);
	else if (!ft_strncmp("rr", op_line, 3))
		rotate_both(stack_A, stack_B);
	else if (!ft_strncmp("rrr", op_line, 3))
		reverse_rotate_both(stack_A, stack_B);
	else if (!ft_strncmp("ss", op_line, 3))
		swap_both(stack_A, stack_B);
	else
		return (0);
	put_command(op_line);
	return (1);
}
