/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_n_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:47:40 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:47:42 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	exec_n_cmd_merge(int cmd_num, size_t n, t_merge *data)
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
