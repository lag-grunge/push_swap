#include "push_swap.h"

static void	init_cmn_asip_data(t_cmn_asip_data *cmn_data, t_stck_data *data)
{
	cmn_data->size = data->size - 1;
	cmn_data->max = data->size - 1;
	cmn_data->mid = (cmn_data->max + cmn_data->next) / 2;
}

static void moveA_B(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t	i;
	size_t 	cur_pos;
	t_list	*last_A;
	size_t	last_A_pos;

	i = data->next;
	last_A = ft_lstlast(*stack_A);
	while (i <= data->mid)
	{
		cur_pos = get_content_asip(*stack_A)->pos;
		last_A_pos = get_content_asip(last_A)->pos;
		if (cur_pos == data->next && (!data->next || last_A_pos == data->next - 1))
		{
			execute_asip_command("ra", stack_A, stack_B);
			data->next++;
		}
		else if (cur_pos > data->mid || cur_pos < data->next)
			execute_asip_command("ra", stack_A, stack_B);
		else
			execute_asip_command("pb", stack_A, stack_B);
		if (last_A->next)
			last_A = last_A->next;
		if (cur_pos <= data->mid && cur_pos >= data->next)
			i++;
	}
	data->max = data->mid;
}


static void operB(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data, int sec)
{
	int	i;
	int	Ib;
	int	cur_next;

	Ib = ft_lstsize(*stack_B);
	while (Ib > 0)
	{
		if (!sec)
			data->flag++;
		data->mid = (data->max + data->next) / 2;
		i = 0;
		cur_next = data->next;
		while (i < Ib)
			i += operBelem(stack_A, stack_B, data, sec);
		Ib -= (int)(data->max - data->mid) + (int)(data->next - cur_next);
		data->max = data->mid;
	}
}


static void	operA(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t cur_flag;

	while (((t_asip_data *)(*stack_A)->content)->flag)
	{
		cur_flag = ((t_asip_data *)(*stack_A)->content)->flag;
		restore_data_max_mid(data);
		while (((t_asip_data *)(*stack_A)->content)->flag == cur_flag)
		{
			if (((t_asip_data *)(*stack_A)->content)->pos <= data->next)
			{
				if (((t_asip_data *)(*stack_A)->content)->pos == data->next)
					data->next++;
				execute_asip_command("ra", stack_A, stack_B);
			}
			else
				execute_asip_command("pb", stack_A, stack_B);
		}
		operB(stack_A, stack_B, data, 1);
	}
}


int 	asipes_sort(t_list **stack_A, t_list **stack_B, t_stck_data *data)
{
	t_cmn_asip_data	cmn_data;
	
	data_change(stack_A);
	cmn_data.flag = 0;
	cmn_data.next = 0;
	while (cmn_data.next != data->size)
	{
		init_cmn_asip_data(&cmn_data, data);
		printf("Move A B\n");
		moveA_B(stack_A, stack_B, &cmn_data);	
		debug_print_stack(stack_A, stack_B);
		printf("oper B\n");
		operB(stack_A, stack_B, &cmn_data, 0);	
		debug_print_stack(stack_A, stack_B);
		printf("oper A\n");
		operA(stack_A, stack_B, &cmn_data);	
		debug_print_stack(stack_A, stack_B);
	}
	return (0);
}
