/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pair_chunks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:50:12 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:50:17 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

static void	o_both_tail_equal(t_merge *data)
{
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = data->stack_a;
	stack_b = data->stack_b;
	if (get_pos(*stack_a) < get_pos(*stack_b))
	{
		execute_command("pb", stack_a, stack_b, 0);
		exec_n_cmd_merge(rb, 2, data);
		merge_fl_change_bottom(*stack_b, 2, data->cur_flag);
		data->i_b++;
	}
	else
	{
		execute_command("pa", stack_a, stack_b, 0);
		exec_n_cmd_merge(ra, 2, data);
		merge_fl_change_bottom(*stack_a, 2, data->cur_flag);
		data->i_a++;
	}
}

static void	o_a_tail_longer(t_dlist **stack_a, t_dlist **stack_b, t_merge *data)
{
	if (get_flag((*stack_a)->next) > data->cur_flag)
	{
		if (get_pos(*stack_a) > get_pos((*stack_a)->next))
			execute_command("sa", stack_a, stack_b, 0);
		execute_command("rr", stack_a, stack_b, 0);
		execute_command("ra", stack_a, stack_b, 0);
		merge_fl_change_bottom(*stack_a, 2, data->cur_flag);
		merge_fl_change_bottom(*stack_b, 1, data->cur_flag + 1);
	}
	else
	{
		execute_command("ra", stack_a, stack_b, 0);
		merge_fl_change_bottom(*stack_a, 1, data->cur_flag);
	}
	data->i_a++;
}

static void	o_tail_2chnks(t_merge *data)
{
	size_t	tail_a;
	size_t	tail_b;
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = data->stack_a;
	stack_b = data->stack_b;
	tail_a = find_chunk_size(*stack_a, data->cur_flag);
	tail_a += find_chunk_size((*stack_a)->next, data->cur_flag);
	tail_b = find_chunk_size(*stack_b, data->cur_flag);
	if (tail_a == tail_b)
		o_both_tail_equal(data);
	else
		o_a_tail_longer(stack_a, stack_b, data);
	data->cur_flag = 0;
}

static void	oper_two_top_elem(t_merge *data)
{
	char	ret;
	int		cmd_num;
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = data->stack_a;
	stack_b = data->stack_b;
	ret = 0;
	if (get_pos(*stack_a) > get_pos((*stack_a)->next))
		ret |= 1;
	if (get_pos(*stack_b) > get_pos((*stack_b)->next))
		ret |= 2;
	cmd_num = sa + (ret - 1) * 4;
	if (ret)
		exec_n_cmd_merge(cmd_num, 1, data);
	exec_n_cmd_merge(rr, 2, data);
	merge_fl_change_bottom(*stack_b, 2, data->cur_flag);
	merge_fl_change_bottom(*stack_a, 2, data->cur_flag + 1);
	data->cur_flag += 2;
}

void	init_2chnks(t_merge *data)
{
	size_t	ib;
	size_t	ia;

	ib = data->i_b;
	ia = data->i_a;
	while (ib > 1)
	{
		oper_two_top_elem(data);
		ib -= 2;
		ia -= 2;
	}
	data->i_a = data->i_b / 2;
	data->i_b = data->i_b / 2;
	if (!ib && !ia)
	{
		data->cur_flag = 0;
		return ;
	}
	o_tail_2chnks(data);
}
