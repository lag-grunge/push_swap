/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:59:11 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:59:13 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include "distance.h"

static void	move_b(t_dlist **stack_a, t_dlist **stack_b, t_stck_data *data)
{
	int	i;
	int	pos;

	i = 0;
	while (i < (int)data->size - 2 || ft_dlst_size(*stack_a) > 2)
	{
		pos = (int)get_pos(*stack_a);
		if (pos != 0 && pos != (int)data->size - 1)
		{
			execute_command("pb", stack_a, stack_b, 0);
			if (pos < (int)data->size / 2)
				execute_command("rb", stack_a, stack_b, 0);
		}
		else
			execute_command("ra", stack_a, stack_b, 0);
		i++;
	}
}

static int	same_directions(int *actions, t_dlist **stack_A, \
							t_dlist **stack_B, t_stck_data *data)
{
	int	m;
	int	d;

	if (actions[f(ra)] && actions[f(rb)])
	{
		m = min_dist(actions[f(ra)], actions[f(rb)], &d);
		exec_n_cmds(data->op_lines[rr], stack_A, stack_B, m);
		if (actions[f(ra)] > actions[f(rb)])
			exec_n_cmds(data->op_lines[ra], stack_A, stack_B, d);
		else if (actions[f(rb)] > actions[f(ra)])
			exec_n_cmds(data->op_lines[rb], stack_A, stack_B, d);
		return (1);
	}
	else if (actions[f(rra)] && actions[f(rrb)])
	{
		m = min_dist(actions[f(rra)], actions[f(rrb)], &d);
		exec_n_cmds(data->op_lines[rrr], stack_A, stack_B, m);
		if (actions[f(rra)] > actions[f(rrb)])
			exec_n_cmds(data->op_lines[rra], stack_A, stack_B, d);
		else if (actions[f(rrb)] > actions[f(rra)])
			exec_n_cmds(data->op_lines[rrb], stack_A, stack_B, d);
		return (1);
	}
	return (0);
}

static void	exec_cmds(int *actions, t_dlist **stack_a, \
					t_dlist **stack_b, t_stck_data *data)
{
	if (same_directions(actions, stack_a, stack_b, data))
		return ;
	if (actions[f(ra)])
		exec_n_cmds(data->op_lines[ra], stack_a, stack_b, actions[f(ra)]);
	else if (actions[f(rra)])
		exec_n_cmds(data->op_lines[rra], stack_a, stack_b, actions[f(rra)]);
	if (actions[f(rrb)])
		exec_n_cmds(data->op_lines[rrb], stack_a, stack_b, actions[f(rrb)]);
	else if (actions[f(rb)])
		exec_n_cmds(data->op_lines[rb], stack_a, stack_b, actions[f(rb)]);
}

static void	correct_a(t_dlist **stack_a)
{
	int		dist1;
	t_dlist	*prev;
	t_dlist	*next;
	char	*op;

	prev = *stack_a;
	next = *stack_a;
	dist1 = 0;
	while (get_pos(prev) > get_pos(prev->prev) && \
			get_pos(next) > get_pos(next->prev))
	{
		prev = prev->prev;
		next = next->next;
		dist1++;
	}
	if (get_pos(prev) < get_pos(prev->prev))
		op = ft_strdup("rra");
	else
		op = ft_strdup("ra");
	exec_n_cmds(op, stack_a, NULL, dist1);
	free(op);
}

void	distance_sort(t_dlist **stack_a, t_dlist **stack_b, t_stck_data *data)
{
	int	min_actions[4];

	move_b(stack_a, stack_b, data);
	data->size_a = 2;
	data->size_b = data->size - data->size_a;
	while (data->size_b)
	{
		find_best_actions(min_actions, stack_a, stack_b, data);
		exec_cmds(min_actions, stack_a, stack_b, data);
		execute_command("pa", stack_a, stack_b, 0);
		data->size_b--;
		data->size_a++;
	}
	correct_a(stack_a);
}
