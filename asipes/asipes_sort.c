/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asipes_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:31:28 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:31:36 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "asipes_sort.h"

static void	move_a_b(t_dlist **stack_a, t_dlist **stack_b, \
					t_cmn_asip_data *data)
{
	size_t	i;
	size_t	cur_pos;
	t_dlist	*last_a;

	i = data->next;
	last_a = (*stack_a)->prev;
	while (i <= data->mid)
	{
		cur_pos = get_pos(*stack_a);
		if (cur_pos <= data->mid && cur_pos >= data->next)
			i++;
		if (cur_pos == data->next && get_pos(last_a) == data->next - 1)
		{
			execute_command("ra", stack_a, stack_b, 0);
			data->next++;
		}
		else if (cur_pos > data->mid || cur_pos < data->next)
			execute_command("ra", stack_a, stack_b, 0);
		else
			execute_command("pb", stack_a, stack_b, 0);
		last_a = last_a->next;
	}
	data->max = data->mid;
}

static void	oper_b(t_cmn_asip_data *data, int sec)
{
	int		i;
	int		size_b;
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	stack_a = data->stack_a;
	stack_b = data->stack_b;
	size_b = ft_dlst_size(*stack_b);
	correct_a_chain(stack_a, data);
	i = 0;
	while (size_b)
	{
		if (!sec)
			data->flag++;
		data->mid = (data->max + data->next) / 2;
		while (i < size_b)
			i += oper_b_elem(data, sec);
		size_b = ft_dlst_size(*stack_b);
		data->max = data->mid;
		i = 0;
	}
}

static void	oper_a(t_dlist **stack_a, t_dlist **stack_b, t_cmn_asip_data *data)
{
	size_t	cur_flag;

	while (get_flag(*stack_a))
	{
		cur_flag = get_flag(*stack_a);
		restore_data_max_mid(data);
		while (get_flag(*stack_a) == cur_flag)
		{
			if (get_pos(*stack_a) <= data->next)
			{
				data->next++;
				execute_command("ra", stack_a, stack_b, 0);
			}
			else
				execute_command("pb", stack_a, stack_b, 0);
		}
		oper_b(data, 1);
	}
}

int	asipes_sort(t_dlist **stack_a, t_dlist **stack_b, t_stck_data *data)
{
	t_cmn_asip_data	cmn_data;

	asip_fl_change(stack_a);
	init_data(&cmn_data, data);
	cmn_data.stack_a = stack_a;
	cmn_data.stack_b = stack_b;
	while (cmn_data.next <= cmn_data.size)
	{
		restore_size(&cmn_data, data);
		move_a_b(stack_a, stack_b, &cmn_data);
		oper_b(&cmn_data, 0);
		if (cmn_data.next > cmn_data.size)
			break ;
		oper_a(stack_a, stack_b, &cmn_data);
	}
	return (0);
}
