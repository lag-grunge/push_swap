#include "push_swap.h"

void	small_2(t_list **stack_A, int order, int start)
{
	int	second;

	second = start + 1 - order;
	if (seek_pos(stack_A, second, 1))
		swap(stack_A);
	return ;
}

void	small_3(t_list **stack_A, int order, int start)
{
	int	second;
	int	third;

	second = start + 1;	
	third = start + (1 - order) * 2;
	if (seek_pos(stack_A, third, 1))
		rotate(stack_A);
	else if (seek_pos(stack_A->next, third, 1))
		reverse_rotate(stack_A);
	if (seek_pos(stack_A, second, 1))
		swap(stack_A);
}

void	small_4(t_list	**stack_A, t_list **stack_B, int order, int start)
{
	int	first;

	first = start + order * 3;
	partition(stack_B, stack_A, first, 1);
	small_3(stack_A, order, start + (1 - order));
	partition(stack_A, stack_B, first, 1);
}

void	small_5(t_list	**stack_A, t_list **stack_B, int order, int start)
{
	int	first;
	int	second;
	int	third;
	int	min;

	first = start + order * 4;
	second = start + (1 - order) * 1 + order * 3;
	min = first;
	if (order)
		min = second;
	partition(stack_B, stack_A, min, 2);
	small_3(stack_A, );
	small_2(stack_B, );

}
