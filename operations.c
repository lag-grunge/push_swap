
#include "push_swap.h"
#include "libft.h"

void	rotate(t_list **stack)
{
	t_list	*elem;

	elem = *stack;
	if (!elem || !elem->next)
		return ;
	*stack = elem->next;
	(ft_lstlast(*stack))->next = elem;
	elem->next = NULL;
}

void	reverse_rotate(t_list **stack)
{
	t_list	*elem;
	t_list	*cur;

	cur = *stack;
	if (!cur || !cur->next)
		return ;
	elem = ft_lstlast(*stack);
	while (cur->next != elem)
		cur = cur->next;
	cur->next = NULL;
	ft_lstadd_front(stack, elem);
}

void	push(t_list **stack1, t_list **stack2)
{
	t_list	*elem;

	elem = *stack2;
	if (!elem)
		return ;
	*stack2 = elem->next;
	elem->next = NULL;
	ft_lstadd_front(stack1, elem);
}

void	swap(t_list **stack)
{
	t_list	*elem;
	t_list	*second;
	t_list	*third;

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

int	seek_pos(t_list *stack, size_t part, size_t size)
{
	size_t	pos;

	pos = ((t_ps_data *)(stack->content))->pos;
	if (pos >= part && pos < part + size)
		return (1);
	return (0);
}

size_t	get_pos(t_list *stack, size_t i)
{
	size_t	j;

	j = 0;
	while (j++ < i)
		stack = stack->next;
	return (((t_ps_data *)(stack->content))->pos);
}
