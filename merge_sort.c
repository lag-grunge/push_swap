#include "push_swap.h"

void 	merge_fl_change(t_list **stack_A)
{
	t_list		*cur;

	cur = *stack_A;
	while (cur)
	{
		cur->content->flag = cur->content->pos;
		cur = cur->next;
	}
}

void 	half(t_dlist **stack_A, t_dlist **stack_B, size_t size, t_stck_data *data)
{
	size_t	i;

	i = 0;
	while (i < size / 2)
	{
		execute_command("pb", stack_A, stack_B);
		i++;
	}
	data->i_A = data->size - i;
	data->i_B = i;
}

void	move_chunk_bottom(t_dlist *stack_A, t_dlist *stack_B, size_t new_flag, t_stck_data *data)
{
	size_t	flag;
	t_dlist *stack;
	size_t	chunks;
	char	*op_line;

	stack = stack_A;
	chunks = data->i_A;
	op_line = "ra";
	if (stack_B)
	{
		stack = stack_B;
		chunks = data->i_B;
		op_line = "rb";
	}
	if (chunks == 1)
		return ;
	flag = stack->content->flag;
	while (stack->content->flag == flag)
	{
		execute_command(op_line, stack_A, stack_B);
		*set_flag(stack->prev) = new_flag;
	}
}

size_t	find_chunk_size(t_dlist *stack, size_t chunk_size, size_t cur_flag)
{
	size_t	flag;
	size_t	ret;

	ret = 1;
	flag = stack->content->flag;
	stack = stack->next;
	while (stack->content->flag == flag)
	{
		ret++;
		stack = stack->next;
	}
	if (ret > chunk_size)
		ret = 0;
	return (ret);
}

void	one_chnk(t_dlist **stack_A, t_dlist **stack_B, size_t chunk_size, t_stck_data *data)
{
	int				rotate;
	size_t 			chunk_a;
	size_t 			chunk_b;
	static size_t	cur_flag;

	rotate = 0;
	chunk_a = find_chunk_size(*stack_A, chunk_size, cur_flag);
	chunk_b = find_chunk_size(*stack_B, chunk_size, cur_flag);
	if (chunk_a && chunk_b)
		rotate = two_chnk_merge(stack_A, stack_B, data);
	else if (!chunk_a && chunk_b)
	{
		rotate = 2;
		move_chunk_bottom(NULL, *stack_B, cur_flag, data);
	}
	else if (!chunk_b && chunk_a)
	{
		rotate = 1;
		move_chunk_bottom(*stack_A, NULL, cur_flag, data);
	}
}

int two_chnk_merge(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	if (chunk_size == 1)
	{
		int		retA;
		int		retB;
		retA = 0;
		retB = 0;
		op_line = "rr";
		if (get_pos(*stack_A) > get_pos((*stack_A)->next))
			retA = 1;
		if (get_pos(*stack_B) > get_pos((*stack_B)->next))
			retB = 1;
		if (retA && retB)
			execute_command("ss", stack_A, stack_B);
		else if (retA)
			execute_command("sa", stack_A, stack_B);
		else if (retB)
			execute_command("sb", stack_A, stack_B);
		set_chunk_flag(stack, chunk_size, flag);
	}
	else
	{

	}
	debug_print_stack(stack_A, stack_B);
}

void	o_tail_chnk(t_dlist **stack_A, t_dlist **stack_B, size_t i, t_stck_data *data)
{
	if (i == data->i_A - 1 && i == data->i_B - 1)
	{
		
		if (get_pos(*stack_A) < get_pos(*stack_B))
		{
			execute_command("pb", stack_A, stack_B);
			execute_command("rb", stack_A, stack_B);
			execute_command("rb", stack_A, stack_B);
		}
		execute_command("pa", stack_A, stack_B);
		execute_command("ra", stack_A, stack_B);
		execute_command("ra", stack_A, stack_B);
		return ;
	}
	if (get_pos(*stack_A) > get_pos((*stack_A)->next) && i < data->i_A - 1)
			execute_command("sa", stack_A, stack_B);
	execute_command("rr", stack_A, stack_B);
	execute_command("ra", stack_A, stack_B);
}

void	merge_chunks(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data, size_t chunk_size)
{
	size_t	i;
	size_t	iterations;
	
	i = 0;
	iterations = (data->i_A + data->i_B + 1) / 2;
	while (i < iterations)
	{
		one_chnk(stack_A, stack_B, data, chunk_size);
		i++;
	}
}

void 	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	size_t chunk_size;
	
	half(stack_A, stack_B, data->size);
	chunk_size = 1;
	while (data->i_A > 1 && data->i_B > 0)
	{
		merge_chunks(stack_A, stack_B, data, chunk_size);
		chunk_size *= 2;
	}
	return ;	
}

//ПЕРЕБРОСИТЬ ПОЛОВИНУ В СТЕК Б
//РАЗМЕР ЦЕПОЧЕК = 1
//ПОКА НЕ ПОЛУЧИТСЯ БОЛЬШАЯ ЦЕПОЧКА (=data->size)
//	ОБЪЕДИНЯТЬ ЦЕПОЧКИ (ИЗ РАЗНЫХ СТЕКОВ >= 2 из ОДНОГО ЕСЛИ == 1, кроме случая когда на конце осталось по 1 элементу ) 

