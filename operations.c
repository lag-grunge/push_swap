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
    if (!*stack1)
    {
        elem->next = elem;
        elem->prev = elem;
        *stack1 = elem;
    }
	elem->next = *stack1;
    elem->prev = (*stack1)->prev;
    (*stack1)->prev->next = elem;
    (*stack1)->prev = elem;
    *stack1 = elem;
}

void	swap(t_dlist **stack)
{
	t_dlist	*first;
	t_dlist	*second;
	t_dlist	*third;
    t_dlist *last;

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