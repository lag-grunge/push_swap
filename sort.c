#include "push_swap.h"

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

void	debug_print_stack(t_list **stack_A, t_list **stack_B)
{
	printf("stack_A\n");
	print_stack(*stack_A);
	if (stack_B)
	{
		printf("stack_B\n");
		print_stack(*stack_B);
	}
}

void	operate_chunk(t_list **stack_A, t_list **stack_B, size_t size, size_t chunk)
{
	size_t	i;
	size_t  i_A;
	int		retA;
	int		retB;
	char	*op_line;
	
	i_A = ft_lstsize(*stack_A);
	i = 0;
	while (i < i_A - 1 || i < size - i_A - 1)
	{	
		retA = 0;
		retB = 0;
		op_line = "rr";
		if (get_pos(*stack_A, 0) > get_pos(*stack_A, 1) && i < i_A - 1)
			retA = 1;
		if (get_pos(*stack_B, 0) > get_pos(*stack_B, 1) && i < size - i_A - 1)
			retB = 1;
		if (retA && retB)
			execute_command("ss", stack_A, stack_B);
		else if (retA)
			execute_command("sa", stack_A, stack_B);
		else if (retB)
			execute_command("sb", stack_A, stack_B);
		if (i >= i_A - 1 && i < size - i_A - 1)
			op_line = "rb";
		else if (i < i_A - 1 && i >= size - i_A - 1)
			op_line = "ra";
		execute_command(op_line, stack_A, stack_B);
		execute_command(op_line, stack_A, stack_B);
		i += 2;
		debug_print_stack(stack_A, stack_B);
	}
}

int 	merge_sort(t_list **stack_A, t_list **stack_B, size_t size)
{
	size_t chunk;
	
	half(stack_A, stack_B, size);
	debug_print_stack(stack_A, stack_B);
	chunk = 1;
	operate_chunk(stack_A, stack_B, size, chunk);
	return (chunk);	
}

size_t	bytes_count(size_t size)
{
	size_t	bytes;

	bytes = 1;
	size >>= 1;
	while (size)
	{
		size >>= 1;
		bytes++;
	}
	return (bytes);
}

void radix_sort(t_list **stack_A, t_list **stack_B, size_t size)
{
	size_t	byte;
	size_t	bytes;
	size_t	cur;
	size_t	i;

	bytes = bytes_count(size);
	byte = 0;
	while (byte < bytes)
	{
		i = 0;
		while (i < size)
		{
			cur = get_pos(*stack_A, 0);
			if (((cur>>byte)&1) == 0) 
				execute_command("pb", stack_A, stack_B);
			else
				execute_command("ra", stack_A, stack_B);
			i++;
		}
		while (*stack_B)
			execute_command("pa", stack_A, stack_B);
		byte++;
	}
}

void big_sort(t_list **stack_A, t_list **stack_B, size_t size)
{
	//radix_sort(stack_A, stack_B, size);
	merge_sort(stack_A, stack_B, size);
}
