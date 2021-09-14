#include "push_swap.h"

void 	half(t_list **stack_A, t_list **stack_B, size_t sizet_stck_data *data)
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

void set_chunk_flag(t_list *stack, size_t chunk_size, size_t flag)
{
	size_t	i;
	t_list	*cur_list;

	i = 0;
	cur_list = stack_A;
	while (i < chunk_size)
	{
		*(set_flag(cur_list)) = flag;
		cur_list = cur_list->next;
		i++;
	}
}

void	o_chnk(t_list **stack_A, t_list **stack_B, size_t i, t_stck_data *data)
{
	int		retA;
	int		retB;
	char	*op_line;
	static size_t	flag;	

	retA = 0;
	retB = 0;
	chunk_size = 2;
	op_line = "rr";
	set_chunk_flag(stack_A, chunk_size, );
	if (get_pos(*stack_A) > get_pos((*stack_A)->next) && i < data->i_A - 1)
		retA = 1;
	if (get_pos(*stack_B) > get_pos((*stack_B)->next) && i < data->i_B - 1)
		retB = 1;
	if (retA && retB)
		execute_command("ss", stack_A, stack_B);
	else if (retA)
		execute_command("sa", stack_A, stack_B);
	else if (retB)
		execute_command("sb", stack_A, stack_B);
	if (i >= data->i_A - 1 && i < data->i_B - 1)
		op_line = "rb";
	else if (i < data->i_A - 1 && i >= data->i_B - 1)
		op_line = "ra";
	execute_command(op_line, stack_A, stack_B);
	execute_command(op_line, stack_A, stack_B);
	debug_print_stack(stack_A, stack_B);
}

void	o_tchnk(t_list **stack_A, t_list **stack_B, size_t i, t_stck_data *data)
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

void	merge_chunk(t_list **stack_A, t_list **stack_B, t_stck_data *data)
{
	size_t	i;
	
	i = 0;
	while (i < data->i_A - 1 && i < data->i_B - 1)
	{	
		o_chnk(stack_A, stack_B, i, data);
		i += 2;
	}
	o_tchnk(stack_A, stack_B, i, data);
}

int 	merge_sort(t_list **stack_A, t_list **stack_B, t_stck_data *data)
{
	size_t chunk;
	
	data_change(stack_A);
	half(stack_A, stack_B, data->size);
	chunk = 1;
	merge_chunk(stack_A, stack_B, data);
	return (chunk);	
}
