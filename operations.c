#include "push_swap.h"

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

size_t	get_pos(t_list *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->pos);
}

int		get_val(t_list *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->val);
}

#include <stdio.h>
int execute_command(char *op_line, t_list **stack_A, t_list **stack_B)
{
	if (!ft_strncmp("ra", op_line, 3))
		ra
	else if (!ft_strncmp("rra", op_line, 3))
		rra
	else if (!ft_strncmp("pa", op_line, 3))
		pa
	else if (!ft_strncmp("sa", op_line, 3))
		sa
	else if (!ft_strncmp("rb", op_line, 3))
		rb
	else if (!ft_strncmp("rrb", op_line, 3))
		rrb
	else if (!ft_strncmp("pb", op_line, 3))
		pb
	else if (!ft_strncmp("sb", op_line, 3))
		sb
	else if (!ft_strncmp("rr", op_line, 3))
		rr
	else if (!ft_strncmp("rrr", op_line, 3))
		rrr
	else if (!ft_strncmp("ss", op_line, 3))
		ss
	else
		return (0);
	write(1, op_line, ft_strlen(op_line));
	write(1, "\n", 1);
	return (1);
}
