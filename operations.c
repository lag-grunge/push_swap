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
    t_dlist *neigh_next;
    t_dlist *neigh_prev;

	elem = *stack2;
    ft_dlst_pop(stack2, elem, &free);

	elem->next = *stack1;
    elem->prev = (*stack1)->prev;

}

void	swap(t_dlist **stack)
{
	t_dlist	*elem;
	t_dlist	*second;
	t_dlist	*third;

	elem = *stack;
	if (!elem)
		return ;
	second = elem->next;
	if (!second)
		return ;
	third = second->next;
	second->next = elem;
	elem->next = third;
	*stack = second;
}
