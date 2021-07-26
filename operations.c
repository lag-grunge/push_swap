
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

void	partition(t_list **stack2, t_list **stack1, size_t part, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (seek_pos(*stack1, part, size))
		{
			push(stack2, stack1); 
			i++;
		}
		else
			rotate(stack1);
	}
}
