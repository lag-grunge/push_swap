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
	radix_sort(stack_A, stack_B, size);
}
