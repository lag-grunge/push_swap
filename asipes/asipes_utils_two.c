#include "push_swap.h"
#include "asipes_sort.h"

void	restore_data_max_mid(t_cmn_asip_data *data)
{
	size_t	cur_max;
	size_t	cur_next;

	if (data->next > data->size >> 1)
	{
		cur_next = data->size - data->next;
		cur_max = data->size >> 1;
		while (cur_max && (cur_max >> 1) >= cur_next)
			cur_max >>= 1;
		data->max = data->size - cur_max;
		if ((cur_max >> 1) != 0)
			data->max += cur_max >> 1;
	}
	else
	{
		cur_max = data->size >> 1;
		cur_next = data->next;
		while (cur_max && (cur_max >> 1) >= cur_next)
			cur_max >>= 1;
		data->max = cur_max;
	}	
	data->mid = (data->max + data->next) / 2;
}

static int	find_dest_ab(t_dlist *a, t_dlist *b)
{
	t_dlist	*cur_prev;
	t_dlist	*cur_next;
	int		dest_prev;
	int		dest_next;

	cur_prev = a;
	cur_next = a;
	dest_next = 0;
	dest_prev = 0;
	while (cur_prev != b && cur_next != b)
	{
		cur_prev = cur_prev->prev;
		cur_next = cur_next->next;
		dest_prev++;
		dest_next--;
	}
	if (cur_prev == b)
		return (dest_prev);
	return (dest_next);
}

int	correctAchain(t_dlist **stack_A, t_cmn_asip_data *data)
{
	t_dlist	*next_list;
	int		cmd_num;
	int		dest;

	if (data->next == 0)
		return (0);
	next_list = *stack_A;
	while (get_pos(next_list) != data->next - 1)
		next_list = next_list->next;
	dest = find_dest_ab(next_list, (*stack_A)->prev);
	if (!dest)
		return (0);
	cmd_num = ra + (dest < 0);
	if (dest < 0)
		dest = -dest;
	exec_n_cmd_asip(cmd_num, dest, data);
	return (0);
}

int	operBelem(t_cmn_asip_data *data, int sec)
{
	size_t	cur_pos;
	t_dlist	**stack_A;
	t_dlist	**stack_B;

	stack_A = data->stack_A;
	stack_B = data->stack_B;
	cur_pos = get_pos(*stack_B);
	if (cur_pos <= data->mid && cur_pos != data->next)
		execute_command(data->op_lines[rb], stack_A, stack_B);
	else
	{
		if (!sec)
			*set_flag(*stack_B) = data->flag;
		execute_command("pa", stack_A, stack_B);
		if (cur_pos == data->next)
		{
			execute_command("ra", stack_A, stack_B);
			data->next++;
		}
	}
	return (1);
}
