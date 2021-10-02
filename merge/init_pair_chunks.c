#include "push_swap.h"
#include "merge_sort.h"

static void	o_both_tail_equal(t_merge *data)
{
	t_dlist	**stack_A;
	t_dlist	**stack_B;

	stack_A = data->stack_A;
	stack_B = data->stack_B;
	if (get_pos(*stack_A) < get_pos(*stack_B))
	{
		execute_command("pb", stack_A, stack_B, 0);
		exec_n_cmd_merge(rb, 2, data);
		merge_fl_change_bottom(*stack_B, 2, data->cur_flag);
		data->i_B++;
	}
	else
	{
		execute_command("pa", stack_A, stack_B, 0);
		exec_n_cmd_merge(ra, 2, data);
		merge_fl_change_bottom(*stack_A, 2, data->cur_flag);
		data->i_A++;
	}
}

static void	o_a_tail_longer(t_dlist **stack_A, t_dlist **stack_B, t_merge *data)
{
	if (get_flag((*stack_A)->next) > data->cur_flag)
	{
		if (get_pos(*stack_A) > get_pos((*stack_A)->next))
			execute_command("sa", stack_A, stack_B, 0);
		execute_command("rr", stack_A, stack_B, 0);
		execute_command("ra", stack_A, stack_B, 0);
		merge_fl_change_bottom(*stack_A, 2, data->cur_flag);
		merge_fl_change_bottom(*stack_B, 1, data->cur_flag + 1);
	}
	else
	{
		execute_command("ra", stack_A, stack_B, 0);
		merge_fl_change_bottom(*stack_A, 1, data->cur_flag);
	}
	data->i_A++;
}

static void	o_tail_2chnks(t_merge *data)
{
	size_t	tailA;
	size_t	tailB;
	t_dlist	**stack_A;
	t_dlist	**stack_B;

	stack_A = data->stack_A;
	stack_B = data->stack_B;
	tailA = find_chunk_size(*stack_A, data->cur_flag);
	tailA += find_chunk_size((*stack_A)->next, data->cur_flag);
	tailB = find_chunk_size(*stack_B, data->cur_flag);
	if (tailA == tailB)
		o_both_tail_equal(data);
	else
		o_a_tail_longer(stack_A, stack_B, data);
	data->cur_flag = 0;
}

static void	oper_two_top_elem(t_merge *data)
{
	char	ret;
	int		cmd_num;
	t_dlist	**stack_A;
	t_dlist	**stack_B;

	stack_A = data->stack_A;
	stack_B = data->stack_B;
	ret = 0;
	if (get_pos(*stack_A) > get_pos((*stack_A)->next))
		ret |= 1;
	if (get_pos(*stack_B) > get_pos((*stack_B)->next))
		ret |= 2;
	cmd_num = sa + (ret - 1) * 4;
	if (ret)
		exec_n_cmd_merge(cmd_num, 1, data);
	exec_n_cmd_merge(rr, 2, data);
	merge_fl_change_bottom(*stack_B, 2, data->cur_flag);
	merge_fl_change_bottom(*stack_A, 2, data->cur_flag + 1);
	data->cur_flag += 2;
}

void	init_2chnks(t_merge *data)
{
	size_t	ib;
	size_t	ia;

	ib = data->i_B;
	ia = data->i_A;
	while (ib > 1)
	{
		oper_two_top_elem(data);
		ib -= 2;
		ia -= 2;
	}
	data->i_A = data->i_B / 2;
	data->i_B = data->i_B / 2;
	if (!ib && !ia)
	{
		data->cur_flag = 0;
		return ;
	}
	o_tail_2chnks(data);
}
