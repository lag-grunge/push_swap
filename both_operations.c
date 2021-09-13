#include "push_swap.h"

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
