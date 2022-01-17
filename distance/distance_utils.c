/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:59:25 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:59:27 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "distance.h"

static void	count_b(int *actions, t_dlist *stack_b, \
							t_dlist *cur_b, int size_b)
{
	t_dlist	*next;
	t_dlist	*prev;
	int		dist;

	next = stack_b;
	prev = stack_b;
	dist = 0;
	while (next != cur_b && prev != cur_b)
	{
		next = next->next;
		prev = prev->prev;
		dist++;
	}
	if (next == stack_b && prev == stack_b)
		return ;
	else if (next == cur_b)
	{
		actions[f(rb)] = dist;
		actions[f(rrb)] = size_b - dist;
	}
	else if (prev == cur_b)
	{
		actions[f(rrb)] = dist;
		actions[f(rb)] = size_b - dist;
	}
}

static void	count_a(int *actions, t_dlist *stack_a, int pos_b, int size_a)
{
	t_dlist	*next;
	t_dlist	*prev;
	int		dist;

	next = stack_a;
	prev = stack_a;
	dist = 0;
	while (((int)get_pos(next) < pos_b || (int)get_pos(next->prev) > pos_b) && \
		((int)get_pos(prev) < pos_b || (int)get_pos(prev->prev) > pos_b))
	{
		next = next->next;
		prev = prev->prev;
		dist++;
	}
	if (((int)get_pos(next) > pos_b && (int)get_pos(next->prev) < pos_b))
	{
		actions[f(ra)] = dist;
		actions[f(rra)] = size_a - dist;
	}
	else if ((int)get_pos(prev) > pos_b && (int)get_pos(prev->prev) < pos_b)
	{
		actions[f(rra)] = dist;
		actions[f(ra)] = size_a - dist;
	}
}

void	find_best_actions(int *min_actions, t_dlist **stack_a, \
							t_dlist **stack_b, t_stck_data *data)
{
	t_dlist	*cur_b;
	int		one_actions[4];
	int		cur_min;
	int		cur_sum;

	ft_memset(min_actions, 0, sizeof(one_actions));
	count_b(min_actions, *stack_b, *stack_b, (int) data->size_b);
	count_a(min_actions, *stack_a, (int) get_pos(*stack_b), (int) data->size_a);
	cur_min = find_actions(min_actions);
	cur_b = (*stack_b)->next;
	while (cur_b != *stack_b)
	{
		ft_memset(one_actions, 0, sizeof(one_actions));
		count_b(one_actions, *stack_b, cur_b, (int)data->size_b);
		count_a(one_actions, *stack_a, (int)get_pos(cur_b), (int)data->size_a);
		cur_sum = find_actions(one_actions);
		if (cur_sum < cur_min)
		{
			ft_memcpy(min_actions, one_actions, sizeof(one_actions));
			cur_min = cur_sum;
		}
		cur_b = cur_b->next;
	}
}

void	exec_n_cmds(char *op_line, t_dlist **stack_A, t_dlist **stack_B, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		execute_command(op_line, stack_A, stack_B, 0);
		i++;
	}
}
