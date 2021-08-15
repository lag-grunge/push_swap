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

static t_asip_data *get_content_asip(t_list *stack)
{
	return ((t_asip_data *)(stack)->content);
}


static void asip_after_command_prev_fix(t_list *stack)
{
	t_list	*prev;
	t_list	*cur;
	
	cur = stack;
	prev = NULL;
	while (cur)
	{
		(get_content_asip(cur))->prev = prev;
		prev = cur;
		cur = cur->next;
	}
}

static void execute_asip_command(char *s, t_list **stack_A, t_list **stack_B)
{
	execute_command(s, stack_A, stack_B);
	asip_after_command_prev_fix(*stack_A);
	asip_after_command_prev_fix(*stack_B);
}

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

	i = data->next;
	while (i <= data->mid)
	{
		cur_pos = get_content_asip(*stack_A)->pos;
		if (cur_pos > data->mid || cur_pos < data->next)
			execute_asip_command("ra", stack_A, stack_B);
		else
		{
			execute_asip_command("pb", stack_A, stack_B);
			i++;
		}
	}
	data->max = data->mid;
}

static int correctAchain(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
{
	t_list	*last_A;
	size_t	cur_pos;
	int		res;
		
	cur_pos = (get_content_asip(*stack_B))->pos;
	last_A = ft_lstlast(*stack_A);
	res = 0;
	if (data->next == 0)
		return (0);
	while ((get_content_asip(last_A))->pos != data->next - 1)
	{
		if (cur_pos == data->next || cur_pos > data->mid)
			execute_asip_command("ra", stack_A, stack_B);
		else
		{
			execute_asip_command("rr", stack_A, stack_B);
			res++;
		}
		last_A = last_A->next;
		cur_pos = (get_content_asip(*stack_B))->pos;
	}
	return (res);
}


static int operBelem(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data, int sec)
{
	size_t 	cur_pos;
	int		res;

	res = correctAchain(stack_A, stack_B, data);
	cur_pos = (get_content_asip(*stack_B))->pos;
	if (cur_pos <= data->mid && cur_pos != data->next)
		execute_asip_command("rb", stack_A, stack_B);
	else
	{
		if (!sec)
			get_content_asip(*stack_B)->flag = data->flag;
		execute_asip_command("pa", stack_A, stack_B);
		if (cur_pos == data->next)
		{
			execute_asip_command("ra", stack_A, stack_B);
			data->next++;
		}
	}
	return (res + 1);
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

void restore_data_max_mid(t_cmn_asip_data *data)
{
	size_t	cur_max;
	size_t 	cur_next;

	if (data->next > data->size >> 1)
	{
		cur_next = data->size - data->next;
		cur_max = data->size >> 1;
		while (cur_max > 1 && cur_max >= cur_next)
			cur_max >>= 1;
		data->max = data->size - cur_max - 1;
		if (!cur_max)
			data->max++;
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

void	operA(t_list **stack_A, t_list **stack_B, t_cmn_asip_data *data)
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
	size_t i = 0;
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
		i++;
		operA(stack_A, stack_B, &cmn_data);	
		debug_print_stack(stack_A, stack_B);
	}
	return (0);
}
