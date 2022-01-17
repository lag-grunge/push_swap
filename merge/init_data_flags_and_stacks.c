/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_flags_and_stacks.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:47:08 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:47:11 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

size_t	init_oper_one_nchnk(t_merge *data, size_t *chunk_0, size_t *chunk_1)
{
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	*chunk_0 = find_chunk_size(*st_ptr[first_stack], data->cur_flag);
	*chunk_1 = find_chunk_size(*st_ptr[second_stack], data->cur_flag);
	if (!*chunk_0 && st_ptr[stack_for_input] == st_ptr[first_stack])
		st_ptr[stack_for_input] = st_ptr[second_stack];
	if (!*chunk_1 && st_ptr[stack_for_input] == st_ptr[second_stack])
		st_ptr[stack_for_input] = st_ptr[first_stack];
	return (*chunk_0 + *chunk_1);
}

static void	half_2stack_b(size_t size, t_merge *data)
{
	size_t	i;
	t_dlist	**stack_a;
	t_dlist	**stack_b;

	i = 0;
	stack_a = data->stack_a;
	stack_b = data->stack_b;
	while (i < size / 2)
	{
		execute_command("pb", stack_a, stack_b, 0);
		i++;
	}
	data->i_a = size - i;
	data->i_b = i;
}

void	init_data_flags(t_merge *data, t_stck_data *cmn_data)
{
	data->size = cmn_data->size;
	data->cmd_array = cmn_data->cmd_array;
	data->op_lines = cmn_data->op_lines;
	data->cur_flag = 0;
}

void	init_data_stacks(t_merge *data, t_dlist **stack_b, t_dlist **stack_a)
{
	data->stack_a = stack_a;
	data->stack_b = stack_b;
	merge_fl_change(*stack_a, 0, NULL);
	half_2stack_b(data->size, data);
	data->cur_flag = 0;
}
