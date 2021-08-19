#include "push_swap.h"

void 	data_change(t_list **stack_A)
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

t_asip_data *get_content_asip(t_list *stack)
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

void execute_asip_command(char *s, t_list **stack_A, t_list **stack_B)
{
	execute_command(s, stack_A, stack_B);
	asip_after_command_prev_fix(*stack_A);
	asip_after_command_prev_fix(*stack_B);
}

