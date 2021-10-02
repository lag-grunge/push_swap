#include "push_swap.h"

static size_t	bytes_count(size_t size)
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

void	radix_sort(t_dlist **stack_A, t_dlist **stack_B, size_t size)
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
			cur = get_pos(*stack_A);
			if (((cur >> byte) & 1) == 0)
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
