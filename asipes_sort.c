#include "push_swap.h"

static void	init_cmn_asip_data(t_cmn_asip_data *cmn_data, t_stck_data *data)
{
	cmn_data->size = data->size - 1;
	cmn_data->max = data->size - 1;
	cmn_data->mid = (cmn_data->max + cmn_data->next) / 2;
}

static void moveA_B(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data)
{
	size_t	i;
	size_t 	cur_pos;
	t_dlist	*last_A;

	i = data->next;
	last_A = (*stack_A)->prev;
	while (i <= data->mid)
	{
		cur_pos = get_pos(*stack_A);
		if (cur_pos <= data->mid && cur_pos >= data->next)
			i++;
		if (cur_pos == data->next && (!data->next || get_pos(last_A) == data->next - 1))
		{
			execute_command("ra", stack_A, stack_B);
			data->next++;
		}
		else if (cur_pos > data->mid || cur_pos < data->next)
			execute_command("ra", stack_A, stack_B);
		else
			execute_command("pb", stack_A, stack_B);
        last_A = last_A->next;
	}
	data->max = data->mid;
}


static void operB(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data, int sec)
{
	int	i;
	int	Ib;

	Ib = ft_dlst_size(*stack_B);
	while (Ib)
	{
		if (!sec)
			data->flag++;
		data->mid = (data->max + data->next) / 2;
		i = 0;
		while (i < Ib)
			i += operBelem(stack_A, stack_B, data, sec);
		Ib = ft_dlst_size(*stack_B);
		data->max = data->mid;
	}
}


static void	operA(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data)
{
	size_t cur_flag;

	while (get_flag(*stack_A))
	{
		cur_flag = get_flag(*stack_A);
		restore_data_max_mid(data);
		while (get_flag(*stack_A) == cur_flag)
		{
			if (get_pos(*stack_A) <= data->next)
			{
				if (get_pos(*stack_A) == data->next)
					data->next++;
				execute_command("ra", stack_A, stack_B);
			}
			else
				execute_command("pb", stack_A, stack_B);
		}
		operB(stack_A, stack_B, data, 1);
	}
}


int 	asipes_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	t_cmn_asip_data	cmn_data;
	
	asip_fl_change(stack_A);
	cmn_data.flag = 0;
	cmn_data.next = 0;
	while (cmn_data.next != data->size)
	{
		init_cmn_asip_data(&cmn_data, data);
		moveA_B(stack_A, stack_B, &cmn_data);	
		operB(stack_A, stack_B, &cmn_data, 0);	
		operA(stack_A, stack_B, &cmn_data);	
	}
	return (0);
}
