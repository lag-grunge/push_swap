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
	cmn_data->max = data->size - 1;
	cmn_data->mid = (cmn_data->max - cmn_data->next) / 2 + cmn_data->next;
}

static void moveA_B(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t	i;

	i = data->next;
	while (i < data->mid + 1)
	{
		if (((t_asip_data *)(*stack_A)->content)->pos <= data->mid)
		{
			execute_command("pb", stack_A, stack_B);
			i++;
		}
		else 
			execute_command("ra", stack_A, stack_B);
	}
	debug_print_stack(stack_A, stack_B);
}

static void operB(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	size_t	i;
	size_t	cur_max;

	cur_max = data->mid;
	data->flag++;
	data->mid = (cur_max - data->next) / 2 + data->next;
	while (cur_max > data->next)
	{
		i = data->next;
		while (i++ < cur_max)
		{
			if (((t_asip_data *)(*stack_B)->content)->pos == data->next)
			{
				((t_asip_data *)(*stack_B)->content)->flag = data->flag;
				execute_command("pa", stack_A, stack_B);
				execute_command("ra", stack_A, stack_B);
				data->next++;
			}
			else if (((t_asip_data *)(*stack_B)->content)->pos <= data->mid)
				execute_command("rb", stack_A, stack_B);
			else 
			{
				((t_asip_data *)(*stack_B)->content)->flag = data->flag;
				execute_command("pa", stack_A, stack_B);
			}
		}
		sleep(10);
		cur_max = data->mid;
		data->mid = (cur_max - data->next) / 2 + data->next;
		data->flag++;
		debug_print_stack(stack_A, stack_B);
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
	return (0);
}
