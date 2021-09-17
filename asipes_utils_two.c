#include "push_swap.h"

void restore_data_max_mid(t_cmn_asip_data *data)
{
	size_t	cur_max;
	size_t 	cur_next;

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

static int correctAchain(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data)
{
	t_dlist	*last_A;
	size_t	cur_pos;
	int		res;
		
	cur_pos = get_pos(*stack_B);
	last_A = (*stack_A)->prev;
	res = 0;
	if (data->next == 0)
		return (0);
	while (get_pos(last_A) != data->next - 1)
	{
		if (cur_pos == data->next || cur_pos > data->mid)
			execute_command("ra", stack_A, stack_B);
		else
		{
			execute_command("rr", stack_A, stack_B);
			res++;
		}
		last_A = last_A->next;
		cur_pos = get_pos(*stack_B);
	}
	return (res);
}


int operBelem(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data, int sec)
{
	size_t 	cur_pos;
	int		res;

	res = correctAchain(stack_A, stack_B, data);
	cur_pos = get_pos(*stack_B);
	if (cur_pos <= data->mid && cur_pos != data->next)
		execute_command("rb", stack_A, stack_B);
	else
	{
		if (!sec)
            ((t_ps_data *)(*stack_B)->content)->flag = data->flag;
		execute_command("pa", stack_A, stack_B);
		if (cur_pos == data->next)
		{
			execute_command("ra", stack_A, stack_B);
			data->next++;
		}
	}
	return (res + 1);
}
