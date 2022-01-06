#include "push_swap.h"
#include "distance.h"

static void count_actions_B(int *actions, t_dlist *stack_B, t_dlist *cur_B, int size_B)
{
	t_dlist *next;
	t_dlist *prev;
	int 	dist;

	next = stack_B;
	prev = stack_B;
	dist = 0;
	while (next != cur_B && prev != cur_B)
	{
		next = next->next;
		prev = prev->prev;
		dist++;
	}
	if (next == stack_B && prev == stack_B)
		return ;
	else if (next == cur_B)
	{
		actions[f(rb)] = dist;
		actions[f(rrb)] = size_B - dist;
	}
	else if (prev == cur_B) {
		actions[f(rrb)] = dist;
		actions[f(rb)] = size_B - dist;
	}
}

static void count_actions_A(int *actions, t_dlist *stack_A, int pos_B, int size_A)
{
	t_dlist *next;
	t_dlist *prev;
	int 	dist;

	next = stack_A;
	prev = stack_A;
	dist = 0;
	while (((int)get_pos(next) < pos_B || (int)get_pos(next->prev) > pos_B) &&\
		((int)get_pos(prev) < pos_B || (int)get_pos(prev->prev) > pos_B))
	{
		next = next->next;
		prev = prev->prev;
		dist++;
	}
	if (((int)get_pos(next) > pos_B && (int)get_pos(next->prev) < pos_B))
	{
		actions[f(ra)] = dist;
		actions[f(rra)] = size_A - dist;
	}
	else if ((int)get_pos(prev) > pos_B && (int)get_pos(prev->prev) < pos_B)
	{
		actions[f(rra)] = dist;
		actions[f(ra)] = size_A - dist;
	}
}


void find_best_actions(int *min_actions, t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	int one_actions[4];
	int cur_min;
	int cur_sum;
	t_dlist *cur_B;

	ft_memset(min_actions, 0, sizeof(one_actions));
	count_actions_B(min_actions, *stack_B, *stack_B, (int)data->size_B);
	count_actions_A(min_actions, *stack_A, (int) get_pos(*stack_B), (int)data->size_A);
	cur_min = find_actions(min_actions);
	cur_B = (*stack_B)->next;
	while (cur_B != *stack_B)
	{
		ft_memset(one_actions, 0, sizeof(one_actions));
		count_actions_B(one_actions, *stack_B, cur_B, (int)data->size_B);
		count_actions_A(one_actions, *stack_A, (int) get_pos(cur_B), (int)data->size_A);
		cur_sum = find_actions(one_actions);
		if (cur_sum < cur_min)
		{
			ft_memcpy(min_actions, one_actions, sizeof(one_actions));
			cur_min = cur_sum;
		}
		cur_B = cur_B->next;
	}
}
