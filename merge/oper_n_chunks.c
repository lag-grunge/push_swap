/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_n_chunks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:01:25 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:01:27 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

/* merge chunks of one size, accurately not more than this size
 * we operate one pair of chunks, then rotate merged result on the
 * bottom as these chunks are situated on top of the stacks A and B
 * we found size of chunks, if this size eq 0, it means this chunk new
 * one so we've rotated whole stack and can continue only with other
 * if it has chunk */

static int	criteria(t_merge *data, int mode, int oper)
{
	int		ret1;
	int		ret2;
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	ret1 = 0;
	ret2 = 0;
	if (oper == from_b_to_a || oper == from_b_to_b)
		ret1 = (st_ptr[cur_stack] == data->stack_b);
	else if (oper == from_a_to_a || oper == from_a_to_b)
		ret1 = (st_ptr[cur_stack] == data->stack_a);
	if (!mode)
		return (ret1);
	if (oper == from_b_to_a || oper == from_b_to_b)
		ret2 = (get_pos(*data->stack_a) > get_pos(*data->stack_b));
	else if (oper == from_a_to_a || oper == from_a_to_b)
		ret2 = (get_pos(*data->stack_a) < get_pos(*data->stack_b));
	return (ret1 && ret2);
}

static void	oper_elem(t_merge *data, int mode, int (*crit)(), size_t *im)
{
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	if (st_ptr[stack_for_input] == data->stack_a)
	{
		if (crit(data, mode, from_b_to_a))
		{
			execute_command("pa", data->stack_a, data->stack_b, 0);
			*im -= execute_command("ra", data->stack_a, data->stack_b, 0);
		}
		else if (crit(data, mode, from_a_to_a))
			*im -= execute_command("ra", data->stack_a, data->stack_b, 0);
	}
	else if (st_ptr[stack_for_input] == data->stack_b)
	{
		if (crit(data, mode, from_a_to_b))
		{
			execute_command("pb", data->stack_a, data->stack_b, 0);
			*im -= execute_command("rb", data->stack_a, data->stack_b, 0);
		}
		else if (crit(data, mode, from_b_to_b))
			*im -= execute_command("rb", data->stack_a, data->stack_b, 0);
	}
}

static int	oper_one_nchnk(t_merge *data)
{
	size_t	chunk_0;
	size_t	chunk_1;
	size_t	chunk_res;
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	chunk_res = init_oper_one_nchnk(data, &chunk_0, &chunk_1);
	if (!chunk_res)
		return (0);
	while (chunk_0 || chunk_1)
	{
		st_ptr[cur_stack] = st_ptr[first_stack];
		if (chunk_0)
			oper_elem(data, chunk_0 && chunk_1, &criteria, &chunk_0);
		st_ptr[cur_stack] = st_ptr[second_stack];
		if (chunk_1)
			oper_elem(data, chunk_1 && chunk_0, &criteria, &chunk_1);
	}
	merge_fl_change_bottom(*st_ptr[stack_for_input], chunk_res, data->cur_flag);
	data->cur_flag++;
	if (st_ptr[stack_for_input] == data->stack_a)
		data->i_a++;
	else
		data->i_b++;
	return (1);
}

void	init_merge_chunks(t_merge *data, size_t *min, size_t *max)
{
	t_dlist	**cur_stack;
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	st_ptr[first_stack] = data->stack_a;
	st_ptr[second_stack] = data->stack_b;
	*min = data->i_b;
	*max = data->i_a;
	if (data->i_a <= data->i_b)
	{
		cur_stack = st_ptr[second_stack];
		st_ptr[second_stack] = st_ptr[first_stack];
		st_ptr[first_stack] = cur_stack;
		*min = data->i_a;
		*max = data->i_b;
	}
}

void	merge_chunks_of_one_size(t_merge *data)
{
	size_t	i_min;
	size_t	i_max;
	t_dlist	***st_ptr;

	st_ptr = data->st_ptr;
	init_merge_chunks(data, &i_min, &i_max);
	while (i_max || i_min)
	{
		st_ptr[stack_for_input] = st_ptr[second_stack];
		if (i_max)
			oper_one_nchnk(data);
		i_min -= (i_max > 0 && i_min > 0);
		i_max -= (i_max > 0);
		st_ptr[stack_for_input] = st_ptr[first_stack];
		if (i_min)
			oper_one_nchnk(data);
		i_max -= (i_min > 0 && i_max > 0);
		i_min -= (i_min > 0);
	}
	data->cur_flag = 0;
}
