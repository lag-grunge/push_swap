#include "../push_swap.h"
#include "distance.h"

static void move_B(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	int	i;
	int pos;

	i = 0;
	while (i < (int)data->size - 2 || ft_dlst_size(*stack_A) > 2)
	{
		pos = (int)get_pos(*stack_A);
		if (pos != 0 && pos != (int)data->size - 1)
		{
			execute_command("pb", stack_A, stack_B, 0);
			if (pos < (int)data->size / 2)
				execute_command("rb", stack_A, stack_B, 0);
		}
		else
			execute_command("ra", stack_A, stack_B, 0);
		i++;
	}
}

static void exec_n_cmds(char *op_line, t_dlist **stack_A, t_dlist **stack_B, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		execute_command(op_line, stack_A, stack_B, 0);
		i++;
	}
}


static int same_directions(int *actions, t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	int m;
	int d;

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

static void exec_cmds(int *actions, t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	if (same_directions(actions, stack_A, stack_B, data))
		return ;
	if (actions[f(ra)])
		exec_n_cmds(data->op_lines[ra], stack_A, stack_B, actions[f(ra)]);
	else if (actions[f(rra)])
		exec_n_cmds(data->op_lines[rra], stack_A, stack_B, actions[f(rra)]);
	if (actions[f(rrb)])
		exec_n_cmds(data->op_lines[rrb], stack_A, stack_B, actions[f(rrb)]);
	else if (actions[f(rb)])
		exec_n_cmds(data->op_lines[rb], stack_A, stack_B, actions[f(rb)]);
}

static void correct_A(t_dlist **stack_A)
{
	int		dist1;
	t_dlist *prev;
	t_dlist *next;
	char	*op;

	prev = *stack_A;
	next = *stack_A;
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
	else//if (get_pos(next) < get_pos(next->prev))
		op = ft_strdup("ra");
	exec_n_cmds(op, stack_A, NULL, dist1);
	free(op);
}


void print_stack(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);

void distance_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	int min_actions[4];

	move_B(stack_A, stack_B, data);
	data->size_A = 2;
	data->size_B = data->size - data->size_A;
	while (data->size_B)
	{
		find_best_actions(min_actions, stack_A, stack_B, data);
		exec_cmds(min_actions, stack_A, stack_B, data);
		execute_command("pa", stack_A, stack_B, 0);
		data->size_B--;
		data->size_A++;
	}
	correct_A(stack_A);
}
