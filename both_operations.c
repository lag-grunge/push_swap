#include "push_swap.h"
#include "libft.h"

void	rotate_both(t_list **stack, t_list **stack2)
{
	rotate(stack);
	rotate(stack2);
}

void	reverse_rotate_both(t_list **stack, t_list **stack2)
{
	reverse_rotate(stack);
	reverse_rotate(stack2);
}

void	swap_both(t_list **stack, t_list **stack2)
{
	swap(stack);
	swap(stack2);
}

void	partition(t_list **stack_B, t_list **stack_A, size_t part, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (seek_pos(*stack_A, part, size))
		{
			pb
			write(1, "pb\n", 3);
			i++;
		}
		else
		{
			ra
			write(1, "ra\n", 3);
		}
	}
}
