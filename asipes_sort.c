#include "push_swap.h"

static void 	data_change(t_list **stack_A)
{
	t_list		*cur;
	t_list		*prev;
	t_list		*next;
	t_asip_data *asip_data;

	prev = NULL;
	cur = *stack_A;
	while (cur)
	{
		next = cur->next;
		asip_data = (t_asip_data *)malloc(sizeof(t_asip_data) * 1);
		asip_data->val = get_val(cur);
		asip_data->pos = get_pos(cur);
		asip_data->flag = 0;
		asip_data->prev = prev;
		free(cur->content);
		cur->content = asip_data;
		prev = cur;
		cur = next;
	}
}

static void	init_cmn_asip_data(t_cmn_asip_data *cmn_data, t_stck_data *data)
{
	cmn_data->size = data->size - 1;
	cmn_data->max = data->size - 1;
	cmn_data->mid = (cmn_data->max - cmn_data->next) / 2 + cmn_data->next;
}

static void moveA_B(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t	i;

	i = data->next;
	while (i < data->mid + 1)
	{
		if (((t_asip_data *)(*stack_A)->content)->pos > data->mid)
			execute_command("ra", stack_A, stack_B);
		else if (((t_asip_data *)(*stack_A)->content)->pos < data->next)
			execute_command("ra", stack_A, stack_B);
		else if (((t_asip_data *)(*stack_A)->content)->pos > data->next)
		{
			execute_command("pb", stack_A, stack_B);
			i++;
		}
		else if (((t_asip_data *)(*stack_A)->content)->pos == data->next)
		{ 
			execute_command("ra", stack_A, stack_B);
			i++;
			data->next++;
		}
	}
	data->flag++;
	data->max = data->mid;
	debug_print_stack(stack_A, stack_B);
}

static void operB(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t	i;

	while (data->max >= data->next)
	{
		data->mid = (data->max - data->next) / 2 + data->next;
		i = data->next;
		while (i <= data->max)
		{
			if (((t_asip_data *)(*stack_B)->content)->pos == data->next)
			{
				execute_command("pa", stack_A, stack_B);
				execute_command("ra", stack_A, stack_B);
				data->next++;
			}
			else if (((t_asip_data *)(*stack_B)->content)->pos < data->mid)
				execute_command("rb", stack_A, stack_B);
			else 
			{
				((t_asip_data *)(*stack_B)->content)->flag = data->flag;
				execute_command("pa", stack_A, stack_B);
			}
			i++;
		}
		data->max = data->mid - 1;
		data->flag++;
		debug_print_stack(stack_A, stack_B);
	}
}

void restore_data_max_mid(t_cmn_asip_data *data, size_t cur_flag)
{
	size_t	i;

	data->max = data->size >> 1;
	i = 1;
	while (i++ < cur_flag)
		data->max >>= 1;
	data->mid = (data->max - data->next) / 2 + data->next;
}

void	operA(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t cur_flag;

	while (((t_asip_data *)(*stack_A)->content)->flag)
	{
		cur_flag = ((t_asip_data *)(*stack_A)->content)->flag;
		while (((t_asip_data *)(*stack_A)->content)->flag == cur_flag)
		{
			if (((t_asip_data *)(*stack_A)->content)->pos <= data->next)
			{
				if (((t_asip_data *)(*stack_A)->content)->pos == data->next)
					data->next++;
				execute_command("ra", stack_A, stack_B);
			}
			else
				execute_command("pb", stack_A, stack_B);
		}
		restore_data_max_mid(data, cur_flag);
		operB(stack_A, stack_B, data);
	}
}


int 	asipes_sort(t_list **stack_A, t_list **stack_B, t_stck_data *data)
{
	t_cmn_asip_data	cmn_data;
	
	data_change(stack_A);
	cmn_data.flag = 0;
	cmn_data.next = 0;
	init_cmn_asip_data(&cmn_data, data);
	moveA_B(stack_A, stack_B, &cmn_data);	
	operB(stack_A, stack_B, &cmn_data);	
	operA(stack_A, stack_B, &cmn_data);	
	return (0);
}
