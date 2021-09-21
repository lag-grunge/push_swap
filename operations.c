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

void	push(t_dlist **stack1, t_dlist **stack2)
{
	t_dlist *elem;

	elem = *stack2;
    ft_dlst_pop(stack2, elem);

	elem->next = *stack1;
    elem->prev = (*stack1)->prev;
    (*stack1)->prev->next = elem;
    (*stack1)->prev = elem;
    *stack1 = elem;
}

void	swap(t_dlist **stack)
{
	t_dlist	*elem;
	t_dlist	*second;
	t_dlist	*third;
    t_dlist *last;

	elem = *stack;
	if (!elem)
		return ;
	second = elem->next;
	if (second == elem)
		return ;
	third = second->next;
    if (third == elem)
    {
        *stack = second;
        return ;
    }
    last = elem->prev;
    elem->next = third;
	second->next = elem;
    last->next = second;
    elem->prev = ;
    third->prev = elem;
	*stack = second;
}
