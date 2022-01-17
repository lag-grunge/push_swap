/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asipes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:31:10 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:32:21 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "asipes_sort.h"

void	init_data(t_cmn_asip_data *cmn_data, t_stck_data *data)
{
	cmn_data->flag = 0;
	cmn_data->next = 0;
	cmn_data->cmd_array = data->cmd_array;
	cmn_data->op_lines = data->op_lines;
}

void	restore_size(t_cmn_asip_data *cmn_data, t_stck_data *data)
{
	cmn_data->size = data->size - 1;
	cmn_data->max = data->size - 1;
	cmn_data->mid = (cmn_data->max + cmn_data->next) / 2;
}

void	asip_fl_change(t_dlist **stack_a)
{
	t_dlist		*cur;
	t_ps_data	*content;

	cur = *stack_a;
	content = NULL;
	while (cur != *stack_a || !content)
	{
		content = cur->content;
		content->flag = 0;
		cur = cur->next;
	}
}

void	exec_n_cmd_asip(int cmd_num, size_t n, t_cmn_asip_data *data)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (ra <= cmd_num && cmd_num < pa)
			data->cmd_array[cmd_num](data->stack_a);
		else if (rb <= cmd_num && cmd_num < pb)
			data->cmd_array[cmd_num](data->stack_b);
		else if (pa == cmd_num || (rr <= cmd_num && cmd_num <= ss))
			data->cmd_array[cmd_num](data->stack_a, data->stack_b);
		else if (pb == cmd_num)
			data->cmd_array[cmd_num](data->stack_b, data->stack_a);
		put_command(data->op_lines[cmd_num]);
		i++;
	}
}
