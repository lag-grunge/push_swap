#include "push_swap.h"

static void	put_command(char *op_line)
{
	write(1, op_line, ft_strlen(op_line));
	write(1, "\n", 1);
}

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
	put_command(op_line);
	return (1);
}
