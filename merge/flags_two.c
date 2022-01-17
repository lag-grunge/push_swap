/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:02:03 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:02:04 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

static void	correct_set_flag_second(t_dlist *cur, size_t start)
{
	while (get_pos(cur->prev) < get_pos(cur))
	{
		*set_flag(cur->prev) = start;
		cur = cur->prev;
	}
}

void	merge_set_flag_second(t_dlist *cur, size_t *start)
{
	static int	flag;
	size_t		next_flag;
	size_t		cur_pos;
	size_t		prev_pos;
	size_t		next_pos;

	next_flag = get_flag(cur->next);
	cur_pos = get_pos(cur);
	next_pos = get_pos(cur->next);
	if (!flag || (next_flag == *start && cur_pos < next_pos))
		*set_flag(cur) = *start;
	else
	{
		prev_pos = get_pos(cur->prev);
		if (prev_pos < cur_pos)
			*set_flag(cur) = get_flag(cur->prev);
		else
			*set_flag(cur) = get_flag(cur->prev) + 1;
	}
	if (!flag)
		flag = 1;
	if (next_flag == *start && cur_pos < next_pos)
		correct_set_flag_second(cur, *start);
}
