#include "push_swap.h"

void	rotate(t_dlist **stack)
{
	if (stack && *stack)
		*stack = (*stack)->next;
}

void	reverse_rotate(t_dlist **stack)
{
	if (stack && *stack)
		*stack = (*stack)->prev;
}

void	push(t_dlist **stack_for_input, t_dlist **stack_output)
{
	t_dlist	*elem;

	if (!*stack_output)
		return ;
	elem = ft_dlst_pop(stack_output, *stack_output);
	if (!*stack_for_input)
	{
		elem->next = elem;
		elem->prev = elem;
		*stack_for_input = elem;
		return ;
	}
	elem->next = *stack_for_input;
	elem->prev = (*stack_for_input)->prev;
	(*stack_for_input)->prev->next = elem;
	(*stack_for_input)->prev = elem;
	*stack_for_input = elem;
}

void	swap(t_dlist **stack)
{
	t_dlist	*first;
	t_dlist	*second;
	t_dlist	*third;
	t_dlist	*last;

	first = *stack;
	if (!first)
		return ;
	second = first->next;
	third = second->next;
	last = first->prev;
	*stack = second;
	if (second == first || third == first)
		return ;
	first->next = third;
	second->next = first;
	last->next = second;
	first->prev = second;
	second->prev = last;
	third->prev = first;
}
